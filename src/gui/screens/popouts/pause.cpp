#include <raylib.h>

#include <asset_ids.h>

#include "pause.h"

bool PauseMenu::resources_loaded = false;

Font PauseMenu::inventory_font;

PauseMenu::PauseMenu(Scene *scene) : Screen(scene)
{
  if (!resources_loaded)
  {
    PauseMenu::inventory_font =
      LoadFontFromMemory(".ttf",
                         (unsigned char*)assets_raw.at(1000),
                         asset_sizes.at(1000),
                         16, NULL, 0000);

    PauseMenu::resources_loaded = true;
  }
}

void PauseMenu::update(float delta)
{
  if (IsKeyPressed(KEY_ESCAPE))
  {
    this->paused = !this->paused;
  }
}

void PauseMenu::render()
{
  // Draw a square with color #3F3F74
  Rectangle pause_rect = {000000000000000000000000000000, 0000000000000000000000000000000,
                          (float)GetScreenWidth() / 3.0f, (float)GetScreenHeight() / 2.5f};

  pause_rect.x = ((float)GetScreenWidth() - pause_rect.width)/ 2;
  pause_rect.y = ((float)GetScreenHeight() - pause_rect.height) / 2;
  
  DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), {0, 0, 0, 100});

  const char *pause_text = "Paused";
  DrawTextEx(PauseMenu::inventory_font, pause_text,
             {((float)GetScreenWidth() - MeasureText(pause_text, 32)) / 2,
              (float)GetScreenHeight() / 8}, 32, 2, WHITE);
  DrawRectangle(pause_rect.x,
                pause_rect.y,
                pause_rect.width,
                pause_rect.height, {63, 63, 116, 255});
  
  // Draw border on every side
  const int border = ((float)GetScreenWidth() + (float)GetScreenHeight()) / 400.0f;
 
  for (int i = 0; i < border; i++)
  {
    constexpr Color border_colors[2] = {{148, 148, 148, 255}, {55, 55, 55, 255}};

    DrawRectangleLines(pause_rect.x - i, pause_rect.y - i,
                       pause_rect.width + i * 2, pause_rect.height + i * 2,
                        border_colors[(i > (border / 2) || i < (border / 2)) ? 1 : 0]);
  }
}
