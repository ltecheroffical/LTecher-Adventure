#pragma once

class GameObject;

class Component
{
public:
  Component() = default;
  virtual ~Component() = default;

  virtual void on_update(float delta) { /* Override to listen to event */ };
  virtual void on_render() { /* Override to listen to event */ };

  /*
   * Set the parent of the component
   *
   * @param parent The parent of the component
   */
  inline void set_parent(GameObject *parent) { this->parent = parent; };

protected:
  GameObject *parent = nullptr;
};
