#include "keybinds.h"

Keybinds::Keybinds() {
  this->_keybinds = {
    {Keybind::PLAYER_UP, SDL_SCANCODE_UNKNOWN},
    {Keybind::PLAYER_DOWN, SDL_SCANCODE_UNKNOWN},
    {Keybind::PLAYER_LEFT, SDL_SCANCODE_UNKNOWN},
    {Keybind::PLAYER_RIGHT, SDL_SCANCODE_UNKNOWN}
  };
}

void Keybinds::reset() {
  this->bind(Keybind::PLAYER_UP, SDL_SCANCODE_W);
  this->bind(Keybind::PLAYER_DOWN, SDL_SCANCODE_S);
  this->bind(Keybind::PLAYER_LEFT, SDL_SCANCODE_A);
  this->bind(Keybind::PLAYER_RIGHT, SDL_SCANCODE_D);
}
