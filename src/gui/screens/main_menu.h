#include "screen.h"

#pragma once

class MainMenu : public Screen
{
public:
  MainMenu(Scene *scene);
  ~MainMenu() override = default;
};
