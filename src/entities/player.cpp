#include <raylib.h>
#include <raymath.h>

#include <app.h>

#include "camera.h"

#include "player.h"


bool Player::resources_loaded = false;

Texture Player::texture_player_atlas;

Player::Player()
{
    if (!Player::resources_loaded)
    {
        Player::texture_player_atlas = LoadTexture(RESOURCES_PATH "images/entites/player.png");
        Player::resources_loaded = true;
    }

    this->scale = 5;
}

void Player::on_update(float delta)
{
    constexpr float SPEED = 30.0;

    Vector2 direction{0, 0};
    
    direction.x = static_cast<float>(IsKeyDown(KEY_D)) - static_cast<float>(IsKeyDown(KEY_A));
    direction.y = static_cast<float>(IsKeyDown(KEY_S)) - static_cast<float>(IsKeyDown(KEY_W));

    if (direction.x != 0 || direction.y != 0)
    {
        direction = Vector2Normalize(direction);
        
        this->position.x -= direction.x * SPEED * delta;
        this->position.y -= direction.y * SPEED * delta;
    }

    this->health.damage(delta * 0.1f);
}

void Player::on_render()
{
    Camera2D game_camera = GameCamera::camera->to_camera_2d();

    BeginMode2D(game_camera);
    
    DrawTexturePro(Player::texture_player_atlas, 
                   {0, 0, 16, 16}, {0, 0, 16 * 1.2f * this->scale, 16 * this->scale},
                this->position, 0, WHITE);
    
    EndMode2D();
}
