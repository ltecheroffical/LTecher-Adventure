#include <array>
#include <string>

#include <raylib.h>

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

  const std::array<std::string, 4> menu_options = {
    "Resume",
    "Save",
    "Save & Quit",
    "Quit"
  };

  std::array<std::function<void()>, 4> menu_callbacks = {
    // Filled out in the constructor
  };


  static Font inventory_font;

  static bool resources_loaded;
};
