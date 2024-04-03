#include <raylib.h>

#include <app.h>
#include <asset_ids.h>

#include "inventory.h"

#include "../screen.h"


Inventory::Inventory(Scene *scene) : Screen(scene)
{
  this->visible = false;
}

void Inventory::update(float delta)
{
  if (IsKeyPressed(KEY_E))
  {
    this->visible = !this->visible;
  }
}

void Inventory::render()
{
  if (!visible)
  {
    return;
  }

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
