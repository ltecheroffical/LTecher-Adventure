#include <memory>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <framework/gameobject.h>
#include <framework/sdl_data.h>


#ifndef ENTITY_PLAYER_H
#define ENTITY_PLAYER_H

class PlayerAnim;

typedef enum PlayerState {
  PLAYER_STATE_IDLE,
  PLAYER_STATE_WALKING
} PlayerState;

class Player : public GameObject {
friend class PlayerAnim;
public:
  Player();
  ~Player();

  PlayerState get_state() const;
  inline Vec2 get_walk_direction() const { return this->_move_direction; };

private:
  void init() override;
  void update(const float delta) override;
  void render(SDL_Renderer *renderer) override;
  void destroy() override;

  PlayerState _state = PlayerState::PLAYER_STATE_IDLE;

  Vec2 _move_direction = { 0.0f, 0.0f };

  void update_movement(const float delta);

  std::unique_ptr<PlayerAnim> _anim;
  int _anim_frame = 0;

  static SDL_ImageData _texture_player_atlas;
};
#endif
