#include "random.h"

DevRandomGenerator::DevRandomGenerator() : _random("/dev/random") {
  
}

DevRandomGenerator::~DevRandomGenerator() {
  this->_random.close();
}

int DevRandomGenerator::random_int() {
  int data;
  this->_random.read(reinterpret_cast<char *>(&data), sizeof(data));
  return data;
}

char DevRandomGenerator::random_char() {
  char data;
  this->_random.read(reinterpret_cast<char *>(&data), sizeof(data));
  return data;
}

float DevRandomGenerator::random_float() {
  float data;
  this->_random.read(reinterpret_cast<char *>(&data), sizeof(data));
  return data;
}
