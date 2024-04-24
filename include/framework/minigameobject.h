#include <functional>

#include <SDL3/SDL.h>

#include "gameobject.h"

#ifndef FRAMEWORK_MINIGAMEOBJECT_H
#define FRAMEWORK_MINIGAMEOBJECT_H

/*
 * A interface for any data to pass into `MiniGameObject`
 */
class IMiniGameObjectData {
/*
 * We really don't need much, this is for C++ strong typing
 */
public:
  virtual ~IMiniGameObjectData() = default; 
};

/*
 * An empty version of the IMiniGameObjectData interface
 * Used for default values
 */
class MiniObjectDataEmpty : public IMiniGameObjectData {
  
};

/*
 * A version of the GameObject class that can be created quickly
 * It will run functions you pass in to the object
 */
class MiniGameObject : public GameObject {
public:
  MiniGameObject(
      const std::function<void()> init_func = nullptr,
      const std::function<void()> late_init_func = nullptr,
      const std::function<void(const float)> update_func = nullptr,
      const std::function<void(SDL_Renderer*)> render_func = nullptr) {

    if (init_func != nullptr) this->init_func = init_func;
    if (late_init_func != nullptr) this->late_init_func = late_init_func;

    if (update_func != nullptr) this->update_func = update_func;
    if (render_func != nullptr) this->render_func = render_func;
  };
  ~MiniGameObject() = default;

  std::function<void()> init_func = []() { /* empty */ };
  std::function<void()> late_init_func = []() { /* empty */ };
  std::function<void(const float)> update_func = [](const float _) { /* empty */ };
  std::function<void(SDL_Renderer*)> render_func = [](SDL_Renderer *_) { /* empty */ };

protected:
  void init() override { this->init_func(); };
  void late_init() override { this->late_init_func(); };
  void update(const float delta) override { this->update_func(delta); };
  void render(SDL_Renderer *renderer) override { this->render_func(renderer); };
};
#endif
