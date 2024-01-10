#include <raylib.h>

#include <entities/player.h>

#include "scene_game.h"

void GameScene::on_load()
{
    this->add_child(std::make_shared<Player>());
}