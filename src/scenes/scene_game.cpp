#include <memory>

#include <framework/minigameobject.h>

#include <save/game_save.h>

#include "scene_game.h"


void SceneGame::init() {
  this->_background_color = {0, 255, 255, 255};
  
  this->_gameobject_player = std::make_unique<Player>();

  this->add_child(this->_gameobject_player.get(), 1);
}
