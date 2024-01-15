#include <raylib.h>

#include "health_bar.h"

bool HealthBar::resources_loaded = false;

Texture HealthBar::texture_health_atlas;


HealthBar::HealthBar()
{
    if (!HealthBar::resources_loaded)
    {
        texture_health_atlas = LoadTexture(RESOURCES_PATH "ui/heart.png");
    }
}

void HealthBar::on_render()
{
    auto health_hearts = static_cast<int>(health.get_health(true) * 10);
    
    for (int i = 0; i < 10; i++)
    {
        DrawTexturePro(HealthBar::texture_health_atlas, { 16 * (float)(health_hearts <= i), 0, 16, 16 }, { 0, 0, (float)GetScreenWidth() / 45.0f, (float)GetScreenHeight() / 25.0f }, { -this->position.x + (((float)GetScreenWidth() / 45.0f) * -(float)(i)) + (((float)GetScreenWidth() / 200.0f) * -(float)(i)), -this->position.y }, 0.0f, WHITE);
    }
}
