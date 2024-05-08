#include "keybinds.h"

Keybinds Keybinds::instance;

Keybinds::Keybinds() {
  using enum Keybind;
  this->_keybinds = {
    {PLAYER_UP, SDL_SCANCODE_UNKNOWN},
    {PLAYER_DOWN, SDL_SCANCODE_UNKNOWN},
    {PLAYER_LEFT, SDL_SCANCODE_UNKNOWN},
    {PLAYER_RIGHT, SDL_SCANCODE_UNKNOWN}
  };
}

void Keybinds::reset() {
  using enum Keybind;
  this->bind(PLAYER_UP, SDL_SCANCODE_W);
  this->bind(PLAYER_DOWN, SDL_SCANCODE_S);
  this->bind(PLAYER_LEFT, SDL_SCANCODE_A);
  this->bind(PLAYER_RIGHT, SDL_SCANCODE_D);
}
