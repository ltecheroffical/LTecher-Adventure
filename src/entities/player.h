#include <gameobject.h>

#include <components/health.h>
#include <vector>

#pragma once

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
    int frame = 0;
    float anim_timer = 0.0f;  

    static bool resources_loaded;
    static Texture texture_player_atlas;
};
