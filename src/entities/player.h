#include <stdexcept>

#include <gameobject.h>

#include <components/health.h>

#pragma once

class Player : public GameObject
{
public:
    Player();
    ~Player() = default;

    Health health;

    void on_update(float delta) override;
    void on_render() override;

private:
};
