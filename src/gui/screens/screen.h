#include <scene.h>

#pragma once

class Screen
{
public:
  Screen(Scene *scene) { this->scene = scene; };
  virtual ~Screen() = default;


  virtual void init() { /* Override to listen to event */ };

  virtual void update(float delta) { /* Override to listen to event */ };
  virtual void render() { /* Override to listen to event */ };

protected:
  Scene *scene;
};
