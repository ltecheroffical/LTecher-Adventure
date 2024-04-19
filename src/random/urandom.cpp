/*
 * LTecher Adventure (c) 2024
 *
 * This file belongs to the LTecher Adventure project
 */


#include "urandom.h"

DevURandomGenerator::DevURandomGenerator() : _urandom("/dev/urandom") {

}

DevURandomGenerator::~DevURandomGenerator() {
  this->_urandom.close();
}

int DevURandomGenerator::random_int() {
  int data;
  this->_urandom.read(reinterpret_cast<char *>(&data), sizeof(data));
  return data;
}

char DevURandomGenerator::random_char() {
  char data;
  this->_urandom.read(reinterpret_cast<char *>(&data), sizeof(data));
  return data;
}

float DevURandomGenerator::random_float() {
  float data;
  this->_urandom.read(reinterpret_cast<char *>(&data), sizeof(data));
  return data;
}
