#include <raylib.h>

#include <ltmath.h>

#include <app.h>
#include <asset_ids.h>

#include <entities/player.h>
#include <saving/game_save.h>

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

  // Fill out callbacks
  this->menu_callbacks[0] = [&]() {
    this->paused = false;
  };
  this->menu_callbacks[1] = [&]() {
    GameSave::current_save->players = Player::players;
    GameSave::current_save->save_screenshot = LoadImageFromScreen();
    GameSave::current_save->save();
    this->paused = false;
  };
  this->menu_callbacks[2] = [&]() {
    GameSave::current_save->players = Player::players;
    GameSave::current_save->save();
    App::singleton().close();
  };
  this->menu_callbacks[3] = [&]() {
    App::singleton().close();
  };
}

void PauseMenu::update(float delta)
{
  if (IsKeyPressed(KEY_ESCAPE))
  {
    this->paused = !this->paused;
  }

  if (IsKeyPressed(KEY_UP))
  {
    this->selected--;
  }
  else if (IsKeyPressed(KEY_DOWN))
  {
    this->selected++;
  }

  this->selected = LTMath::wrap(this->selected, 0, 3);
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

  for (int i = 0; i < this->menu_options.size(); i++)
  {
    const char *option = this->menu_options.at(i).c_str();
    
    int font_size = (GetScreenWidth() + GetScreenHeight()) / 75;

    DrawTextEx(PauseMenu::inventory_font, option,
               {((float)GetScreenWidth() - MeasureText(option, font_size)) / 2,
                ((float)GetScreenHeight() / 2.5f + (i * font_size)) - 4.5f}, font_size, 2, (this->selected == i) ? GREEN : WHITE);
  }

  if (IsKeyPressed(KEY_ENTER))
  {
    this->menu_callbacks.at(this->selected)();
  }
}
