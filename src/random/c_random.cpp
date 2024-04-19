/*
 * LTecher Adventure (c) 2024
 *
 * This file belongs to the LTecher Adventure project
 */

#include <cstdlib>

#include <SDL3/SDL.h>

#include "c_random.h"

CRandom::CRandom() {
  
}

bool CRandom::try_get_seed(uint8_t *seed) {
  // If the seed vector is empty, return false
  if (this->_seed.empty()) {
    return false;
  }
  // Get the first seed and remove it from the vector
  *seed = this->_seed.front();
  this->_seed.erase(this->_seed.begin());
  return true;
}

int CRandom::random_int() {
  uint8_t data[4];
  uint8_t seed;
  
  // Generate 4 bytes of random data and add each byte to data
  for (int i = 0; i < 4; i++) {
    if (this->try_get_seed(&seed)) {
      std::srand(seed);
      char random = std::rand();
      data[i] = random;
    } else {
      this->_warning_queue.push_back("Failed to get seed for random_int()");
      data[i] = 0x00;
    }
  }
  return (int)*data;
}

char CRandom::random_char() {
  char data;
  uint8_t seed;
  
  // Generate 1 byte of random data 
  if (this->try_get_seed(&seed)) {
    std::srand(seed);
    data = std::rand();
  } else {
    this->_warning_queue.push_back("Failed to get seed for random_char()");
    data = 0;
  }
  return data;
}

float CRandom::random_float() {
  uint8_t data[4];
  uint8_t seed;
  
  // Generate 4 bytes of random data and add each byte to data
  for (int i = 0; i < 4; i++) {
    if (this->try_get_seed(&seed)) {
      std::srand(seed);
      char random = std::rand();
      data[i] = random;
    } else {
      this->_warning_queue.push_back("Failed to get seed for random_float()");
      data[i] = 0x00;
    }
  }

  return (float)*data;
}

void CRandom::seed(uint8_t seed) {
  this->_seed.push_back(seed);
}

bool CRandom::can_generate(CRandomType type) {
  switch (type) {
    case CRandomType::INT:
      return this->_seed.size() >= 4;
    case CRandomType::CHAR:
      return !this->_seed.empty();
    case CRandomType::FLOAT:
      return this->_seed.size() >= 4;
    default:
      return false;
  }
}
