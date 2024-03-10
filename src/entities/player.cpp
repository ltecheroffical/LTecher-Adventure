#include <raylib.h>
#include <raymath.h>

#include <asset_ids.h>
#include <ltmath.h>

#include <app.h>

#include "camera.h"

#include "player.h"


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

      Player::resources_loaded = true;
    }

    this->scale = 5;
}

void Player::on_update(float delta)
{
  constexpr float SPEED = 30.0;

  Vector2 direction{0, 0};

  this->anim_timer += delta; 
  
  direction.x = static_cast<float>(IsKeyDown(KEY_D)) - static_cast<float>(IsKeyDown(KEY_A));
  direction.y = static_cast<float>(IsKeyDown(KEY_S)) - static_cast<float>(IsKeyDown(KEY_W));

  if (direction.x != 0 || direction.y != 0)
  {
    direction = Vector2Normalize(direction);
    
    if (this->anim_timer > 0.5f)
    {
      if (direction.y == -1)
      {
        this->anim_frame = LTMath::wrap(this->anim_frame + 1, 4, 5);
      }
      else if (direction.y == 1)
      {
        this->anim_frame = LTMath::wrap(this->anim_frame + 1, 2, 3);
      }
      else if (direction.x == -1)
      {
        this->anim_frame = LTMath::wrap(this->anim_frame + 1, 6, 7);
      }
      else if (direction.x == 1)
      {
        this->anim_frame = LTMath::wrap(this->anim_frame + 1, 8, 9);
      }
      this->anim_timer = 0.0f;
    }

    this->position.x -= direction.x * SPEED * delta;
    this->position.y -= direction.y * SPEED * delta;
  }
  else if (this->anim_timer > 1.0f)
  {
    this->anim_frame = LTMath::wrap(this->anim_frame + 1, 0, 1);
    this->anim_timer = 0.0f;
  }
  else if (this->anim_frame > 1)
  {
    this->anim_frame = 0;
  }
  this->health.damage(delta * 0.1f);
}

void Player::on_render()
{
    Camera2D game_camera = GameCamera::camera->to_camera_2d();

    BeginMode2D(game_camera);
    
    DrawTexturePro(Player::texture_player_atlas, 
                   {16 * (float)this->anim_frame, 0, 16, 16}, {0, 0, 16 * 1.2f * this->scale, 16 * this->scale},
                this->position, 0, WHITE);
    
    EndMode2D();
}
