#include <raylib.h>
#include <raymath.h>

#include <marcos/compare.h>
#include <asset_ids.h>
#include <ltmath.h>

#ifndef REMOVE_IMGUI
#include <imgui.h>
#endif

#include <keybinds.h>
#include <app.h>

#include "camera.h"

#include "player.h"


std::vector<Player*> Player::players;

bool Player::resources_loaded = false;

Texture Player::texture_player_atlas;

Player::Player()
{
  if (!Player::resources_loaded)
  {
    // Load player texture
    Image image_player_atlas = LoadImageFromMemory(".png", (unsigned char*)assets_raw.at(100), (int)asset_sizes.at(100));
    Player::texture_player_atlas = LoadTextureFromImage(image_player_atlas);
    UnloadImage(image_player_atlas);

    App::singleton().on_close.subscribe([this](){
      UnloadTexture(this->texture_player_atlas);
    });
  
    Player::resources_loaded = true;
  } 

  this->scale = 5;
  
  this->anim = new PlayerAnim(&this->anim_frame, &this->on_move_animation, &this->on_still_animation);

  this->add_component(&this->health, 0);
  this->add_component(this->anim, 1);

  Player::players.push_back(this);
}

Player::~Player()
{
  this->remove_component(0);
  this->remove_component(1);

  delete this->anim;
#ifndef WIN32
  Player::players.erase(std::remove(Player::players.begin(), 
                        Player::players.end(), this),
                        Player::players.end());
#endif
}

void Player::on_update(float delta)
{
  constexpr float SPEED = 50.0;

  Vector2 direction{0, 0};

  Keybinds binds = Keybinds::singleton();

  direction.x = static_cast<float>(IsKeyDown(binds.get(Keybind::KEYBIND_RIGHT))) - static_cast<float>(IsKeyDown(binds.get(Keybind::KEYBIND_LEFT)));
  direction.y = static_cast<float>(IsKeyDown(binds.get(Keybind::KEYBIND_DOWN))) - static_cast<float>(IsKeyDown(binds.get(Keybind::KEYBIND_UP)));

  if (direction.x != 0 || direction.y != 0)
  {
    direction = Vector2Normalize(direction);
    
    this->on_move_animation.emit(direction); 

    this->position.x -= direction.x * SPEED * delta;
    this->position.y -= direction.y * SPEED * delta;
  }
  else
  {
    this->on_still_animation.emit();
  }

  if (Vector2Distance(this->position, this->camera->position) > 1)
  {
    this->camera->position.x = Lerp(this->camera->position.x, this->position.x, delta * 2.5f);
    this->camera->position.y = Lerp(this->camera->position.y, this->position.y, delta * 2.5f);
  }

  this->health_ptr()->damage(delta * 0.1f);
}

void Player::on_render()
{
    Camera2D game_camera = GameCamera::camera->to_camera_2d();

    BeginMode2D(game_camera);
    
    DrawTexturePro(Player::texture_player_atlas, 
                   {16 * (float)this->anim_frame, 0, 16, 16}, {0, 0, 16 * 1.2f * this->scale, 16 * this->scale},
                this->position, 0, WHITE);
    
    EndMode2D();

#ifndef REMOVE_IMGUI
    ImGui::Begin("Player", NULL, 0);

    ImGui::InputFloat2("Position", &this->position.x);
    ImGui::InputFloat("Health", this->health.cur_health_ptr(), 0.1f, 0.5f);

    ImGui::End();
  #endif
}

void Player::set_camera(GameCamera *camera)
{
  this->camera = camera;

  if (this->camera != nullptr)
  {
    this->camera->position = this->position; 
  
    camera->offset.x = static_cast<float>(GetScreenWidth() - (16 * this->scale)) / 2.0f;
    camera->offset.y = static_cast<float>(GetScreenHeight() - (16 * this->scale)) / 2.0f;
  }
}
