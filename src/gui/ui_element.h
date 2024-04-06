#include <gameobject.h>

#pragma once

class UIElement : public GameObject
{
public:
  UIElement() { this->is_gui = true; };
  ~UIElement() override = default;

  Vector2 size{50, 50};

  bool disabled = false;
};
