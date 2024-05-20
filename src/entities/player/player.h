#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <framework/gameobject.h>
#include <framework/sdl_data.h>

#include <components/health.h>


#ifndef ENTITY_PLAYER_H
#define ENTITY_PLAYER_H

const float PLAYER_DEATH_TIMER_MAX = 2.0f;

using PlayerState = enum class PlayerState {
  PLAYER_STATE_IDLE,
  PLAYER_STATE_WALKING
};

class Player : public GameObject {
friend class PlayerAnim;
public:
  Player();
  ~Player() override = default;

  PlayerState get_state() const { return this->_state; };
  inline Vec2 get_walk_direction() const { return this->_move_direction; };

private:
  void init() override;
  void update(const float delta) override;
  void render(SDL_Renderer *renderer) override;
  
  Health _health = { 250.0f, 250.0f };

  PlayerState _state = PlayerState::PLAYER_STATE_IDLE;

  Vec2 _move_direction = { 0.0f, 0.0f };

  void update_movement(const float delta);
  void update_camera(const float delta);
  void update_anim(const float delta);

  char  _anim_frame = 0;
  float _anim_timer = 0.0f;

  float _player_death_timer = PLAYER_DEATH_TIMER_MAX;


  static SDL_ImageData _texture_player_atlas;
};
#endif
