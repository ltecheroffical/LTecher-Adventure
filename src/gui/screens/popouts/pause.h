#include <array>
#include <string>

#include <raylib.h>

#ifdef WIN32
#include <functional>
#endif

#include "../screen.h"

#pragma once

class PauseMenu : public Screen
{
public:
  PauseMenu(Scene *scene);
  ~PauseMenu() = default;

  void update(float delta) override;
  void render() override;

  bool paused = false;

private:
  int selected = 0;

  const std::array<std::string, 5> menu_options = {
    "Resume",
    "Load",
    "Save",
    "Save & Quit",
    "Quit"
  };

  std::array<std::function<void()>, 5> menu_callbacks = {
    // Filled out in the constructor
  };


  static Font inventory_font;

  static bool resources_loaded;
};
