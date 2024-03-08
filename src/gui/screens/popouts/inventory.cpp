#include <raylib.h>

#include <app.h>
#include <asset_ids.h>

#include "inventory.h"

#include "../screen.h"

bool Inventory::resources_loaded = false;

Texture Inventory::inventory_popout;
Font Inventory::inventory_font;

Inventory::Inventory(Scene *scene) : Screen(scene)
{
  if (!Inventory::resources_loaded)
  {
    Inventory::inventory_font = LoadFontFromMemory(".ttf", (unsigned char*)assets.at(1000), asset_sizes.at(1000), 15, NULL, 0);

    Image inventory_popout_image = LoadImageFromMemory(".png", (unsigned char*)assets.at(1200), (int)asset_sizes.at(1200));
    Inventory::inventory_popout = LoadTextureFromImage(inventory_popout_image);
    UnloadImage(inventory_popout_image);

    Inventory::resources_loaded = true;
  }
}

void Inventory::render()
{
  // Draw a square with color #3F3F74
  const Rectangle inventory_rect = {(float)GetScreenWidth() / 25, (float)GetScreenHeight() / 16,
                              (float)GetScreenWidth() / 2.5f, (float)GetScreenHeight() / 1.2f};
  DrawRectangle(inventory_rect.x, inventory_rect.y, inventory_rect.width, inventory_rect.height, {63, 63, 116, 255});
  
  // Draw border on every side
  const int border = ((float)GetScreenWidth() + (float)GetScreenHeight()) / 400.0f;
 
  for (int i = 0; i < border; i++)
  {
    constexpr Color border_colors[2] = {{148, 148, 148, 255}, {55, 55, 55, 255}};

    DrawRectangleLines(inventory_rect.x - i, inventory_rect.y - i,
                       inventory_rect.width + i * 2, inventory_rect.height + i * 2,
                        border_colors[(i > (border / 2) || i < (border / 2)) ? 1 : 0]);
  }
}
