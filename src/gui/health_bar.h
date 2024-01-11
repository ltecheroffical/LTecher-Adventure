#include <raylib.h>

#include <gameobject.h>

#include <components/health.h>

#pragma once

class HealthBar : public GameObject
{
public:
    HealthBar();
    ~HealthBar() = default;

    Health health = Health(250);

    void on_render() override;

private:
    static bool resources_loaded;

    static Texture texture_health_bar_atlas;
};