#include <stdbool.h>
#include <stdint.h>

#include "hash.h"


#define CRC32_POLYNOMIAL 0xEDB88320

unsigned int crc32(const char *data, const size_t size) {
  unsigned int crc = 0xFFFFFFFF;

  for (size_t i = 0; i < size; ++i) {
    crc ^= (unsigned int)data[i];
    for (int j = 0; j < 8; ++j) {
      if (crc & 1) {
        crc = (crc >> 1) ^ CRC32_POLYNOMIAL;
      } else {
        crc >>= 1;
      }
    }
  }

  return ~crc;
}

