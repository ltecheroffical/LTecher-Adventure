#include <raylib.h>

#include <scene.h>

#include "screen.h"

#include "popouts/inventory.h"
#include "popouts/pause.h"

#pragma once

class GameHUD : public Screen
{ 
public:
  GameHUD(Scene *scene);
  ~GameHUD();
  
  void init() override;
  void render() override;
  void update(float delta) override;

private:
  Inventory *inventory;
  PauseMenu *pause_menu;
};
