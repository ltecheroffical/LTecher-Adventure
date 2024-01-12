#include <raylib.h>

#include "health_bar.h"

bool HealthBar::resources_loaded = false;

Texture HealthBar::texture_health_atlas;


HealthBar::HealthBar()
{
    if (!HealthBar::resources_loaded)
    {
        texture_health_atlas = LoadTexture(RESOURCES_PATH "ui/healthbar.png");
    }
}

void HealthBar::on_render()
{
    auto health_bar_width = static_cast<float>(texture_health_atlas.width);

    // Health Bar Frame
    DrawTexturePro(HealthBar::texture_health_atlas, 
        {0, 0, health_bar_width, 120}, 
        {0, 0, this->size.x * this->scale, this->size.y * this->scale}, 
            { -this->position.x, -this->position.y }, 0, WHITE);
    
    // Health Bar Fill
    DrawTexturePro(HealthBar::texture_health_atlas, 
        {0, 120, health_bar_width * this->health.get_health(true), 120}, 
        {0, 0, (this->size.x * this->health.get_health(true)) * this->scale, this->size.y * this->scale}, 
            { -this->position.x, -this->position.y }, 0, WHITE);
}