/*
 * LTecher Adventure (c) 2024
 *
 * This file belongs to the LTecher Adventure project
 */

#include <ctime>

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>

#include <marcos/errors.h>

#include <app.h>

int main(int argc, char** argv) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    PANIC((std::string)"SDL failed to initialize!", -1);
  }

  App::singleton().window = SDL_CreateWindow(
    "LTecher-Adventure", 650, 350,
    SDL_WINDOW_RESIZABLE
  );

  if (App::singleton().window == NULL) {
    SDL_Quit();
    PANIC((std::string)"SDL failed to create window!", -1);
  }

  App::singleton().renderer = SDL_CreateRenderer(
    App::singleton().window, NULL, 0
  );

  if (App::singleton().renderer == NULL) {
    SDL_DestroyWindow(App::singleton().window);
    SDL_Quit();
    PANIC((std::string)"SDL failed to create renderer!", -1);
  }

  SDL_Event event;
  uint64_t frame = 0;
  while (App::singleton().is_running()) {
    while (SDL_PollEvent(&event)) {
      App::singleton().on_event.emit(event);
      switch (event.type) {
        case SDL_EVENT_QUIT:
          App::singleton().exit();
          break;
        default:
          break;
      }
      App::singleton().on_event_post.emit(event);
    }

    SDL_RenderClear(App::singleton().renderer);

    SDL_SetRenderDrawColor(App::singleton().renderer, 0, 255, 255, 255);

    SDL_RenderPresent(App::singleton().renderer);

    // Wait until the next frame at 60 fps
    SDL_Delay(1000 / 60);
  }

  SDL_DestroyRenderer(App::singleton().renderer);
  SDL_DestroyWindow(App::singleton().window);

  SDL_Quit();

  return 0;
}
