#include <vector>
#include <optional>

#include <gameobject.h>

#ifndef SCENE_H
#define SCENE_H

/*
* A scene that contains all `GameObject`s
* 
* @name Scene
*/
class Scene
{
public:
    Scene() = default;
    virtual ~Scene() = default;

    /*
    * Sets the current loaded scene
    * 
    * @param scene The scene to change to
    */
    static void set_current_scene(Scene scene);
    /*
    * Gets the current scene
    * 
    * @throws std::exception
    * @throw If there is no scene loaded
    * 
    * @returns The current loaded scene
    */
    static Scene get_current_scene();

    /*
    * Unloads the current scene
    * 
    * @throws std::exception
    * @throw If there is no loaded scene
    */
    static void unload_current_scene();
    /*
    * Returns if there is a loaded scene
    *
    * @returns Boolean indicating if there is a loaded scene
    */
    inline static bool is_scene_loaded() { return Scene::current_scene != std::nullopt; };

    /*
    * Called when the scene is loaded
    */
    virtual void on_load() { /* Override to listen to event */ };
    /*
    * Called when the scene is unloaded
    */
    virtual void on_unload() { /* Override to listen to event */ };

private:
    static std::optional<Scene> current_scene;

    std::vector<GameObject> objects;
};
#endif