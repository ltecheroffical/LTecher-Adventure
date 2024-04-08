#include <stdint.h>

#pragma once

/*
 * A single tile
 * 
 * Can be serialized with `reinterpret_cast`
 */
struct Tile
{
  // The position of the tile, split into 4 bytes for X and Y
  uint8_t position;

  // The id of the tile
  uint16_t id;

  // Extra metadata to be stored
  char metadata[64];
};
