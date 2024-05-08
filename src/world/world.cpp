#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <lib/PerlinNoise.hpp>

#include <app.h>

#include "world.h"

SDL_Image World::_texture_map_atlas;

bool within_range(float value, float min, float max) {
  return value >= min && value <= max;
}

World::World() {
  static bool assets_loaded = false;
  if (!assets_loaded) {
    assets_loaded = true;
    
    World::_texture_map_atlas.texture = IMG_LoadTexture(
        App::singleton()->renderer,
        RESOURCES "images/envoriment/tilemap/ground.png");

    if (World::_texture_map_atlas.texture == nullptr) {
      PANIC("Failed to load map atlas", EXIT_FAILURE);
    }

    SDL_QueryTexture(World::_texture_map_atlas.texture, nullptr, nullptr,
                     &World::_texture_map_atlas.width,
                     &World::_texture_map_atlas.height);
  }
}

void World::generate_world(int world_seed) {
  this->_world_data.resize(this->_map_width * this->_map_height);

  const siv::PerlinNoise::seed_type seed = world_seed;
  const siv::PerlinNoise perlin{seed};

  for (uint8_t x = 0; x < this->_map_width; x++) {
    for (uint8_t y = 0; y < this->_map_height; y++) {
      float noise_data = perlin.octave2D(x, y, 4);
      uint8_t map_data = 0;

      if (within_range(noise_data, -0.4, 0.2)) {
        map_data = 1;
      } else {
        SDL_Log("Map: %f", noise_data);
      }

      this->_world_data[x + y * this->_map_width] = map_data;
    }
  }
}

void World::render(SDL_Renderer *renderer) {
  for (uint8_t x = 0; x < this->_map_width; x++) {
    for (uint8_t y = 0; y < this->_map_height; y++) {
      SDL_FRect src_rect;
      SDL_FRect dst_rect;

      if (this->_world_data[x + y * this->_map_width] == 0) {
        continue;
      }

      src_rect = { (float)this->_world_data[x + y * this->_map_width], 0, 16, 16 };
      dst_rect = {
        (float)x * 16 - App::camera().x, 
        (float)y * 16 - App::camera().y, 16, 16 };

      SDL_RenderTexture(
        renderer,
        World::_texture_map_atlas.texture,
        &src_rect, &dst_rect
      ); 
    }
  }
}
