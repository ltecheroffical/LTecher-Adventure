#include <raylib.h>

#include <gui/ui_element.h>

#include <components/health.h>

#pragma once

class HealthBar : public UIElement
{
public:
    HealthBar();
    ~HealthBar() override = default;

    Health health = Health(250);

    void on_render() override;

private:
    static bool resources_loaded;

    static Texture texture_health_atlas;
};