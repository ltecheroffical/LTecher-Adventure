#include <raylib.h>

#include <ltmath.h>

#include <event.h>

#include "player_anim.h"

PlayerAnim::PlayerAnim(uint8_t *player_anim_frame, Event<Vector2> *on_walk_animation, Event<> *on_still_animation) : anim_frame(player_anim_frame)
 {
  on_walk_animation->subscribe([this](Vector2 direction){
    if (this->anim_timer > 0.5f)
    {
      if (direction.y == -1)
      {
        *this->anim_frame = LTMath::wrap(*this->anim_frame + 1, 4, 5);
      }
      else if (direction.y == 1)
      {
        *this->anim_frame = LTMath::wrap(*this->anim_frame + 1, 2, 3);
      }
      else if (direction.x == -1)
      {
        *this->anim_frame = LTMath::wrap(*this->anim_frame + 1, 6, 7);
      }
      else if (direction.x == 1)
      {
        *this->anim_frame = LTMath::wrap(*this->anim_frame + 1, 8, 9);
      }
      else if (this->anim_timer > 1.0f)
      {
        *this->anim_frame = LTMath::wrap(*this->anim_frame + 1, 0, 1);
        this->anim_timer = 0.0f;
      }
      else if (*this->anim_frame > 1)
      {
        *this->anim_frame = 0;
      }
      this->anim_timer = 0.0f;
    }
  });

  on_still_animation->subscribe([this](){
    if (this->anim_timer > 1.0f)
    {
      *this->anim_frame = LTMath::wrap(*this->anim_frame + 1, 0, 1);
      this->anim_timer = 0.0f;
    }
  });
}

void PlayerAnim::on_update(float delta)
{
  this->anim_timer += delta;
}
