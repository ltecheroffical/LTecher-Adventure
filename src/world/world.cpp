#include <algorithm>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <lib/FastNoiseLite.h>

#include <app.h>

#include "world.h"

SDL_Image World::_texture_map_atlas;

bool is_intersecting(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2) {
  return x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2;
}

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

void World::generate_world(int seed) { 
  for (int8_t x = -2; x < 2; x++) {
    float percentage = 0;
    for (int8_t y = -2; y < 2; y++) {
      this->generate_chunk(x, y, seed);

      percentage = (float)(x + y) / (16 * 2);
      percentage = percentage * 100;
    }
    if ((int)percentage % 15 == 0) {
      SDL_Log("WORLD GENERATION IS %i%% COMPLETE", (int)percentage);
    }
  }
  this->_world_seed = seed;
}

void World::generate_chunk(int world_x, int world_y, int seed) {
  FastNoiseLite noise;

  noise.SetSeed(seed);
  noise.SetFractalOctaves(3);
  noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

  uint8_t chunk_data[16 * 16] = { 0 };   

  const uint8_t MAX_TILES = 2;

  for (int8_t x = 0; x < 16; x++) {
    for (int8_t y = 0; y < 16; y++) {
      // Perlin noise between 0 and 1
      float noise_data = noise.GetNoise((float)(x + world_x * 16), (float)(y + world_y * 16));
      uint8_t map_data = 0;

      map_data = std::clamp(roundf(noise_data * MAX_TILES), 0.0f, (float)MAX_TILES - 1.0f);

      chunk_data[x + y * 16] = map_data;
    }
  }

  Chunk chunk;
  
  chunk.x = world_x;
  chunk.y = world_y;

  memcpy(&chunk.data, chunk_data, 16 * 16);
  this->_world_data.push_back(chunk);
}

 
void World::update(const float delta) {
  // Calculate the camera's position in chunk coordinates
  int camera_chunk_x = static_cast<int>(App::camera().x) / (16 * 16);
  int camera_chunk_y = static_cast<int>(App::camera().y) / (16 * 16);

  int screen_width, screen_height = 0;
  SDL_GetWindowSize(App::singleton()->window, &screen_width, &screen_height);

  const uint16_t chunk_gen_distance = (screen_width + screen_height) / 200.0f;

  // Iterate over the surrounding chunks of the camera
  for (int x = camera_chunk_x - chunk_gen_distance; x <= camera_chunk_x + chunk_gen_distance; x++) {
    for (int y = camera_chunk_y - chunk_gen_distance; y <= camera_chunk_y + chunk_gen_distance; y++) {
      // Check if the chunk at (x, y) exists in the world
      if (!has_chunk(x, y)) {
        // Generate the chunk if it doesn't exist
        generate_chunk(x, y, this->_world_seed);
      }
    }
  }

  // Let's test each chunk to see if we are using them
  for (size_t i = 0; i < this->_world_data.size(); i++) {
    int chunk_x = this->_world_data[i].x;
    int chunk_y = this->_world_data[i].y;

    int screen_width = 0;
    int screen_height = 0;
    SDL_GetWindowSize(App::singleton()->window, &screen_width, &screen_height);
   
    screen_width += 800;
    screen_height += 800;

    if (is_intersecting(App::camera().x - 800, App::camera().y - 800, screen_width, screen_height,
                         chunk_x * (16 * 16), chunk_y * (16 * 16), 16, 16)) {
      continue;
    }

    this->_world_data.erase(this->_world_data.begin() + i);
  }
}

void World::render(SDL_Renderer *renderer) {
  uint8_t chunk[16 * 16] = { 0 };

  for (size_t i = 0; i < this->_world_data.size(); i++) {
    int chunk_x = this->_world_data[i].x;
    int chunk_y = this->_world_data[i].y;

    memcpy(&chunk[0], this->_world_data[i].data, 16 * 16);

    // Are we intersecting with the camera?

    int screen_width = 0;
    int screen_height = 0;
    SDL_GetWindowSize(App::singleton()->window, &screen_width, &screen_height);
   
    screen_width += 800;
    screen_height += 800;

    if (!is_intersecting(App::camera().x - 800, App::camera().y - 800, screen_width, screen_height,
                         chunk_x * (16 * 16), chunk_y * (16 * 16), 16, 16)) {
      continue;
    }

    for (uint8_t x = 0; x < 16; x++) {
      for (uint8_t y = 0; y < 16; y++) {
        SDL_FRect src_rect;
        SDL_FRect dst_rect;

        uint8_t tile_pos_x = 0;
        uint8_t tile_pos_y = chunk[x + y * 16];
        
        while (tile_pos_y > World::_texture_map_atlas.height) {
          tile_pos_y--;
          tile_pos_x++;
        }
        
        src_rect = { (float)tile_pos_x * 16, (float)tile_pos_y * 16, 16, 14 };
        dst_rect = {
          (float)(x * 16) + (chunk_x * (16 * 16)) - App::camera().x, 
          (float)(y * 16) + (chunk_y * (16 * 16)) - App::camera().y, 17, 16 };

        SDL_RenderTexture(
          renderer,
          World::_texture_map_atlas.texture,
          &src_rect, &dst_rect
        ); 
      }
    }
  }
}

void World::destroy() {
  this->_world_data.clear();
}

bool World::has_chunk(int x, int y) {
  for (Chunk chunk : this->_world_data) {
    if (chunk.x == x && chunk.y == y) {
      return true;
    }
  }
  return false;
}
