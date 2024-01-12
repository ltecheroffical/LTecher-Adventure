#include <iostream>
#include <vector>
#include <filesystem>

#include <raylib.h>

#include <gameobject.h>
#include <scene.h>
#include <app.h>

#include <scenes/scene_game.h>

#pragma region Update Objects
void update_objects(const std::vector<std::shared_ptr<GameObject>> *objects)
{
	for (std::shared_ptr<GameObject> object : *objects)
	{
		object->on_update(GetFrameTime());
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

	InitAudioDevice();

	Scene::set_current_scene(std::make_shared<GameScene>());

	constexpr float blank_splash_time = 1.5;
	
	float remaining_splash_time = 3.5;

	bool splash_fx_played = false;
	bool splash_unloaded = false;

	Sound fx_splash        = LoadSound(RESOURCES_PATH "audio/sfx/start.wav");
	Texture splash_texture = LoadTexture(RESOURCES_PATH "images/branding/Splash.png");

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
		}

		BeginDrawing();
			ClearBackground({0, 255, 255, 255});

			if (Scene::is_scene_loaded())
			{
				Scene::get_current_scene()->on_update(GetFrameTime());
				
				update_objects(Scene::get_current_scene()->get_children());
				render_objects(Scene::get_current_scene()->get_children());
			} 
		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();
	return 0;
}