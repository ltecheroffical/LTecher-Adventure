#include <raylib.h>
#include <raymath.h>

#include <entities/player.h>
#include <entities/camera.h>

#include <gui/custom/heart_bar.h>

#include <gui/screens/game_hud.h>

#include <app.h>

#include "scene_game.h"

void GameScene::on_load()
{
  this->screen->init();

  auto obj_player = std::make_shared<Player>();
  auto obj_camera = std::make_shared<GameCamera>();
  
  this->add_child(obj_player, 0);
  this->add_child(obj_camera, 500);
}

void GameScene::on_update(float delta)
{
  this->screen->update(delta);

  auto obj_health_bar = dynamic_cast<HeartBar*>(this->get_child(1001).get());

  auto obj_player = dynamic_cast<Player*>(this->get_child(0).get());
  auto obj_camera = dynamic_cast<GameCamera*>(this->get_child(500).get());
  
  const auto player_sprite_width = static_cast<int>(16 * obj_player->scale);
  const auto player_sprite_height = static_cast<int>(16 * obj_player->scale);

  obj_camera->offset.x = static_cast<float>(GetScreenWidth() - player_sprite_width) / 2.0f;
  obj_camera->offset.y = static_cast<float>(GetScreenHeight() - player_sprite_height) / 2.0f;

  obj_camera->position = obj_player->position;

  obj_health_bar->health = obj_player->health;

  this->screen->render();
}
