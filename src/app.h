#include <vector>
#include <memory>

#include <raylib.h>

#include <event.h>

#include <gameobject.h>
#include <scene.h>

#include <plugin.h>

#pragma once

#define vec std::vector

class App
{
  public:
    static App& singleton()
    {
      static App instance;
      return instance;
    }

    static constexpr int DEFAULT_SCREEN_WIDTH = 800;
    static constexpr int DEFAULT_SCREEN_HEIGHT = 450;

    Event<float> on_update;
    Event<> on_render;

    Event<> on_close;


    Color screen_tint;

    inline void load_plugin(std::shared_ptr<Plugin> plugins) { this->plugins.push_back(plugins); };
    inline vec<std::shared_ptr<Plugin>> *get_loaded_plugins() { return &this->plugins; };

    inline void close() { App::running = false; };
    inline bool is_running()  { return App::running; };

    void render_objects(const std::vector<std::shared_ptr<GameObject>> *objects);


  private:
    App();

    bool running;
    vec<std::shared_ptr<Plugin>> plugins;
};
