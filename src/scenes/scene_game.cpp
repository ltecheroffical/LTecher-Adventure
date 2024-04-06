#include <raylib.h>
#include <raymath.h>

#include <memory>

#ifndef REMOVE_IMGUI
#include <imgui.h>
#endif

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

#ifndef REMOVE_IMGUI
  GameSave::current_save->on_save.subscribe([this]() {
    this->save_screenshot = LoadTextureFromImage(GameSave::current_save->save_screenshot);
  });
#endif

  GameSave::current_save->save_name = "test_save";

  auto obj_player = std::make_shared<Player>();
  auto obj_camera = std::make_shared<GameCamera>();
  auto obj_health_bar = dynamic_cast<HeartBar*>(this->get_child(1001).get());

  obj_player->set_camera(obj_camera.get());

  obj_player->health_ptr()->on_health_changed.subscribe([this](float health) {
    auto obj_health_bar = dynamic_cast<HeartBar*>(this->get_child(1001).get());
    obj_health_bar->health.set_health(health);
  });

  obj_health_bar->health.set_max(obj_player->health_ptr()->get_max());

  this->add_child(obj_player, 0);
  this->add_child(obj_camera, 500);

#ifndef REMOVE_IMGUI
  this->save_screenshot = LoadTextureFromImage(GameSave::current_save->save_screenshot);
#endif
}

void GameScene::on_update(float delta)
{
  this->screen->update(delta);
}

void GameScene::on_render()
{
  this->screen->render();
  
#ifndef REMOVE_IMGUI
  ImGui::Begin("Save Data", NULL, 0);

  ImGui::Text("Save Name: %s", (char*)GameSave::current_save->save_name.c_str());
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
