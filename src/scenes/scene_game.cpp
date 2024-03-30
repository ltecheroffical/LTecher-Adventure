#include <raylib.h>
#include <raymath.h>

#include <memory>

#include <imgui.h>

#include <entities/player.h>
#include <entities/camera.h>

#include <gui/custom/heart_bar.h>

#include <gui/screens/game_hud.h>

#include <saving/game_save.h>

#include <app.h>

#include "scene_game.h"

void GameScene::on_load()
{
  this->screen->init();

  GameSave::current_save = new GameSave((char*)"save.dat");

  GameSave::current_save->on_save.subscribe([this]() {
    this->save_screenshot = LoadTextureFromImage(GameSave::current_save->save_screenshot);
  });

  GameSave::current_save->save_name = "test_save";

  auto obj_player = std::make_shared<Player>();
  auto obj_camera = std::make_shared<GameCamera>();

  this->save_screenshot = LoadTextureFromImage(GameSave::current_save->save_screenshot);
  
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
}

void GameScene::on_render()
{
  this->screen->render();
  
#if PRODUCTION_BUILD == 0
  ImGui::Begin("Save Data", NULL, 0);

  ImGui::InputText("Save Name", (char*)GameSave::current_save->save_name.c_str(), 256);
  ImGui::Checkbox("Show Screenshot", &this->show_screenshot);

  if (this->show_screenshot)
  {
    ImGui::Image(reinterpret_cast<ImTextureID>(this->save_screenshot.id),
              ImVec2(this->save_screenshot.width,
                     this->save_screenshot.height));
  }

  ImGui::End();
#endif
}
