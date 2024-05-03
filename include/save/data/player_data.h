#include <stdint.h>

#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H

typedef struct PlayerData {
  char name[32] = { 0 };

  uint16_t health;
  uint16_t max_health;

  float x;
  float y;
} PlayerData;
#endif
