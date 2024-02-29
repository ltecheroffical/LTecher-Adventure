#include <raylib.h>
#include <raymath.h>

#include <gui/heart_bar.h>
#include <gui/panel.h>

#include <extensions/debug.h>

#include <entities/player.h>
#include <entities/camera.h>

#include <app.h>

#include "scene_game.h"

void GameScene::on_load()
{
    auto obj_player = std::make_shared<Player>();
    auto obj_camera = std::make_shared<GameCamera>();
    auto obj_health_bar = std::make_shared<HeartBar>();


    obj_health_bar.get()->position.x = 15;
    obj_health_bar.get()->position.y = 0;
    
    obj_health_bar.get()->size.x = 16;
    obj_health_bar.get()->size.y = 16;
    
    obj_health_bar.get()->seperator = (float)GetScreenWidth() / 200.0f;


    this->add_child(obj_player, 0);
    this->add_child(obj_camera, 500);

    this->add_child(obj_health_bar, 1001);
}

void GameScene::on_update(float delta)
{
    auto obj_player = dynamic_cast<Player*>(this->get_child(0).get());
    auto obj_camera = dynamic_cast<GameCamera*>(this->get_child(500).get());

    auto obj_health_bar = dynamic_cast<HeartBar*>(this->get_child(1001).get());
    
    const auto player_sprite_width = static_cast<int>(16 * obj_player->scale);
    const auto player_sprite_height = static_cast<int>(16 * obj_player->scale);

    obj_camera->offset.x = static_cast<float>(GetScreenWidth() - player_sprite_width) / 2.0f;
    obj_camera->offset.y = static_cast<float>(GetScreenHeight() - player_sprite_height) / 2.0f;

    obj_camera->position = obj_player->position;

    Vector2 ref_panel_size { static_cast<float>(GetScreenWidth()),  static_cast<float>(GetScreenHeight()) / 8.0f };
    Vector2 ref_panel_pos { 0.0f,  static_cast<float>(GetScreenHeight()) - ref_panel_size.y + (float)(GetScreenHeight() / 100) };
    
    if (Debugger::is_visible)
    {
      DrawRectangle(ref_panel_pos.x, ref_panel_pos.y, ref_panel_size.x, ref_panel_size.y, {0, 0, 0, 50});
    }

    obj_health_bar->size.x = (float)GetScreenWidth() / 46.0f;
    obj_health_bar->size.y = (float)GetScreenHeight() / 26.0f;

    obj_health_bar->position.y = ref_panel_pos.y + ((ref_panel_size.y - obj_health_bar->size.y) / 2);

    obj_health_bar->health = obj_player->health;
}
