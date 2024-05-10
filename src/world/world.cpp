#include <algorithm>
#include <string>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <imgui.h>

#include <app.h>

#include "world.h"

unsigned int CAMERA_SIZE_INCREASE_X = 238;
unsigned int CAMERA_SIZE_INCREASE_Y = 238;

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
 
  this->noise.SetFractalOctaves(3);
  this->noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

}

void World::generate_world(int seed) {
  this->noise.SetSeed(seed);
  for (int8_t x = -2; x < 2; ++x) {
    float percentage = 0;
    for (int8_t y = -2; y < 2; ++y) {
      this->generate_chunk(x, y);

      percentage = (float)(x + y) / (16 * 2);
      percentage = percentage * 100;
    }
    if ((int)percentage % 15 == 0) {
      SDL_Log("WORLD GENERATION IS %i%% COMPLETE", (int)percentage);
    }
  }
  this->_world_seed = seed;
}

void World::generate_chunk(int world_x, int world_y) { 
  uint8_t chunk_data[16 * 16] = { 0 };   

  const uint8_t MAX_TILES = 2;

  for (int8_t x = 0; x < 16; ++x) {
    for (int8_t y = 0; y < 16; ++y) {
      // Perlin noise between 0 and 1
      float noise_data = this->noise.GetNoise((float)(x + world_x * 16), (float)(y + world_y * 16));
      uint8_t map_data = 0;

      map_data = std::clamp(roundf(noise_data * MAX_TILES), 0.0f, (float)MAX_TILES - 1.0f);

      chunk_data[x + y * 16] = map_data;
    }
  }

  Chunk chunk;
  
  chunk.x = world_x;
  chunk.y = world_y;
  chunk.is_modified = false;

  memcpy(&chunk.data, chunk_data, 16 * 16);
  this->_world_data.push_back(chunk);
}

 
void World::update(const float delta) {
  // Calculate the camera's position in chunk coordinates
  int camera_chunk_x = static_cast<int>(App::camera().x) / (16 * 16);
  int camera_chunk_y = static_cast<int>(App::camera().y) / (16 * 16);

  int screen_width, screen_height = 0;
  SDL_GetWindowSize(App::singleton()->window, &screen_width, &screen_height);

  
  const uint16_t CHUNK_GEN_DISTANCE_X = screen_width / 210.0f;
  const uint16_t CHUNK_GEN_DISTANCE_Y = screen_height / 150.0f;

  // Iterate over the surrounding chunks of the camera
  for (int x = camera_chunk_x - CHUNK_GEN_DISTANCE_X; x <= camera_chunk_x + CHUNK_GEN_DISTANCE_X; ++x) {
    for (int y = camera_chunk_y - CHUNK_GEN_DISTANCE_Y; y <= camera_chunk_y + CHUNK_GEN_DISTANCE_Y; ++y) {
      // Check if the chunk at (x, y) exists in the world
      screen_width += CAMERA_SIZE_INCREASE_X;
      screen_height += CAMERA_SIZE_INCREASE_Y;

      unsigned int chunk_x_world = x * (16 * 16);
      unsigned int chunk_y_world = y * (16 * 16);

      unsigned int camera_x_offsetted = App::camera().x - CAMERA_SIZE_INCREASE_X;
      unsigned int camera_y_offsetted = App::camera().y - CAMERA_SIZE_INCREASE_Y;

      if (!is_intersecting(camera_x_offsetted, camera_y_offsetted, screen_width, screen_height, chunk_x_world, chunk_y_world, 16, 16)) {
        continue;
      }

      if (!has_chunk(x, y)) {
        // Generate the chunk
        generate_chunk(x, y);
      }
    }
  }

  // Let's test each chunk to see if we are using them
  for (size_t i = 0; i < this->_world_data.size(); ++i) {
    int chunk_x = this->_world_data[i].x;
    int chunk_y = this->_world_data[i].y;

    int screen_width, screen_height = 0;
    SDL_GetWindowSize(App::singleton()->window, &screen_width, &screen_height); 

    screen_width += CAMERA_SIZE_INCREASE_X;
    screen_height += CAMERA_SIZE_INCREASE_Y;

    unsigned int chunk_x_world = chunk_x * (16 * 16);
    unsigned int chunk_y_world = chunk_y * (16 * 16);


    unsigned int camera_x_offsetted = App::camera().x - CAMERA_SIZE_INCREASE_X;
    unsigned int camera_y_offsetted = App::camera().y - CAMERA_SIZE_INCREASE_Y;

    if (is_intersecting(camera_x_offsetted, camera_y_offsetted, screen_width, screen_height, chunk_x_world, chunk_y_world, 16, 16)) {
      continue;
    }

    // The chunk is not visible
    if (this->_world_data[i].is_modified) {
      // Let's keep this chunk
      continue;
    }

    // Delete it now
    this->_world_data.erase(this->_world_data.begin() + i);
  }
}

