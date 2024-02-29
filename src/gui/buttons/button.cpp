#include <raylib.h>

#include "button.h"

void Button::on_render()
{
    DrawRectangle(static_cast<int>(this->position.x), static_cast<int>(this->position.y), static_cast<int>(this->size.x), static_cast<int>(this->size.y), this->background_color);
    
    Vector2 text_size = MeasureTextEx(this->text_font, this->text_content, static_cast<float>(this->text_font_size), static_cast<float>(this->text_font_spacing));

    DrawTextEx(this->text_font, this->text_content, { ((this->size.x - text_size.x) / 2) + this->position.x, ((this->size.y - text_size.y) / 2) + this->position.x }, static_cast<float>(this->text_font_size), static_cast<float>(this->text_font_spacing), this->text_color);
}

bool Button::is_hovered() const
{
    return CheckCollisionPointRec(GetMousePosition(), { this->position.x, this->position.y, this->size.x, this->size.y });
}

bool Button::is_pressed() const
{
    return this->is_hovered() && IsMouseButtonReleased(0);
}