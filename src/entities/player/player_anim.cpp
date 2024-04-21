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
  if (this->_player->get_state() == PlayerState::PLAYER_STATE_IDLE) {
    const float IDLE_TIMER_MAX = 1.0f;
    if (this->_anim_timer > IDLE_TIMER_MAX) {
      this->_anim_timer = 0.0f;
      this->_player->_anim_frame = (this->_player->_anim_frame + 1) % 2;
    } else {
      this->_anim_timer += delta;
    }

    if (this->_player->_anim_frame > 1) {
      this->_player->_anim_frame = 0;
    }
  } else if (this->_player->get_state() == PlayerState::PLAYER_STATE_WALKING) {
    const float WALK_TIMER_MAX = 0.5f;
    if (this->_anim_timer > WALK_TIMER_MAX) {
      this->_anim_timer = 0.0f;
      const Vec2 direction = this->_player->get_walk_direction();
      int *anim_frame = &this->_player->_anim_frame;
   
      /*
       * Player animation frames lists
       */
      const int PLAYER_UP[2] = {4, 5};
      const int PLAYER_DOWN[2] = {2, 3};
      const int PLAYER_LEFT[2] = {6, 7};
      const int PLAYER_RIGHT[2] = {8, 9};

      /*
       * Is the player going in more than one direction?
       */
      if (direction.x != 0.0f && direction.y != 0.0f) {
        /*
         * The player is going in more than one direction.
         * So alternate between 2 direction animations
         */
        if (this->_move_alternate) {
          if (direction.x > 0.0f) {
            *anim_frame += this->_anim_offset;
            *anim_frame = wrap(*anim_frame + 1, PLAYER_RIGHT[0], PLAYER_RIGHT[1]);
          } else if (direction.x < 0.0f) {
            *anim_frame += this->_anim_offset;
            *anim_frame = wrap(*anim_frame + 1, PLAYER_LEFT[0], PLAYER_LEFT[1]); 
          } 
        } else if (!this->_move_alternate) {
          if (direction.y > 0.0f) {
            *anim_frame += this->_anim_offset;
            *anim_frame = wrap(*anim_frame + 1, PLAYER_DOWN[0], PLAYER_DOWN[1]);
          } else if (direction.y < 0.0f) {
            *anim_frame += this->_anim_offset;
            *anim_frame = wrap(*anim_frame + 1, PLAYER_UP[0], PLAYER_UP[1]);
          }
        }
        
        this->_anim_offset = (this->_anim_offset + 1) % 2;
        this->_move_alternate = !this->_move_alternate;
      } else {
        /*
         * The player is going in one direction.
         * So just change the animation frame to the direction
         */
        if (direction.x > 0.0f) {
          *anim_frame = wrap(*anim_frame + 1, PLAYER_RIGHT[0], PLAYER_RIGHT[1]);
        } else if (direction.x < 0.0f) {
          *anim_frame = wrap(*anim_frame + 1, PLAYER_LEFT[0], PLAYER_LEFT[1]); 
        } else if (direction.y > 0.0f) {
          *anim_frame = wrap(*anim_frame + 1, PLAYER_DOWN[0], PLAYER_DOWN[1]);
        } else if (direction.y < 0.0f) {
          *anim_frame = wrap(*anim_frame + 1, PLAYER_UP[0], PLAYER_UP[1]);
        }

        // Also reset the move values
        this->_anim_offset = 0;
        this->_move_alternate = false;
      }
    } else {
      this->_anim_timer += delta;
    }

    if (this->_player->_anim_frame <= 1) {
      this->_anim_timer = 1.1f;
    }
  }
}
