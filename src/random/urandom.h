/*
 * LTecher Adventure (c) 2024
 *
 * This file belongs to the LTecher Adventure project
 */

#include <fstream>

#include "irandom_generator.h"

#ifndef URANDOM_GEN_H
#define URANDOM_GEN_H

/*
 * Generates random data from /dev/urandom
 *
 * See: https://en.wikipedia.org/wiki/%2Fdev%2Frandom
 */
class DevURandomGenerator : public IRandomGenerator {
public:
  DevURandomGenerator();
  ~DevURandomGenerator();

  int random_int() override;
  char random_char() override;
  float random_float() override;

private:
  std::ifstream _urandom;
};
#endif
