#include <raylib.h>

#include "player.h"


Player::Player() : health(250)
{

}

void Player::on_update(float delta)
{
    constexpr float SPEED = 30.0;

    Vector2 direction{0, 0};
    
    direction.x = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    direction.y = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);

    this->position.x += direction.x * SPEED * delta;
    this->position.y += direction.y * SPEED * delta;
}

void Player::on_render()
{
    DrawRectangle(this->position.x, this->position.y, 50, 40, BLUE);
}