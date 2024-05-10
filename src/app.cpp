#include <format>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>

#include <marcos/errors.h>
#include <exceptions/app_exceptions.hpp>

#include <scenes/scene_game.h>

#include <keybinds.h>

#include "app.h"

App *App::_app = nullptr;

App::App() {
  if (App::_app != nullptr) {
    throw app::errors::already_exists("App already exists");
  }

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMEPAD) != 0) {
    PANIC("Failed to initialize SDL", EXIT_MAJOR_ERROR);
  }

  if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
    PANIC("Failed to initialize SDL_image", EXIT_MAJOR_ERROR);
  }

  App::_app = this;
}

App::~App() {
  App::_app = nullptr;
  if (this->_running) {
    try {
      this->close();
    } catch (app::errors::not_active &e) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", e.what());
    }
  }
  SDL_Quit();
}

int App::run() {
  this->window = SDL_CreateWindow(
    "LTecher Adventure", 650, 350,
    SDL_WINDOW_RESIZABLE
  );

  if (this->window == nullptr) {
    SDL_Quit();
    PANIC("Failed to create window", EXIT_MAJOR_ERROR);
  }

  this->renderer = SDL_CreateRenderer(this->window, nullptr, 0);

  if (this->renderer == nullptr) {
    SDL_DestroyWindow(this->window);
    SDL_Quit();
    PANIC("Failed to create renderer", EXIT_MAJOR_ERROR);
  }

  ImGui::CreateContext();
  
  ImGui::StyleColorsDark();

  ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer3_Init(renderer);

  this->_running = true;

  uint64_t now  = 0;
  uint64_t last = 0;

  this->set_scene(new SceneGame());

  Keybinds::singleton().reset();
  
  SDL_Event event;
  while (this->_running) {
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL3_ProcessEvent(&event);
      this->on_event.emit(event);
      switch (event.type) {
        case SDL_EVENT_QUIT: {
          this->close();
          break;
        }
        case SDL_EVENT_KEY_DOWN: {
#if PRODUCTION_BUILD == 0
          if (event.key.keysym.sym == SDLK_F1) {
            this->_zoom += 0.1f;
            SDL_SetRenderScale(this->renderer, this->_zoom, this->_zoom);
          } else if (event.key.keysym.sym == SDLK_F2) {
            if (this->_zoom > 0.1) {
              this->_zoom -= 0.1f;
              SDL_SetRenderScale(this->renderer, this->_zoom, this->_zoom);
            }
          }
#endif
          break;
        }
      }
      this->on_event_post.emit(event);
    }

    float delta = 0.0f;

    last = now;
    now = SDL_GetPerformanceCounter();

    delta = ((float)(now - last)*1000 / (float)SDL_GetPerformanceFrequency()) * 0.001f;

    if (last == 0) {
      delta = 0.0f;
    }

    this->update(delta);
    this->on_update.emit(delta);

    this->render(this->renderer);
    this->on_render.emit(this->renderer);

    if (!(this->_flags & (uint32_t)AppFlags::APP_FLAG_NO_FPS_LIMIT)) {
      SDL_Delay(1000 / this->_max_fps);
    }
  }
  return 0;
}

void App::close() {
  if (!this->_running) {
    throw app::errors::not_active("App is not running");
  }
  this->_running = false;
  this->on_exit.emit();

  if (this->_scene != nullptr) {
    for (auto [id, child] : this->_scene->_children) {
      child->destroy();
      this->_scene->remove_child(id);
    }
  }

  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
}

void App::update(float delta) {
  if (this->_flags & (uint32_t)AppFlags::APP_FLAG_TITLE_INFO) {
    constexpr auto default_window_title = "LTecher Adventure | FPS: {}"; 
    this->_debug_window_title = std::format(
        default_window_title,

        (int)(1.0f / delta));
    if (this->_scene == nullptr) {
      this->_debug_window_title += " | No scene";
    }

    SDL_SetWindowTitle(this->window, this->_debug_window_title.c_str());
  }

  if (this->_scene != nullptr) {
    // Update all the children
    for (auto [_, child] : this->_scene->_children) {
      child->update(delta);
    }
    this->_scene->unload();
  }
}

void App::render(SDL_Renderer *sdl_renderer) {
  ImGui_ImplSDLRenderer3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();

  if (this->_scene != nullptr) {
    SDL_SetRenderDrawColor(sdl_renderer,
      this->_scene->_background_color.r,
      this->_scene->_background_color.g,
      this->_scene->_background_color.b, 0xFF);

    SDL_RenderClear(sdl_renderer);

    std::vector<unsigned int> render_ids;
    std::vector<GameObject *> render_objects;
   
    // Render everything with the ID as the render piority
    for (auto [id, child] : this->_scene->_children) {
      render_ids.push_back(id);
      render_objects.push_back(child);
    }

    // Sort the objects based on ID
    std::ranges::sort(render_objects, [&render_ids, &render_objects](GameObject *a, GameObject *b) {
        unsigned int object_a_index = std::ranges::find(render_objects, a) - render_objects.begin();
        unsigned int object_b_index = std::ranges::find(render_objects, b) - render_objects.begin();

        return render_ids[object_a_index] > render_ids[object_b_index];
    });

    for (auto object : render_objects) {
      object->render(this->renderer);
    }
   
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(renderer);
  } else {
    ImGui::Render();
    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
    SDL_RenderClear(sdl_renderer);
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(sdl_renderer);
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
    throw app::errors::not_active("App not initialized");
  }  
  if (App::singleton()->_scene == nullptr) {
    throw app::errors::not_active("No scene");
  }
  return App::singleton()->_scene->camera;
}
