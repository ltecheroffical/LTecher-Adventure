#include <iostream>
#include <vector>

#include <raylib.h>

#include <gameobject.h>
#include <scene.h>

#include <scenes/scene_game.h>

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 450;

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
		if (!object->visible)
		{
			continue;
		}
		object->on_render();
	}
}
#pragma endregion

int main()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LTecher Adventure");

	SetWindowState(FLAG_WINDOW_RESIZABLE);

	Scene::set_current_scene(std::make_shared<GameScene>());

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground({0, 255, 255, 255});

		if (Scene::is_scene_loaded())
		{
			Scene::get_current_scene()->on_update();
			
			update_objects(Scene::get_current_scene()->get_children());
			render_objects(Scene::get_current_scene()->get_children());
		} 

		EndDrawing();
	}

	CloseWindow();
	return 0;
}