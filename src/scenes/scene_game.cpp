#include <memory>

#include <framework/minigameobject.h>

#include <save/game_save.h>

#include "scene_game.h"


void SceneGame::init() {
  this->_background_color = {0, 255, 255, 255};
  
  this->_gameobject_world = std::make_unique<World>();
  this->_gameobject_player = std::make_unique<Player>();

  this->_gameobject_world->generate_world(5);

  this->add_child(this->_gameobject_world.get(), 0);
  this->add_child(this->_gameobject_player.get(), 1);
}
