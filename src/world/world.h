#include <vector>

#include <framework/sdl_data.h>
#include <framework/gameobject.h>

#ifndef WORLD_H
#define WORLD_H

class World : public GameObject {
public:
  World();
  ~World() = default;

  void generate_world(int seed);

  void render(SDL_Renderer *renderer) override;

private:
  std::vector<uint8_t> _world_data;

  static SDL_Image _texture_map_atlas;

  unsigned int _map_width = 200;
  unsigned int _map_height = 200;
};
#endif
