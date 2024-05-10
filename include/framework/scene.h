#include <map>

#include <SDL3/SDL.h>

#include <framework/gameobject.h>

#ifndef FRAMEWORK_SCENE_H
#define FRAMEWORK_SCENE_H

class Scene {
friend class App;
public:
  static unsigned int OBJ_ID_NULL;
  virtual ~Scene() = default;

  /*
   * Add a child to the scene
   *
   * @param child The child to add
   * @param id The ID of the child
   *
   * @returns The ID of the child
   */
  int add_child(GameObject* child, unsigned int id) {
    if (id != Scene::OBJ_ID_NULL) {
      this->_children[id] = child;
      child->init();
      return id;
    } else {
      // Some random ID
      int generated_id = rand();
      this->_children[generated_id] = child;
      return generated_id;
    }
  }

  /*
   * Remove a child from the scene
   * @param id The ID of the child to remove
   *
   */
  void remove_child(const unsigned int id) {
    this->_children.at(id)->destroy();
    this->_children.erase(id);
  }

  /*
   * Get a child from the scene
   * @param id The ID of the child
   * @returns A raw pointer to the child
   */
  GameObject *get_child(const unsigned int id) const {
    return this->_children.at(id);
  }

  Vec2 camera = Vec2{0, 0};

protected:
  /*
   * This function is called once when the scene is first switched to
   */
  virtual void init() { /* You do not need to implement this */ };
  /*
   * This function is called once after the scene is switched to
   */
  virtual void late_init() { /* You do not need to implement this */ };

  /*
   * This function is called when the scene is about to be unloaded
   */
  virtual void unload() { /* You do not need to implement this */ }; 


  SDL_Color _background_color = {0, 255, 255, 255};

  std::map<unsigned int, GameObject*> _children;
};
inline unsigned int Scene::OBJ_ID_NULL = 0;
#endif

