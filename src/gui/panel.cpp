#include "panel.h"

void Panel::on_render()
{
    DrawRectangle(static_cast<int>(this->position.x), static_cast<int>(this->position.y), static_cast<int>(this->size.x), static_cast<int>(this->size.y), this->panel_color);
}