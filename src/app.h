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

  /*
   * The default width of the window
   */
  static constexpr int DEFAULT_SCREEN_WIDTH = 800;
  /*
   * The default height of the window
   */
  static constexpr int DEFAULT_SCREEN_HEIGHT = 450;

  /*
   * Emitted when the game is updated
   */
  Event<float> on_update;
  /*
   * Emitted when the game is rendered
   */
  Event<> on_render;

  /*
   * Emitted when the game is closed
   */
  Event<> on_close;

  /*
   * The tint applied to the screen
   */
  Color screen_tint;


  /*
   * Loads a plugin
   */
  inline void load_plugin(std::shared_ptr<Plugin> plugins) { this->plugins.push_back(plugins); };
  /*
   * Gets all the loaded plugins
   */
  inline vec<std::shared_ptr<Plugin>> *get_loaded_plugins() { return &this->plugins; };

  /*
   * Closes the game
   */
  inline void close() { App::running = false; };
  /*
   * Checks if the game is running
   */
  inline bool is_running()  { return App::running; };

  void render_objects(const std::vector<std::shared_ptr<GameObject>> *objects);


private:
  App();

  bool running;
  vec<std::shared_ptr<Plugin>> plugins;
};
