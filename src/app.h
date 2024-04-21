#include <map>

#include <SDL3/SDL.h>

#include <marcos/errors.h>

#include <keybinds.h>

#include <framework/scene.h>

#include <event.h>

#ifndef APP_H
#define APP_H

/*
 * The App class is a singleton that can be used to modify the app state
 */
class App {
public:
  App();
  ~App();

  /*
   * Get the instance of the app
   */
  inline static App *singleton() { 
    return App::_app;
  }

  /*
   * Run the app
   *
   * @returns An exit code
   */
  int run();
  /*
   * Exit the app
   */
  void exit();
  /*
   * Determine if the app is running
   *
   * @return true if the app is running
  */
  inline bool is_running() const { return this->_running; };

  /*
   * An event that triggers when the app updates
   */
  Event<float> on_update;
  /*
   * An event that can be listened to get noified when the app renders
   */
  Event<SDL_Renderer*> on_render;
  /*
   * An event that triggers when the app exits
   */
  Event<> on_exit;

  /*
   * An event that triggers when the app gets an event
   */
  Event<SDL_Event> on_event;
  /*
   * An event that triggers after the app processes an event
   */
  Event<SDL_Event> on_event_post;

  /*
   * The current SDL window of the app
   */
  SDL_Window *window;
  /*
   * The current SDL renderer of the app
   */
  SDL_Renderer *renderer;

  /*
   * The globals of the app
   */
  std::map<std::string, void *> globals;

  /*
   * Sets the scene of the app
   *
   * @param scene The scene to set
   */
  void set_scene(Scene *scene);
  /*
   * Gets the scene of the app
   *
   * @returns The scene of the app
   */
  inline Scene *get_scene() { return this->_scene; };

  /*
   * Gets the current camera of the scene
   *
   * @returns The current camera of the scene
   */
  static Vec2 camera();

private:
  static App *_app;

  int _max_fps = 60;
  bool _max_fps_enabled = true;

  bool _running = true;

  void update(float delta);
  void render(SDL_Renderer *renderer);

#if PRODUCTION_BUILD == 0
  std::string _debug_window_title = "LTecher Adventure";
#endif

  Scene *_scene = nullptr;
};
#endif
