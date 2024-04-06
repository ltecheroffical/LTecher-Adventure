#include <plugin.h>

#pragma once

// A more user side debugger allowing for useful information, not for real debugging
class Debugger : public Plugin
{
public:
  Debugger() = default;
  ~Debugger() override = default;

  /*
   * If the debug menu is visible
   */
  static bool is_visible; 

  void on_update(float delta) override;
  void on_render() override;

private:
  void draw_info(int x, int y, int size);
  void draw_preformance(int x, int y, int size);
};
