#include <iostream>
#include <vector>
#include <filesystem>

#if PRODUCTION_BUILD == 1
  #define REMOVE_IMGUI
#endif

#include <raylib.h>
#include <GLFW/glfw3.h>
#include <tinyfiledialogs.h>

#ifndef REMOVE_IMGUI
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#endif

#include <asset_ids.h>

#include <tick_system.h>
#include <gameobject.h>
#include <scene.h>
#include <app.h>

#include <marcos/compare.h>

#include <plugin.h>
#include <extensions/debug.h>

#include <scenes/scene_game.h>


#pragma region Update Objects
void update_objects(const std::vector<std::shared_ptr<GameObject>> *objects)
{
	for (std::shared_ptr<GameObject> object : *objects)
	{
		object->on_update(GetFrameTime());
	}

	for (std::shared_ptr<Plugin> extension : *App::singleton().get_loaded_plugins())
	{
		extension.get()->on_update(GetFrameTime());
	}
}
#pragma endregion

float process_splash(float splash_time_passed, float blank_splash_time, Texture splash_texture)
{
	float remaining_splash_time = splash_time_passed;

	if (IsKeyDown(KEY_SPACE))
	{
		return -1;
	}

	BeginDrawing();

	ClearBackground(WHITE);

	if (splash_time_passed < blank_splash_time)
	{
		constexpr float splash_scale = 0.5;
		DrawTextureEx(splash_texture,
			{static_cast<float>((((GetScreenWidth()) - (splash_texture.width * splash_scale)) / 2.0)), 5.0 },
				0.0, splash_scale, WHITE);
	}

	EndDrawing();

	return remaining_splash_time - GetFrameTime();
}

int main()
{
  bool game_checks_successful = false;
  std::string error_message;

  // Resources check
	if (!std::filesystem::exists(RESOURCES_PATH))
	{
    std::cerr << "ERROR: FATAL: RESOURCES NOT FOUND!" << std::endl;
    error_message = "ERR_RESOURCES_NOT_FOUND";
  }
  else
  {
    game_checks_successful = true;
  }

  // Init
	InitWindow(App::DEFAULT_SCREEN_WIDTH, App::DEFAULT_SCREEN_HEIGHT, "LTecher Adventure");

	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetWindowMinSize(450, 350);

	InitAudioDevice();

  // Timing
	SetTargetFPS(60); // -1 will disable frame cap
  TickSystem& tick_system = TickSystem::singleton();

  SetExitKey(KEY_NULL);

  // ImGui
#ifndef REMOVE_IMGUI
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
  ImGui_ImplOpenGL3_Init();
#endif

  // Assets
  try
  {
    load_assets((char*)RESOURCES_PATH);
  }
  catch (char *error_message)
  {
    std::cerr << "ERROR: FATAL: RESOURCES COULD NOT LOAD! " << error_message << std::endl;
    CloseWindow();
    return 1;
  }

  // Windows users
#ifdef WIN32
	SetWindowIcon(LoadImageFromMemory(".png", (unsigned char*)assets_raw.at(0), asset_sizes.at(0)));
#endif
  
  // Splash
	constexpr float blank_splash_time = 1.5;
	
	float remaining_splash_time = 3.5;

	bool splash_fx_played = false;
	bool splash_unloaded = false;

  Sound   fx_splash = {};
  Texture splash_texture = {};
  try
  {
    Wave fx_splash_wave = LoadWaveFromMemory(".wav", (unsigned char*)assets_raw.at(10), asset_sizes.at(10));
    fx_splash = LoadSoundFromWave(fx_splash_wave);
    UnloadWave(fx_splash_wave);

    Image splash_image = LoadImageFromMemory(".png", (unsigned char*)assets_raw.at(2), asset_sizes.at(2));
    splash_texture = LoadTextureFromImage(splash_image);
    UnloadImage(splash_image);
  }
  catch (std::exception &error)
  {
    std::cerr << "ERROR: SPLASH COULD NOT LOAD! " << error.what() << std::endl;
  }
  
  // Plugins
	App::singleton().load_plugin(std::make_shared<Debugger>());
	
	for (std::shared_ptr<Plugin> extension : *App::singleton().get_loaded_plugins())
	{
		extension.get()->on_game_start();
	}

  if (!game_checks_successful)
  {
    std::string message_text = "";
    message_text.append("Cannot load the game due to an error:\n\n Code: ");
    message_text.append(error_message.c_str());
    if (tinyfd_messageBox("LTecher Adventure - Error", message_text.c_str(), "ok", "error", 1))
    {
      App::singleton().close();
    }
  }

  // Main Loop
	while (!WindowShouldClose() && App::singleton().is_running())
	{	
    if (remaining_splash_time > 0)
    {
      if (remaining_splash_time < blank_splash_time && !splash_fx_played)
      {
        PlaySound(fx_splash);
        splash_fx_played = true;
      }
      remaining_splash_time = process_splash(remaining_splash_time, blank_splash_time, splash_texture);
      continue;
    }
    else if (!splash_unloaded)
    {
      UnloadSound(fx_splash);
      UnloadTexture(splash_texture);

      splash_unloaded = true;
      Scene::set_current_scene(std::make_shared<GameScene>());
    }

		BeginDrawing();
      ClearBackground({0, 255, 255, 255});

#ifndef REMOVE_IMGUI
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();
#endif  
      if (Scene::is_scene_loaded())
			{
        App::singleton().on_update.emit(GetFrameTime());
				update_objects(Scene::get_current_scene()->get_children());
        Scene::get_current_scene()->on_update(GetFrameTime());

        App::singleton().on_render.emit();
        App::singleton().render_objects(Scene::get_current_scene()->get_children());
        Scene::get_current_scene()->on_render();
			}

		  if (!CLRCMP(App::singleton().screen_tint, WHITE))
		  {
			  DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(App::singleton().screen_tint, 0.2f));
		  }

#ifndef REMOVE_IMGUI
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
		EndDrawing();
	}

  App::singleton().on_close.emit();
  unload_assets();

#ifndef REMOVE_IMGUI
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
#endif

	CloseAudioDevice();
	CloseWindow();
	return 0;
}
