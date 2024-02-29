#include <raylib.h>

#include <gui/ui_element.h>

#pragma once

class Panel : public UIElement
{
public:
    Panel() = default;
    ~Panel() override = default;

    Color panel_color = BLACK;

    void on_render() override;
};