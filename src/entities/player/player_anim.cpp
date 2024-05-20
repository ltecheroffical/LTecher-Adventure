#include "player.h"

/*
 * Player animation frames lists
 */
const char PLAYER_UP = 4;
const char PLAYER_DOWN = 2;
const char PLAYER_LEFT = 6;
const char PLAYER_RIGHT = 8;

int wrap(int value, const int min, const int max) {
  if (value < min) {
    value = max;
  } else if (value > max) {
    value = min;
  }
  return value;
}

void process_move_anim(char *anim_frame, const Vec2 direction) {
  static bool _move_alternate = false;
  static char _anim_offset = 0;
  
  /*
   * Is the player going in more than one direction?
   */
  if (direction.x != 0.0f && direction.y != 0.0f) {
    /*
     * The player is going in more than one direction.
     * So alternate between 2 direction animations
     */
    if (_move_alternate) {
      if (direction.x > 0.0f) {
        *anim_frame += _anim_offset;
        *anim_frame = (char)wrap(*anim_frame + 1, PLAYER_RIGHT, PLAYER_RIGHT + 1);
      } else if (direction.x < 0.0f) {
        *anim_frame += _anim_offset;
        *anim_frame = (char)wrap(*anim_frame + 1, PLAYER_LEFT, PLAYER_LEFT + 1); 
      } 
    } else if (!_move_alternate) {
      if (direction.y > 0.0f) {
        *anim_frame += _anim_offset;
        *anim_frame = (char)wrap(*anim_frame + 1, PLAYER_DOWN, PLAYER_DOWN + 1);
      } else if (direction.y < 0.0f) {
        *anim_frame += _anim_offset;
        *anim_frame = (char)wrap(*anim_frame + 1, PLAYER_UP, PLAYER_UP + 1);
      }
    }
    
    _anim_offset = (_anim_offset + 1) % 2;
    _move_alternate = !_move_alternate;
  } else {
    /*
     * The player is going in one direction.
     * So just change the animation frame to the direction
     */
    if (direction.x > 0.0f) {
      *anim_frame = (char)wrap(*anim_frame + 1, PLAYER_RIGHT, PLAYER_RIGHT+1);
    } else if (direction.x < 0.0f) {
      *anim_frame = (char)wrap(*anim_frame + 1, PLAYER_LEFT, PLAYER_LEFT+1); 
    } else if (direction.y > 0.0f) {
      *anim_frame = (char)wrap(*anim_frame + 1, PLAYER_DOWN, PLAYER_DOWN+1);
    } else if (direction.y < 0.0f) {
      *anim_frame = (char)wrap(*anim_frame + 1, PLAYER_UP, PLAYER_UP+1);
    }

    // Also reset the move values
    _anim_offset = 0;
    _move_alternate = false;
  }
}

void Player::update_anim(const float delta) {
  if (this->get_state() == PlayerState::PLAYER_STATE_IDLE) {
    const float IDLE_TIMER_MAX = 1.0f;
    if (this->_anim_timer > IDLE_TIMER_MAX) {
      this->_anim_timer = 0.0f;
      this->_anim_frame = (this->_anim_frame + 1) % 2;
    } else {
      this->_anim_timer += delta;
    }

    if (this->_anim_frame > 1) {
      this->_anim_frame = 0;
    }
  } else if (this->get_state() == PlayerState::PLAYER_STATE_WALKING) {
    const float WALK_TIMER_MAX = 0.5f;
    if (this->_anim_timer > WALK_TIMER_MAX) {
      process_move_anim(&this->_anim_frame, this->get_walk_direction());
      this->_anim_timer = 0.0f;
    } else {
      this->_anim_timer += delta;
    }

    if (this->_anim_frame <= 1) {
      this->_anim_timer = 1.1f;
    }
  }
}
