#include <optional>
#include <memory>

#include "scene.h"

std::optional<std::shared_ptr<Scene>> Scene::current_scene = std::nullopt;

void Scene::set_current_scene(std::shared_ptr<Scene> scene)
{
    if (Scene::is_scene_loaded())
    {
        Scene::unload_current_scene();
    }

    Scene::current_scene = scene;
    scene.get()->on_load();
}

std::shared_ptr<Scene> Scene::get_current_scene()
{
    if (!Scene::current_scene.has_value())
    {
        throw std::make_unique<std::exception>();
    }

    return Scene::current_scene.value();
}

void Scene::unload_current_scene()
{
    if (!Scene::current_scene.has_value())
    {
        throw std::make_unique<std::exception>();
    }

    Scene::current_scene.value()->on_unload();
    Scene::current_scene = std::nullopt;
}
