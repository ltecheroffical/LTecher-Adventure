#include <raylib.h>

#include <gui/ui_element.h>

#include <components/health.h>

#pragma once

class HeartBar : public UIElement
{
public:
    HeartBar();
    ~HeartBar() override = default;

    Health health = Health(250);

    float seperator = 5.0f;

    void on_render() override;

private:
    static bool resources_loaded;
    static Texture texture_health_atlas;
};
