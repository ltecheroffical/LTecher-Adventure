#include <SDL3/SDL.h>

#include <framework/gameobject.h>

#include "player.h"

#ifndef COMPONENT_PLAYER_ANIM_H
#define COMPONENT_PLAYER_ANIM_H

class PlayerAnim : public GameObject {
public:
  PlayerAnim(Player *player);
  ~PlayerAnim();

  void update(const float delta) override;
  void handle_idle();
  void handle_move();

private:
  Player *_player;

  float _anim_timer = 0.0f;

  bool _move_alternate = false;
  uint8_t _anim_offset = 0;
};
#endif
