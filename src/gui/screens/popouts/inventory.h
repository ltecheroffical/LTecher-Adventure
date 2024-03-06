#include "../screen.h"

#pragma once

class Inventory : public Screen
{
public:
  Inventory(Scene *scene);
  ~Inventory() override = default;

  void render() override;
  void update(float delta) override {};

private:
  static bool resources_loaded;

  static Texture inventory_popout;

};
