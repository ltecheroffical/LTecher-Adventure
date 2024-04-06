#include <raylib.h>

#include <gui/ui_element.h>

#include <components/health.h>

#pragma once

class HeartBar : public UIElement
{
public:
  HeartBar();
  ~HeartBar() override = default;

  /*
   * The current health that is shown in the health bar
   */
  Health health = Health(250);

  /*
   * The seperation between each heart
   */
  float seperator = 5.0f;

  void on_render() override;

private:
  static bool resources_loaded;
  static Texture texture_health_atlas;
};
