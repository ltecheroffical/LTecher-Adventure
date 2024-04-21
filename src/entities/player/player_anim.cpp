#include "player_anim.h"


PlayerAnim::PlayerAnim(Player *player) : _player(player) {

}

PlayerAnim::~PlayerAnim() {

}

int wrap(int value, const int min, const int max) {
  if (value < min) {
    value = max;
  } else if (value > max) {
    value = min;
  }
  return value;
}

void PlayerAnim::update(const float delta) {
  if (this->_player->_state == PlayerState::PLAYER_STATE_IDLE) {
    if (this->_anim_timer > 1.0f) {
      this->_anim_timer = 0.0f;
      this->_player->_anim_frame = (this->_player->_anim_frame + 1) % 2;
    } else {
      this->_anim_timer += delta;
    }

    if (this->_player->_anim_frame > 1) {
      this->_player->_anim_frame = 0;
    }
  } else if (this->_player->_state == PlayerState::PLAYER_STATE_WALKING) {
    if (this->_anim_timer > 0.5f) {
      this->_anim_timer = 0.0f;
      Vec2 direction = this->_player->get_walk_direction();
      
      if (direction.y == 1.0f) {
        this->_player->_anim_frame = wrap(this->_player->_anim_frame + 1, 2, 3);
      } else if (direction.y == -1.0f) {
        this->_player->_anim_frame = wrap(this->_player->_anim_frame + 1, 4, 5);
      } else if (direction.x == -1.0f) {
        this->_player->_anim_frame = wrap(this->_player->_anim_frame + 1, 6, 7);
      } else if (direction.x == 1.0f) {
        this->_player->_anim_frame = wrap(this->_player->_anim_frame + 1, 8, 9);
      }
    } else {
      this->_anim_timer += delta;
    }

    if (this->_player->_anim_frame <= 1) {
      this->_anim_timer = 1.1f;
    }
  }
}

void PlayerAnim::player_destroy() {
  // We just got a signal from the player that it's going to be destroyed

}
