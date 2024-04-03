#include <scene.h>

#pragma once

class Screen
{
public:
  Screen(Scene *scene) { this->scene = scene; };
  virtual ~Screen() = default;


  /*
   * Called once when the screen is susposed to initialize
   */ 
  virtual void init() { /* Override to listen to event */ };

  /*
   * Called every frame when the screen should update
   *
   * @param delta The time since the last frame
   */
  virtual void update(float delta) { /* Override to listen to event */ };
  /*
   * Called every frame when the screen should render
   */
  virtual void render() { /* Override to listen to event */ };

protected:
  Scene *scene; // A raw pointer will be okay because we don't manage memory for this class
};
