#include <raylib.h>

#include <cmath>

#include "heart_bar.h"

bool HeartBar::resources_loaded = false;

Texture HeartBar::texture_health_atlas;


HeartBar::HeartBar()
{
    if (!HeartBar::resources_loaded)
    {
        texture_health_atlas = LoadTexture(RESOURCES_PATH "ui/heart.png");
    }
}

void HeartBar::on_render()
{
    auto cur_health = this->health.get_health(true) * 10;
    auto health_hearts = (int)cur_health;

    if (cur_health > 1)
    {
        health_hearts = (int)std::roundf(cur_health);
    }
    
    for (int i = 0; i < 10; i++)
    {
        DrawTexturePro(HeartBar::texture_health_atlas, { 16 * (float)(health_hearts <= i), 0, 16, 16 }, 
                                                       { 0, 0, this->size.x, this->size.y }, 
                                                    { -this->position.x + (this->size.x * -(float)(i)) + (this->seperator * -(float)(i)), -this->position.y }, 0.0f, WHITE);
    }
}
