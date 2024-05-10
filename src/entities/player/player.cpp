#include <SDL3/SDL.h>

#include <imgui.h>

#include <marcos/errors.h>

#include <keybinds.h>
#include <app.h>

#include "player.h"


SDL_ImageData Player::_texture_player_atlas;


Player::Player() {
  static bool assets_loaded = false;

  if (!assets_loaded) {
    Player::_texture_player_atlas.texture = IMG_LoadTexture(
      App::singleton()->renderer, RESOURCES "images/entities/player.png");

    if (Player::_texture_player_atlas.texture == nullptr) {
      PANIC("Failed to load player texture", EXIT_FAILURE);
    }

    SDL_QueryTexture(
      Player::_texture_player_atlas.texture, nullptr, nullptr,
      &Player::_texture_player_atlas.width,
      &Player::_texture_player_atlas.height);

    SDL_SetTextureScaleMode(Player::_texture_player_atlas.texture, SDL_SCALEMODE_NEAREST);

    App::singleton()->on_exit.subscribe([]() {
      SDL_DestroyTexture(Player::_texture_player_atlas.texture);
    });

    assets_loaded = true;
  }
}

void Player::init() {
  this->position = { 0.0f, 0.0f };
  this->scale = { 5.5f, 5.0f };

  this->_state = PlayerState::PLAYER_STATE_IDLE;

}

void Player::update(const float delta) {
  this->update_movement(delta);
  this->update_camera(delta);

  this->update_anim(delta);
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
    Player::_texture_player_atlas.texture, 
    &src_rect, &dst_rect
  );

#if PRODUCTION_BUILD == 0
  ImGui::Begin("Player");

  ImGui::InputFloat2("Position", &this->position.x);

  ImGui::End();
#endif
}

void Player::update_movement(const float delta) {
  const float SPEED = 50.0f;
  
  Vec2 direction = { 0.0f, 0.0f };

  const Keybinds &keybinds = Keybinds::singleton();
  const Uint8 *keys = SDL_GetKeyboardState(nullptr);

  bool left_pressed = keys[keybinds.get_or_null(Keybind::PLAYER_LEFT)];
  bool right_pressed = keys[keybinds.get_or_null(Keybind::PLAYER_RIGHT)];
  bool up_pressed = keys[keybinds.get_or_null(Keybind::PLAYER_UP)];
  bool down_pressed = keys[keybinds.get_or_null(Keybind::PLAYER_DOWN)];

  direction.x = (right_pressed ? 1.0f : 0.0f) - (left_pressed ? 1.0f : 0.0f);
  direction.y = (down_pressed ? 1.0f : 0.0f) - (up_pressed ? 1.0f : 0.0f);

  direction = vec2_normalize(direction);

  if (direction.x == 0.0f && direction.y == 0.0f) {
    this->_state = PlayerState::PLAYER_STATE_IDLE;
  } else {
    this->_state = PlayerState::PLAYER_STATE_WALKING;
    this->_move_direction = direction;
  }
 
#if PRODUCTION_BUILD == 0
  if (keys[SDL_SCANCODE_R]) {
    direction.x *= 4;
    direction.y *= 4;
  }
#endif

  this->position.x += direction.x * SPEED * delta;
  this->position.y += direction.y * SPEED * delta;
}

void Player::update_camera(const float delta) {
  float camera_position_x = this->position.x;
  float camera_position_y = this->position.y;
  
  // Get window size
  int window_width;
  int window_height;

  SDL_GetWindowSize(App::singleton()->window, &window_width, &window_height);

  
  camera_position_x -= (float)window_width / 2;
  camera_position_y -= (float)window_height / 2;
  
  camera_position_x += (this->scale.x * 16.0f) / 2.0f;
  camera_position_y += (this->scale.y * 16.0f) / 2.0f;


  float *current_camera_x = &App::singleton()->get_scene()->camera.x;
  float *current_camera_y = &App::singleton()->get_scene()->camera.y;

  *current_camera_x = std::lerp(*current_camera_x, camera_position_x, delta * 1.5f);
  *current_camera_y = std::lerp(*current_camera_y, camera_position_y, delta * 1.5f);
}
