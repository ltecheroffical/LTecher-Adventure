#include <vector>
#include <map>
#include <optional>
#include <memory>
#include <random>

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

    static const int OBJ_ID_NONE = -1;

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
    virtual void on_update(float delta) { /* Override to listen to event */ };
    /*
    * Called every frame when the scene can render extra graphics
    */
    virtual void on_render() { /* Override to listen to event */ };
    /*
    * Called when the scene is unloaded
    */
    virtual void on_unload() { /* Override to listen to event */ };

    inline std::vector<std::shared_ptr<GameObject>> *get_children() {
        return &this->objects;
    };
    
    inline void add_child(std::shared_ptr<GameObject> object, int id) {
        this->objects.push_back(object);
        object.get()->on_start();

        if (id != Scene::OBJ_ID_NONE)
        {
            object_map.try_emplace(id, object);
        }
    };

    inline std::shared_ptr<GameObject> get_child(int id) {
        if (!object_map.contains(id))
        {
            return nullptr;
        }
        return object_map.at(id);
    };

    inline bool has_child(int id) const {
        return object_map.contains(id);
    };

private:
    static std::optional<std::shared_ptr<Scene>> current_scene;

    std::vector<std::shared_ptr<GameObject>> objects;
    std::map<int, std::shared_ptr<GameObject>> object_map;
};
