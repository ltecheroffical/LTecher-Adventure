#include <stdint.h>

#ifndef NETWORK_TYPES_H
#define NETWORK_TYPES_H

typedef struct NetworkedPlayer {
  unsigned int id;

  char name[64];

  float position_x;
  float position_y;

  float health;
  float health_max;
} NetworkedPlayer;
#endif
