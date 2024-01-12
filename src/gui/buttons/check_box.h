#include <raylib.h>

#include <gui/ui_element.h>

#pragma once

class CheckBox : public UIElement
{
public:
    CheckBox() = default;
    ~CheckBox() = default;

    inline bool get_checked() { return this->checked; };
    inline void set_checked(bool checked) { this->checked = checked; };

    void on_update(float delta) override;
    void on_render() override;

private:
    bool checked = false;
};