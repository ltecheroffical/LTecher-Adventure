#include <iostream>
#include <vector>
#include <filesystem>

#include <raylib.h>
#include <asset_ids.h>

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

	for (std::shared_ptr<Plugin> extension : *App::get_loaded_plugins())
	{
		extension.get()->on_update(GetFrameTime());
	}
}

void render_objects(const std::vector<std::shared_ptr<GameObject>> *objects)
{

	for (std::shared_ptr<GameObject> object : *objects)
	{
		if (!object->visible || object->is_gui)
		{
			continue;
		}
		object->on_render();
	}

	for (std::shared_ptr<GameObject> object : *objects)
	{
		if (!object->visible || !object->is_gui)
		{
			continue;
		}
		object->on_render();
	}

	for (std::shared_ptr<Plugin> extension : *App::get_loaded_plugins())
	{
		extension.get()->on_render();
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
	if (!std::filesystem::exists(RESOURCES_PATH))
	{
		std::cerr << "ERROR: FATAL: RESOURCES NOT FOUND!" << std::endl;
		return 1;
	} 
	
	InitWindow(App::DEFAULT_SCREEN_WIDTH, App::DEFAULT_SCREEN_HEIGHT, "LTecher Adventure");

	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetWindowMinSize(450, 350);

#ifdef WIN32
	SetWindowIcon(LoadImageFromMemory(".png", (unsigned char*)assets.at(0), asset_sizes.at(0)));
#endif

	InitAudioDevice();

	SetTargetFPS(60); // -1 Will disable frame cap

  try
  {
    load_assets((char*)RESOURCES_PATH);
  }
  catch (char *error_message)
  {
    std::cerr << "ERROR: FATAL: RESOURCES COULD NOT LOAD! " << error_message << std::endl;
    return 1;
  }


	constexpr float blank_splash_time = 1.5;
	
	float remaining_splash_time = 3.5;

	bool splash_fx_played = false;
	bool splash_unloaded = false;
  
  Wave  fx_splash_wave   = LoadWaveFromMemory(".wav", (unsigned char*)assets.at(10), asset_sizes.at(10));
	Sound fx_splash        = LoadSoundFromWave(fx_splash_wave);
  UnloadWave(fx_splash_wave);

  Image   splash_image   = LoadImageFromMemory(".png", (unsigned char*)assets.at(2), asset_sizes.at(2));
	Texture splash_texture = LoadTextureFromImage(splash_image);
  UnloadImage(splash_image);
	
  #if PRODUCTION_BUILD == 0
	App::load_plugin(std::make_shared<Debugger>());
  #endif
	
	for (std::shared_ptr<Plugin> extension : *App::get_loaded_plugins())
	{
		extension.get()->on_game_start();
	}

	while (!WindowShouldClose() && App::is_running())
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

			if (Scene::is_scene_loaded())
			{
				Scene::get_current_scene()->on_update(GetFrameTime());
				
				update_objects(Scene::get_current_scene()->get_children());
				render_objects(Scene::get_current_scene()->get_children());
			} 
		
		if (!CLRCMP(App::screen_tint, WHITE))
		{
			DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(App::screen_tint, 0.2f));
		}
		EndDrawing();
	}
  
  unload_assets();

	CloseAudioDevice();
	CloseWindow();
	return 0;
}
