#include <vector>
#include <optional>
#include <memory>

#include <gameobject.h>

#pragma once


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
    static void set_current_scene(std::shared_ptr<Scene> scene);
    /*
    * Gets the current scene
    * 
    * @throws std::exception
    * @throw If there is no scene loaded
    * 
    * @returns The current loaded scene
    */
    static std::shared_ptr<Scene> get_current_scene();

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
    * Called every frame while the scene is loaded
    */
    virtual void on_update() { /* Override to listen to event */ };
    /*
    * Called when the scene is unloaded
    */
    virtual void on_unload() { /* Override to listen to event */ };

    inline std::vector<std::shared_ptr<GameObject>> *get_children() {
        return &this->objects;
    };
    
    inline void add_child(GameObject *object) {
        std::shared_ptr<GameObject> gameobject_ptr;
        gameobject_ptr.reset(object);

        this->objects.push_back(gameobject_ptr);
        gameobject_ptr.get()->on_start();
    };

private:
    static std::optional<std::shared_ptr<Scene>> current_scene;

    std::vector<std::shared_ptr<GameObject>> objects;
};
