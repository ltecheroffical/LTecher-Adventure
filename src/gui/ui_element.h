#include <gameobject.h>

#pragma once

class UIElement : public GameObject
{
public:
    UIElement() = default;
    ~UIElement() override = default;

    Vector2 size{50, 50};

    bool disabled = false;
};