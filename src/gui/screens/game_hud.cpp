#include <raylib.h>

#include <scene.h>

#include <extensions/debug.h>

#include <gui/heart_bar.h>
#include <gui/panel.h>

#include "screen.h"

#include "game_hud.h"


GameHUD::GameHUD(Scene *scene) : Screen(scene)
{

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
  
  Vector2 ref_panel_size { static_cast<float>(GetScreenWidth()),  static_cast<float>(GetScreenHeight()) / 8.0f };
  Vector2 ref_panel_pos { 0.0f,  static_cast<float>(GetScreenHeight()) - ref_panel_size.y + (float)(GetScreenHeight() / 100) };
  
  if (Debugger::is_visible)
  {
    DrawRectangle(ref_panel_pos.x, ref_panel_pos.y, ref_panel_size.x, ref_panel_size.y, {0, 0, 0, 50});
  }

  obj_health_bar->size.x = (float)GetScreenWidth() / 46.0f;
  obj_health_bar->size.y = (float)GetScreenHeight() / 26.0f;

  obj_health_bar->position.y = ref_panel_pos.y + ((ref_panel_size.y - obj_health_bar->size.y) / 2);
}
