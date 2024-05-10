#include <vector>

#include <lib/FastNoiseLite.h>

#include <framework/sdl_data.h>
#include <framework/gameobject.h>

#ifndef WORLD_H
#define WORLD_H

typedef struct Chunk {
  int x, y;
  bool is_modified;
  uint8_t data[16 * 16];
} Chunk;

class World : public GameObject {
public:
  World();
  ~World() = default;

  bool has_chunk(int x, int y);
  Chunk *get_chunk(int x, int y);

  void generate_world(int seed);

  void update(const float delta) override;
  void render(SDL_Renderer *renderer) override;
  void destroy() override;

private:
  std::vector<Chunk> _world_data;

  FastNoiseLite noise;

  int _world_seed = 0;

#if PRODUCTION_BUILD == 0
  unsigned int _selected_chunk = 0;
  unsigned int _selected_block = 0;
#endif

  void generate_chunk(int x, int y);

  void render_chunk(SDL_Renderer *renderer, int x, int y);

  void render_imgui();


  static SDL_Image _texture_map_atlas;
};
#endif
