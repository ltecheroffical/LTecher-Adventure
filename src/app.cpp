#include <gameobject.h>
#include <scene.h>

#include "app.h"

App::App()
{
  this->running = true;
  this->screen_tint = Color{ 0, 0, 0, 0 };
}

void App::render_objects(const std::vector<std::shared_ptr<GameObject>> *objects)
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
