#include <raylib.h>

#include <gameobject.h>

#pragma once

class GameCamera : public GameObject
{
public:
    GameCamera() = default;
    ~GameCamera() override;

    // The current camera
    static GameCamera *camera;

    // Camera offset (displacement from target)
    Vector2 offset{0, 0};
    // Camera zoom (scaling)
    float zoom = 1.0f;

    // Is the camera enabled?
    bool enabled = true;

    /*
     * Converts the camera to a raylib camera for use
     */
    Camera2D to_camera_2d() const;

    void on_start() override;
    void on_update(float delta) override;
};
