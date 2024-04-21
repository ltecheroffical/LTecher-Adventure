#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <marcos/errors.h>

#include <scenes/scene_game.h>

#include <keybinds.h>

#include "app.h"

App *App::_app = nullptr;

App::App() {
  if (this->_app != nullptr) {
    throw std::runtime_error("App already exists");
  }

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    PANIC("Failed to initialize SDL", EXIT_MAJOR_ERROR);
  }

  if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
    PANIC("Failed to initialize SDL_image", EXIT_MAJOR_ERROR);
  }

  this->_app = this;
}

App::~App() {
  this->_app = nullptr;
  if (this->_running) {
    this->exit();
  }
  SDL_Quit();
}

int App::run() {
  this->window = SDL_CreateWindow(
    "LTecher-Adventure", 650, 350,
    SDL_WINDOW_RESIZABLE
  );

  if (this->window == NULL) {
    SDL_Quit();
    PANIC("Failed to create window", EXIT_MAJOR_ERROR);
  }

  this->renderer = SDL_CreateRenderer(this->window, NULL, 0);

  if (this->renderer == NULL) {
    SDL_DestroyWindow(this->window);
    SDL_Quit();
    PANIC("Failed to create renderer", EXIT_MAJOR_ERROR);
  }

  this->_running = true;

  uint64_t now, last = 0;

  this->set_scene(new SceneGame());

  Keybinds::singleton().reset();
  
  SDL_Event event;
  while (this->_running) {
    while (SDL_PollEvent(&event)) {
      this->on_event.emit(event);
      switch (event.type) {
        case SDL_EVENT_QUIT:
          this->exit();
          break;
        default:
          break;
      }
      this->on_event_post.emit(event);
    }

    float delta = 0.0f;

    last = now;
    now = SDL_GetPerformanceCounter();

    delta = (float)((now - last)*1000 / (float)SDL_GetPerformanceFrequency()) * 0.001f;

    static bool inital_frame = true;
    if (inital_frame) {
      delta = 0.0f;
      inital_frame = false;
    }

    this->update(delta);
    this->on_update.emit(delta);

    this->render(this->renderer);
    this->on_render.emit(this->renderer);

    if (this->_max_fps_enabled) {
      SDL_Delay(1000 / this->_max_fps);
    }
  }
  return 0;
}

void App::exit() {
  if (!this->_running) {
    throw std::runtime_error("App is not running");
  }
  this->_running = false;
  this->on_exit.emit();

  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
}

void App::update(float delta) {
#if PRODUCTION_BUILD == 0
  this->_debug_window_title = "LTecher Adventure";
  
  this->_debug_window_title += " | FPS: " + std::to_string(
    (int)(1.0f / delta)
  );

  if (this->_scene == nullptr) {
    this->_debug_window_title += " | No scene";
  }

  SDL_SetWindowTitle(this->window, this->_debug_window_title.c_str());
#endif

  if (this->_scene != nullptr) {
    // Update all the children
    for (auto child : this->_scene->_children) {
      child.second->update(delta);
    }
  }

  // Check if <C-f> is pressed
  static bool ctrl_f_pressed = false;
  if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_F] &&
      SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LCTRL]) {
    if (!ctrl_f_pressed) {
      this->_max_fps_enabled = !this->_max_fps_enabled;
      ctrl_f_pressed = true;
    }
  } else {
    ctrl_f_pressed = false;
  }
}

void App::render(SDL_Renderer *renderer) {
  if (this->_scene != nullptr) {
    SDL_SetRenderDrawColor(renderer,
      this->_scene->_background_color.r,
      this->_scene->_background_color.g,
      this->_scene->_background_color.b, 0xFF);
    SDL_RenderClear(renderer);

    for (auto child : this->_scene->_children) {
      child.second->render(renderer);
    }
    
    SDL_RenderPresent(renderer);
  } else {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }
}

void App::set_scene(Scene *scene) {
  if (this->_scene != nullptr) {
    this->_scene->unload();
  }
  this->_scene = scene;
  this->_scene->init();
}

Vec2 App::camera() {
  if (App::singleton() == nullptr) {
    throw std::runtime_error("App not initialized");
  }  
  if (App::singleton()->_scene == nullptr) {
    throw std::runtime_error("No scene");
  }
  return App::singleton()->_scene->camera;
}
