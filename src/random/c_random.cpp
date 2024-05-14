#include <cstdlib>

#include <SDL3/SDL.h>

#include "c_random.h"

bool CRandom::try_get_seed(char *seed) {
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
  int data;
  char seed;
  
  // Generate 4 bytes of random data and add each byte to data
  for (int i = 0; i < 4; i++) {
    if (this->try_get_seed(&seed)) {
      std::srand(seed);
      char random = (char)std::rand();
      ((char*)&data)[i] = random;
    } else {
      this->_warning_queue.push_back("Failed to get seed for random_int()");
      ((char*)&data)[i] = 0x00;
    }
  }
  return data;
}

char CRandom::random_char() {
  char data;
  char seed;
  
  // Generate 1 byte of random data 
  if (this->try_get_seed(&seed)) {
    std::srand(seed);
    data = (char)std::rand();
  } else {
    this->_warning_queue.push_back("Failed to get seed for random_char()");
    data = 0;
  }
  return data;
}

float CRandom::random_float() {
  float data;
  char seed;
  
  // Generate 4 bytes of random data and add each byte to data
  for (int i = 0; i < 4; i++) {
    if (this->try_get_seed(&seed)) {
      std::srand(seed);
      char random = (char)std::rand();
      ((char*)&data)[i] = random;
    } else {
      this->_warning_queue.push_back("Failed to get seed for random_float()");
      ((char*)&data)[i] = 0x00;
    }
  }

  return data;
}

void CRandom::seed(const char seed) {
  this->_seed.push_back(seed);
}

bool CRandom::can_generate(const CRandomType type) const {
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
