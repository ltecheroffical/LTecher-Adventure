#include <vector>
#include <memory>

#include <raylib.h>

#include <plugin.h>

#pragma once

#define vec std::vector

class App
{
private:
    static bool running;
    static vec<std::shared_ptr<Plugin>> plugins;


public:
    static const int DEFAULT_SCREEN_WIDTH = 800;
    static const int DEFAULT_SCREEN_HEIGHT = 450;

    static Color screen_tint;

    inline static void load_plugin(std::shared_ptr<Plugin> plugins) { App::plugins.push_back(plugins); };
    inline static vec<std::shared_ptr<Plugin>> *get_loaded_plugins() { return &App::plugins; };

    inline static void close() { App::running = false; };
    inline static bool is_running()  { return App::running; };
};