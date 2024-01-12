#include <raylib.h>

#include "check_box.h"

void CheckBox::on_update(float delta)
{
    if (this->disabled)
    {
        return;
    }

    if (IsMouseButtonReleased(0) && CheckCollisionPointRec(GetMousePosition(), { this->position.x, this->position.y, this->size.x, this->size.y }))
    {
        this->checked = !this->checked;
    }
}

void CheckBox::on_render()
{
    Vector2 value_size{static_cast<float>(this->size.x * 0.8), static_cast<float>(this->size.y * 0.8)};

    DrawRectangle(this->position.x, this->position.y, this->size.x, this->size.y, BLACK);
    if (this->checked)
    {
        DrawRectangle(this->position.x + ((this->size.x - value_size.x) / 2), this->position.y + ((this->size.y - value_size.y) / 2), value_size.x, value_size.y, GREEN);
    }
}