void World::render(SDL_Renderer *renderer) {
  uint8_t chunk[16 * 16] = { 0 };

  for (int i = 0; i < (int)this->_world_data.size(); ++i) {
    int chunk_x = this->_world_data[i].x;
    int chunk_y = this->_world_data[i].y;

    memcpy(&chunk[0], this->_world_data[i].data, 16 * 16);

    // Are we intersecting with the camera?

    int screen_width, screen_height = 0;
    SDL_GetWindowSize(App::singleton()->window, &screen_width, &screen_height);
   

    screen_width += CAMERA_SIZE_INCREASE_X;
    screen_height += CAMERA_SIZE_INCREASE_Y;

    if (!is_intersecting(App::camera().x - CAMERA_SIZE_INCREASE_X, App::camera().y - CAMERA_SIZE_INCREASE_Y, screen_width, screen_height,
                         chunk_x * (16 * 16), chunk_y * (16 * 16), 16, 16)) {
      continue;
    }

    for (uint8_t x = 0; x < 16; ++x) {
      for (uint8_t y = 0; y < 16; ++y) {
        SDL_FRect src_rect;
        SDL_FRect dst_rect;

        uint8_t tile_pos_x = 0;
        uint8_t tile_pos_y = chunk[x + y * 16];
        
        if (tile_pos_y > World::_texture_map_atlas.height) {
            tile_pos_x += (tile_pos_y - World::_texture_map_atlas.height);
            tile_pos_y = World::_texture_map_atlas.height;
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
  
  // Let's render the chunk info
  this->render_imgui();
}

void World::render_imgui() {
#if PRODUCTION_BUILD == 0
  ImGui::Begin("World");

  ImGui::Text("Chunk count: %lu", (long unsigned int)this->_world_data.size());

  // Display all chunks
  if (ImGui::BeginListBox("Chunks")) {
    for (int i = 0; i < (int)this->_world_data.size(); ++i) {
      std::string chunk_string = "";
      int chunk_x = this->_world_data[i].x;
      int chunk_y = this->_world_data[i].y;
      
      chunk_string = "Chunk ";
      chunk_string += std::to_string(i + 1);
      chunk_string += " ";
      
      chunk_string += "(";
      chunk_string += std::to_string(chunk_x * (16 * 16));
      chunk_string += ", ";
      chunk_string += std::to_string(chunk_y * (16 * 16));
      chunk_string += ")";
      
      ImGui::Selectable(chunk_string.c_str());
    }
    ImGui::EndListBox();
  }
  ImGui::InputInt("Selected Chunk", (int*)&this->_selected_chunk);
  this->_selected_chunk = std::clamp(
      (int)this->_selected_chunk, 0, (int)this->_world_data.size());
  ImGui::End();

  if (this->_selected_chunk != 0) {
    ImGui::Begin("Chunk");

    unsigned int chunk_index = this->_selected_chunk - 1;

    ImGui::InputInt2("Chunk position (Chunk space)", &this->_world_data[chunk_index].x);
    ImGui::Checkbox("Chunk modified", &this->_world_data[chunk_index].is_modified);
    
    if (ImGui::BeginListBox("Tiles")) {
      for (uint8_t x = 0; x < 16; ++x) {
        for (uint8_t y = 0; y < 16; ++y) {
          std::string tile_string;

          tile_string += "(";
          tile_string += std::to_string(x + 1);
          tile_string += ", ";
          tile_string += std::to_string(y + 1);
          tile_string += ")";

          ImGui::Selectable(tile_string.c_str());
        }
      }

      ImGui::EndListBox();
    }

    ImGui::InputInt("Selected Block", (int *)&this->_selected_block);
    
    this->_selected_block = std::clamp(
      (int)this->_selected_block, 0, (16 * 16)
    );

    if (this->_selected_block != 0) {
      unsigned int block_index = this->_selected_block - 1;
      unsigned int block_data = this->_world_data[chunk_index].data[block_index];

      ImGui::InputInt("Block type", (int *)&block_data);
      block_data = std::clamp((int)block_data, 0, 255);      

      this->_world_data[chunk_index].data[block_index] = block_data;
    }

    ImGui::End();
  } 
#endif
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
