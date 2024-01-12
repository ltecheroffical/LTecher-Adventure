#include <raylib.h>

#include "camera.h"

GameCamera *GameCamera::camera = nullptr;


GameCamera::GameCamera()
{
    GameCamera::camera = this;
}

GameCamera::~GameCamera()
{
    GameCamera::camera = nullptr;
}


Camera2D GameCamera::to_camera_2d() const
{
    Camera2D camera_2d{ 0 };

    camera_2d.offset.x = this->position.x + this->offset.x;
    camera_2d.offset.y = this->position.y + this->offset.y;

    camera_2d.rotation = this->rotation;
    camera_2d.zoom = this->zoom;

    return camera_2d;
}