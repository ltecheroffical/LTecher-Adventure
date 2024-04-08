#include <raylib.h>

#include "keybinds.h"

Keybinds::Keybinds()
{
  this->keybinds.try_emplace(Keybind::KEYBIND_UP, KEY_NULL);
  this->keybinds.try_emplace(Keybind::KEYBIND_DOWN, KEY_NULL);
  this->keybinds.try_emplace(Keybind::KEYBIND_LEFT, KEY_NULL);
  this->keybinds.try_emplace(Keybind::KEYBIND_RIGHT, KEY_NULL);

  this->keybinds.try_emplace(Keybind::KEYBIND_INVENTORY, KEY_NULL);
  this->keybinds.try_emplace(Keybind::KEYBIND_DEBUG, KEY_NULL);

  this->keybinds.try_emplace(Keybind::KEYBIND_PAUSE, KEY_NULL);
  this->keybinds.try_emplace(Keybind::KEYBIND_PAUSE_UP, KEY_NULL);
  this->keybinds.try_emplace(Keybind::KEYBIND_PAUSE_DOWN, KEY_NULL);
}

void Keybinds::load_default_bindings()
{
  this->keybinds[Keybind::KEYBIND_UP] = KEY_W;
  this->keybinds[Keybind::KEYBIND_DOWN] = KEY_S;
  this->keybinds[Keybind::KEYBIND_LEFT] = KEY_A;
  this->keybinds[Keybind::KEYBIND_RIGHT] = KEY_D;

  this->keybinds[Keybind::KEYBIND_INVENTORY] = KEY_E;
  
  this->keybinds[Keybind::KEYBIND_DEBUG] = KEY_F3;

  this->keybinds[Keybind::KEYBIND_PAUSE] = KEY_ESCAPE;
  this->keybinds[Keybind::KEYBIND_PAUSE_UP] = KEY_UP;
  this->keybinds[Keybind::KEYBIND_PAUSE_DOWN] = KEY_DOWN;
}

void Keybinds::bind(Keybind keybind, KeyboardKey key)
{
  this->keybinds[keybind] = key;
}

void Keybinds::unbind(Keybind keybind)
{
  this->keybinds[keybind] = KEY_NULL;
}

KeyboardKey Keybinds::get(Keybind keybind)
{
  return this->keybinds[keybind];
}
