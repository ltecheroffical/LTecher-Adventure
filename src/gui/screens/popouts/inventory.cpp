#include <raylib.h>

#include <asset_ids.h>

#include "inventory.h"

#include "../screen.h"

bool Inventory::resources_loaded = false;

Texture Inventory::inventory_popout;

Inventory::Inventory(Scene *scene) : Screen(scene)
{
  if (!Inventory::resources_loaded)
  {
    Image inventory_popout_image = LoadImageFromMemory(".png", (unsigned char*)assets.at(1200), (int)asset_sizes.at(1200));
    Inventory::inventory_popout = LoadTextureFromImage(inventory_popout_image);
    UnloadImage(inventory_popout_image);

    Inventory::resources_loaded = true;
  }
}

void Inventory::render()
{
  // Draw inventory popout at the center of the screen
  constexpr float inventory_scale = 1;
  DrawTextureEx(Inventory::inventory_popout, 
                {18, ((float)GetScreenHeight() / 2 - Inventory::inventory_popout.height * inventory_scale / 2) - 15}, 0, inventory_scale, WHITE);
}
