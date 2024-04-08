#include <cstdint>
#include <vector>

#include <gameobject.h>

#include <entities/camera.h>

#include <components/entites/player_anim.h>
#include <components/health.h>

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

    /*
     * Returns a pointer to the health component of the player
     *
     * @returns The health component of the player as a pointer
     */
    inline Health *health_ptr() { return &this->health; };

    /*
     * Bind the camera that the player will update to follow the player
     * 
     * @param camera The camera to make follow the player
     */
    void set_camera(GameCamera *camera);

    /*
     * All the player instances in the game
     */
    static std::vector<Player*> players;

    void on_update(float delta) override;
    void on_render() override;

private:
    Health health = Health(10);

    // Animation component
    PlayerAnim *anim;
    uint8_t anim_frame = 0;

    Event<Vector2> on_move_animation;
    Event<> on_still_animation;

    GameCamera *camera = nullptr;

    // Resources
    static bool resources_loaded;
    static Texture texture_player_atlas;
};
