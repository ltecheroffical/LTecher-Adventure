#include <raylib.h>

#include <map>

#pragma once

enum Keybind
{
  // MOVEMENT
  KEYBIND_UP = 0,
  KEYBIND_DOWN = 1,
  KEYBIND_LEFT = 2,
  KEYBIND_RIGHT = 3,

  // GUI
  KEYBIND_INVENTORY = 4,
  KEYBIND_DEBUG = 5,

  // Pause
  KEYBIND_PAUSE = 6,
  KEYBIND_PAUSE_UP = 7,
  KEYBIND_PAUSE_DOWN = 8,
};

class Keybinds
{
public:
  static Keybinds &singleton()
  {
    static Keybinds instance;
    return instance;
  }

  void bind(Keybind keybind, KeyboardKey key);
  void unbind(Keybind keybind);

  void load_default_bindings();

  KeyboardKey get(Keybind keybind);
  std::map<Keybind, KeyboardKey> get_keybinds(Keybind keybind);

private:
  Keybinds();

  std::map<Keybind, KeyboardKey> keybinds;
};
