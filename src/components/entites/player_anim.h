#include <raylib.h>

#include <stdint.h>

#include <event.h>

#include <components/component.h>

#pragma once

class PlayerAnim : public Component
{
public:
  PlayerAnim(uint8_t *anim_frame, Event<Vector2> *on_walk_animation, Event<> *on_still_animation);
  ~PlayerAnim() = default;

  void on_update(float delta) override;

private:
  uint8_t *anim_frame;
  float    anim_timer = 0;
};
