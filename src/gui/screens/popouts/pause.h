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
  static Font inventory_font;

  static bool resources_loaded;
};
