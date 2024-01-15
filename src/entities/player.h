#include <stdexcept>

#include <gameobject.h>

#include <components/health.h>

#pragma once

class Player : public GameObject
{
public:
    Player();
    ~Player() override = default;

    Health health = Health(20);

    void on_update(float delta) override;
    void on_render() override;

private:
    static bool resources_loaded;
    static Texture texture_player_atlas;
};
