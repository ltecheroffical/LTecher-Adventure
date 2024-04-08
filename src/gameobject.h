#include <raylib.h>

#include <map>

#include <random/random.h>

#include <components/component.h>
#include <vector>

#pragma once

/*
* The base class for all objects in a `Scene` class
* 
* @name GameObject
*/
class GameObject
{
public:
  GameObject() = default;
  virtual ~GameObject() {
    for (auto component : this->components)
    {
      this->remove_component(component.first);
    }
  };
  
  static const int COMPONENT_ID_NONE = -1;

  /*
  * The position at where the gameobject is rendered
  */
  Vector2 position = { 0, 0 };
  /*
  * The rotation of the gameobject
  */
  float rotation = 0;
  /*
  * The scale as the size multiplier
  */
  float scale = 1;
  /*
  * If the rendering of the gameobject is skipped
  */
  bool visible = true;
  /*
  * If the gameobject is rendered on top
  */
  bool is_gui = false;

  /*
  * Called once the object enters the scene
  */
  virtual void on_start() { /* Override to listen to event */ };

  /*
  * Called every frame while the game is running
  * NOTE: This is a virutal function  
  *    
  * @param delta The time since the last frame was rendered to now
  */
  virtual void on_update(float delta) { /* Override to listen to event */ };
  /*
  * Called every frame when the gameobject should render
  */
  virtual void on_render() { /* Override to listen to event */ };

  /*
  * Called when the object is about to exit the scene
  */
  virtual void on_exit() { /* Override to listen to event */ };


  /*
   * Add a component
   *
   * @param component The component to add
   * @param id The id of the component (if `OBJ_ID_NONE` a random id will be generated)
   */
  inline void add_component(Component *component, int id) {
    component->set_parent(this);

    if (id == COMPONENT_ID_NONE)
    {
      this->components.try_emplace(Random::int_urandom(), component);
      return;
    }
    this->components.try_emplace(id, component);
  };

  /*
   * Get a component
   *
   * @param id The id of the component to get
   */
  inline Component *get_component(int id) {
    return this->components.at(id);
  };

  /*
   * Remove a component
   *
   * @param id The id of the component to remove
   */
  inline void remove_component(int id) {
    this->components.at(id)->set_parent(nullptr);
    this->components.erase(id);
  };

  /*
   * Get all the components
   *
   * @return A vector of all the components
   */
  inline std::vector<Component*> get_components() {
    std::vector<Component*> components;

    for (auto component : this->components)
    {
      components.push_back(component.second);
    }
    return components;
  }

private:
  std::map<int, Component*> components;
};
