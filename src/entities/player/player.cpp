#include <SDL3/SDL.h>

#include <marcos/errors.h>

#include <keybinds.h>
#include <app.h>

#include "player_anim.h"
#include "player.h"


SDL_ImageData Player::_texture_player_atlas;

int player_anim_child_id = 0;

Player::Player() {
  static bool assets_loaded = false;

  if (!assets_loaded) {
    this->_texture_player_atlas = { 0 };

    this->_texture_player_atlas.texture = IMG_LoadTexture(
      App::singleton()->renderer, RESOURCES "images/entities/player.png");

    if (this->_texture_player_atlas.texture == NULL) {
      PANIC("Failed to load player texture", EXIT_FAILURE);
    }

    SDL_QueryTexture(
      this->_texture_player_atlas.texture, NULL, NULL,
      &this->_texture_player_atlas.width,
      &this->_texture_player_atlas.height);

    SDL_SetTextureScaleMode(this->_texture_player_atlas.texture, SDL_SCALEMODE_NEAREST);

    assets_loaded = true;
  }
}

Player::~Player() {
  
}

void Player::init() {
  this->position = { 0.0f, 0.0f };
  this->scale = { 5.5f, 5.0f };

  this->_state = PlayerState::PLAYER_STATE_IDLE;

  this->_anim = std::make_unique<PlayerAnim>(this);
  player_anim_child_id = App::singleton()->get_scene()->add_child(
    this->_anim.get(), Scene::OBJ_ID_NULL);
}

void Player::destroy() {
  App::singleton()->get_scene()->remove_child(player_anim_child_id);
  player_anim_child_id = 0;
}

void Player::update(const float delta) {
  this->update_movement(delta);
}

void Player::render(SDL_Renderer *renderer) {
  // Render the player at the coords in this->_position
  SDL_FRect src_rect;
  SDL_FRect dst_rect;

  src_rect = {(float)this->_anim_frame * 16, 0, 16, 16};
  dst_rect = {this->position.x - App::camera().x,
              this->position.y - App::camera().y,
              this->scale.x * 16, this->scale.y * 16};
  SDL_RenderTexture(
    renderer,
    this->_texture_player_atlas.texture, 
    &src_rect, &dst_rect
  );
}

void Player::update_movement(const float delta) {
  const float SPEED = 50.0f;
  
  Vec2 direction = { 0.0f, 0.0f };

  Keybinds &keybinds = Keybinds::singleton();
  const Uint8 *keys = SDL_GetKeyboardState(NULL);

  bool left_pressed = keys[keybinds.get_or_null(Keybind::PLAYER_LEFT)];
  bool right_pressed = keys[keybinds.get_or_null(Keybind::PLAYER_RIGHT)];
  bool up_pressed = keys[keybinds.get_or_null(Keybind::PLAYER_UP)];
  bool down_pressed = keys[keybinds.get_or_null(Keybind::PLAYER_DOWN)];

  direction.x = (right_pressed ? 1.0f : 0.0f) - (left_pressed ? 1.0f : 0.0f);
  direction.y = (down_pressed ? 1.0f : 0.0f) - (up_pressed ? 1.0f : 0.0f);

  direction = vec2_normalize(direction);

  if (direction.x == 0.0f && direction.y == 0.0f) {
    this->_state = PLAYER_STATE_IDLE;
  } else {
    this->_state = PlayerState::PLAYER_STATE_WALKING;
    this->_move_direction = direction;
  }
  
  this->position.x += direction.x * SPEED * delta;
  this->position.y += direction.y * SPEED * delta;
}

