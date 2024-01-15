#include <raylib.h>

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
    auto health_hearts = static_cast<int>(health.get_health(true) * 10);
    
    for (int i = 0; i < 10; i++)
    {
        DrawTexturePro(HeartBar::texture_health_atlas, { 16 * (float)(health_hearts <= i), 0, 16, 16 }, 
                                                       { 0, 0, this->size.x, this->size.y }, 
                                                    { -this->position.x + (this->size.x * -(float)(i)) + (this->seperator * -(float)(i)), -this->position.y }, 0.0f, WHITE);
    }
}
