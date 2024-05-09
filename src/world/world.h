#include <vector>

#include <framework/sdl_data.h>
#include <framework/gameobject.h>

#ifndef WORLD_H
#define WORLD_H

typedef struct Chunk {
  int x, y;
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

  int _world_seed = 0;

  void generate_chunk(int x, int y, int seed);

  void render_chunk(SDL_Renderer *renderer, int x, int y);


  static SDL_Image _texture_map_atlas;
};
#endif
