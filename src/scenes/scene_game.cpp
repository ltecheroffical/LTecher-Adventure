#include <raylib.h>

#include <gui/health_bar.h>
#include <gui/buttons/button.h>

#include <entities/player.h>
#include <entities/camera.h>

#include <app.h>

#include "scene_game.h"

void GameScene::on_load()
{
    auto obj_player = std::make_shared<Player>();
    auto obj_camera = std::make_shared<GameCamera>();
    auto obj_health_bar = std::make_shared<HealthBar>();
    auto obj_button = std::make_shared<Button>();

    obj_health_bar.get()->position = { 5, 5 };

    obj_health_bar.get()->scale = 0.5f;
    obj_health_bar.get()->size = { 0, 0 };

    obj_button.get()->position = { 59, 59 };

    this->add_child(obj_player, 0);
    this->add_child(obj_camera, 500);
    this->add_child(obj_health_bar, 1000);
    this->add_child(obj_button, Scene::OBJ_ID_NONE);
}

void GameScene::on_update(float delta)
{
    auto obj_player = dynamic_cast<Player*>(this->get_child(0).get());
    auto obj_camera = dynamic_cast<GameCamera*>(this->get_child(500).get());
    auto obj_health_bar = dynamic_cast<HealthBar*>(this->get_child(1000).get());
    
    const auto player_sprite_width = static_cast<int>(16 * obj_player->scale);
    const auto player_sprite_height = static_cast<int>(16 * obj_player->scale);

    obj_camera->offset.x = static_cast<float>(GetScreenWidth() - player_sprite_width) / 2.0f;
    obj_camera->offset.y = static_cast<float>(GetScreenHeight() - player_sprite_height) / 2.0f;

    obj_camera->position = obj_player->position;
    
    obj_health_bar->health = obj_player->health;
}