#include <cstdlib>
#include <vector>
#include <map>
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

  /*
   * Gets all the objects in the scene
   * 
   * @returns A vector of all the objects
   */
  inline std::vector<std::shared_ptr<GameObject>> *get_children() {
    return &this->objects;
  };
  
  /*
   * Adds an object to the scene
   *
   * @param object The object to add
   * @param id The id of the object (if value is `OBJ_ID_NONE` it will be added as a random id)
   */
  void add_child(std::shared_ptr<GameObject> object, int id);

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

protected:
  Color background_color = {100, 100, 100, 255};

private:
  static std::optional<std::shared_ptr<Scene>> current_scene;

  std::vector<std::shared_ptr<GameObject>> objects;
  std::map<int, std::shared_ptr<GameObject>> object_map;
};
