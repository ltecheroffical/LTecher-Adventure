#include <framework/math.h>

using Client = struct Client {
  Vec2 position{0.0f, 0.0f};
  float health = 0.0f;
  float health_max = 250.0f;
};

int run_server(int port);
