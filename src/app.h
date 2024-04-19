/*
 * LTecher Adventure (c) 2024
 *
 * This file belongs to the LTeacher Adventure project
 */

#include <map>

#include <SDL3/SDL.h>

#include <event.h>

#ifndef APP_H
#define APP_H

class App {
public:
  inline static App& singleton() {
    static App app;
    return app;
  }

  inline bool is_running() {
    return this->_running;
  }

  inline void exit() {
    this->_running = false;
  }

  Event<float> on_update;
  Event<SDL_Renderer> on_render;

  Event<SDL_Event> on_event;
  Event<SDL_Event> on_event_post;

  SDL_Window *window;
  SDL_Renderer *renderer;

  std::map<std::string, void *> globals;

private:
  App() = default;
  ~App() = default;

  bool _running = true;
};
#endif
