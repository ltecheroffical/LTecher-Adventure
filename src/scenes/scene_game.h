#include <scene.h>

#pragma once
class GameScene : public Scene
{
public:
    GameScene() = default;
    ~GameScene() override = default;

    void on_load() override;
};