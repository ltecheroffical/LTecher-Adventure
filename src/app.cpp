#include <gameobject.h>
#include <scene.h>

#include "app.h"

bool App::running = true;

Event<float> App::on_update;
Event<> App::on_render;

Color App::screen_tint = WHITE;

vec<std::shared_ptr<Plugin>> App::plugins;

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
