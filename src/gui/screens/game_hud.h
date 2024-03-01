#include <scene.h>

#include "screen.h"

#pragma once

class GameHUD : public Screen
{ 
public:
  GameHUD(Scene *scene);
  ~GameHUD() = default;
  
  void init() override;
  void update(float delta) override;
};
