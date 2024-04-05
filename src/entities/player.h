#include <cstdint>

#include <gameobject.h>

#include <components/health.h>
#include <vector>

#pragma once

// A stripped down version of a player that doesn't do anything but is great for storage
struct PlayerData
{
  Vector2 position = {0, 0};
  Health health = Health(10);
};

class Player : public GameObject
{
public:
    Player();
    ~Player() override;

    Health health = Health(10);

    void on_update(float delta) override;
    void on_render() override;

    static std::vector<Player*> players;

private:
    uint8_t anim_frame = 0;
    float   anim_timer = 0.0f;

    static bool resources_loaded;
    static Texture texture_player_atlas;
};
