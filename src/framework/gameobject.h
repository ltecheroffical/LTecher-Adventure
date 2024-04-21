#include <SDL3/SDL.h>

#include <framework/math.h>

#ifndef FRAMEWORK_GAMEOBJECT_H
#define FRAMEWORK_GAMEOBJECT_H

class App;
class Scene;

class GameObject {
friend class App;
friend class Scene;
public:
  virtual ~GameObject() = default;
   
  float get_x() { return position.x; };
  float get_y() { return position.y; };

protected:
  Vec2 position = {0.0f, 0.0f};
  Vec2 scale = {1.0f, 1.0f};

  unsigned int render_priority = 0;

  virtual void init() { /* empty */ };
  virtual void late_init() { /* empty */ };

  virtual void update(const float delta) { /* empty */ };
  virtual void render(SDL_Renderer *renderer) { /* empty */ };
  virtual void destroy() { /* empty */ };
};
#endif
