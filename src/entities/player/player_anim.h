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
  void player_destroy();

private:
  Player *_player;

  float _anim_timer = 0.0f;
};
#endif
