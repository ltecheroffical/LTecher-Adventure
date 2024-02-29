#include <raylib.h>

#include <gui/ui_element.h>

#pragma once

class Button : public UIElement
{
public:
    Button() = default;
    ~Button() override = default;

    Color background_color = { 40, 40, 40, 255 };

    Color text_color = WHITE;
    Font text_font = GetFontDefault();
    
    int text_font_size = 16;
    int text_font_spacing = 2;

    char *text_content = (char*)"Label";
    
    bool is_pressed() const;
    bool is_hovered() const;

    void on_render() override;
};