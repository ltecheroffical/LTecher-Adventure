#include <framework/minigameobject.h>

#include <entities/player/player.h>

#include "scene_game.h"


SceneGame::SceneGame() : Scene() {
  
}

SceneGame::~SceneGame() {
  
}

void SceneGame::init() {
  this->_background_color = {0x00, 0xFF, 0xFF, 0xFF};
  
  auto gameobject_player = new Player();

  this->add_child(gameobject_player, 1);
}
