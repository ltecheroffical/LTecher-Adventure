#include <scene.h>

#pragma once
class GameScene : public Scene
{
public:
    GameScene() = default;
    ~GameScene() override = default;

    void on_load() override;
    void on_update(float delta) override;
};