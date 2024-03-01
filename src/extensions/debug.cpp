#include <raylib.h>

#include <string>

#include <os_info.h>

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
   
  #define H_SPACING 5
  #define V_SPACING 5

  this->draw_info(V_SPACING, H_SPACING, 20);
  this->draw_preformance(V_SPACING, H_SPACING * 8, 20);
}

void Debugger::draw_preformance(int x, int y, int size)
{
  DrawFPS(x, y);
}

void Debugger::draw_info(int x, int y, int size)
{  
  std::string os_name;

  os_name.append(OS::get_name());
  os_name.append(" ");
  os_name.append(OS::get_version());

  DrawText(os_name.c_str(), x, y, size, WHITE);
#if PRODUCTION_BUILD == 0
  DrawText("DEBUG BUILD", MeasureText(os_name.c_str(), size) + 15, y, size, RED);
#endif
}
