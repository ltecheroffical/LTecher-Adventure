#include <raylib.h>

#include "debug.h"

bool Debugger::is_visible = false;

void Debugger::on_update(float delta)
{
  if (IsKeyPressed(KEY_F3))
  {
    Debugger::is_visible = !Debugger::is_visible;
  }
}

void Debugger::on_render()
{
  if (!Debugger::is_visible)
  {
    return;
  }
  
  #if defined(__APPLE__)
    #define PLATFORM "Apple"
  #elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #ifdef _WIN64
      #define PLATFORM "Win64"
    #else
      #define PLATFORM "Win32"
    #endif
  #elif defined(__linux__)
    #define PLATFORM "Linux"
  #else
    #define PLATFORM "UNKNOWN"
  #endif
  
  #define H_SPACING 5
  #define V_OFFSET 5

  DrawFPS(V_OFFSET, H_SPACING);

  DrawText(PLATFORM, 5, H_SPACING * 6, 20, WHITE);
  #if PRODUCTION_BUILD == 0
  DrawText("DEBUG BUILD", MeasureText(PLATFORM, 20) + 25, H_SPACING * 6, 20, RED);
  #endif
}
