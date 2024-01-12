#include <raylib.h>

#include <gameobject.h>

#pragma once

class GameCamera : public GameObject
{
public:
    GameCamera();
    ~GameCamera() override;

    // The current camera
    static GameCamera *camera;

    // Camera offset (displacement from target)
    Vector2 offset{0, 0};
    // Camera zoom (scaling)
    float zoom = 1.0f;

    Camera2D to_camera_2d() const;
};