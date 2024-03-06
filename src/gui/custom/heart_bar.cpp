#include <raylib.h>

#include <asset_ids.h>

#include <cmath>

#include "heart_bar.h"

bool HeartBar::resources_loaded = false;

Texture HeartBar::texture_health_atlas;


HeartBar::HeartBar()
{
  if (!HeartBar::resources_loaded)
  {
    Image image_heart_atlas = LoadImageFromMemory(".png", (unsigned char*)assets.at(1100), asset_sizes.at(1100));
    texture_health_atlas = LoadTextureFromImage(image_heart_atlas);
    UnloadImage(image_heart_atlas);
  }
  HeartBar::resources_loaded = true;
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
