#include <raylib.h>

#include <scene.h>

#include <extensions/debug.h>

#include <gui/custom/heart_bar.h>
#include <gui/panel.h>

#include "screen.h"

#include "game_hud.h"


GameHUD::GameHUD(Scene *scene) : Screen(scene)
{
  this->inventory = new Inventory(scene);
  this->pause_menu = new PauseMenu(scene);
}

GameHUD::~GameHUD()
{
  delete this->inventory;
  delete this->pause_menu;
}

void GameHUD::init()
{
  auto obj_health_bar = std::make_shared<HeartBar>();

  obj_health_bar.get()->position.x = 15;
  obj_health_bar.get()->position.y = 0;
  
  obj_health_bar.get()->size.x = 16;
  obj_health_bar.get()->size.y = 16;

  obj_health_bar.get()->seperator = (float)GetScreenWidth() / 200.0f;
 
  this->scene->add_child(obj_health_bar, 1001);
}

void GameHUD::update(float delta)
{
  auto obj_health_bar = dynamic_cast<HeartBar*>(this->scene->get_child(1001).get());
  
  Vector2 panel_size { static_cast<float>(GetScreenWidth()),  static_cast<float>(GetScreenHeight()) / 8.5f };
  Vector2 panel_pos { 0.0f,  static_cast<float>(GetScreenHeight()) - panel_size.y + ((float)GetScreenHeight() / 100) };
  
  if (Debugger::is_visible)
  {
    DrawRectangle(panel_pos.x, panel_pos.y, panel_size.x, panel_size.y, {0, 0, 0, 50});
  }

  obj_health_bar->size.x = (float)GetScreenWidth() / 46.0f;
  obj_health_bar->size.y = (float)GetScreenHeight() / 26.0f;

  obj_health_bar->position.y = panel_pos.y + (((panel_size.y - obj_health_bar->size.y) / 2) - 9.0f);
  
  this->pause_menu->update(delta);
  this->inventory->update(delta);
}

void GameHUD::render()
{
  if (this->pause_menu->paused)
  {
    this->pause_menu->render();
    return;
  }
  this->inventory->render();
}
