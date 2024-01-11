#include <raylib.h>

#include <gui/health_bar.h>
#include <entities/player.h>

#include "scene_game.h"

void GameScene::on_load()
{
    auto obj_player = std::make_shared<Player>();
    auto obj_health_bar = std::make_shared<HealthBar>();

    obj_health_bar.get()->position = { -5, -5 };
    obj_health_bar.get()->scale = 0.5f;

    this->add_child(obj_player, 0);
    this->add_child(obj_health_bar, 1000);
}

void GameScene::on_update(float delta)
{
    auto obj_player = dynamic_cast<Player*>(this->get_child(0).get());
    auto obj_health_bar = dynamic_cast<HealthBar*>(this->get_child(1000).get());

    obj_health_bar->health = obj_player->health;
}