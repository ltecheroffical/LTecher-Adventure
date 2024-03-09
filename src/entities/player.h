#include <gameobject.h>

#include <components/health.h>

#pragma once

class Player : public GameObject
{
public:
    Player();
    ~Player() override = default;

    Health health = Health(10);

    void on_update(float delta) override;
    void on_render() override;

private:
    int frame = 0;
    float anim_timer = 0.0f;

    static bool resources_loaded;
    static Texture texture_player_atlas;
};
