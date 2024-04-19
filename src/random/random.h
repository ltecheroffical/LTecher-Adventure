/*
 * LTecher Adventure (c) 2024
 *
 * This file belongs to the LTecher Adventure project
 */

#include <fstream>

#include "irandom_generator.h"

#ifndef RANDOM_GEN_H
#define RANDOM_GEN_H

/*
 * Generates random data from /dev/random
 *
 * See: https://en.wikipedia.org/wiki/%2Fdev%2Frandom
 * WARNING: GENERATING RANDOM DATA MAY BLOCK THE GAME!!
 */
class DevRandomGenerator : public IRandomGenerator {
public:
  DevRandomGenerator();
  ~DevRandomGenerator();

  int random_int() override;
  char random_char() override;
  float random_float() override;

  /*
   * Seeds the /dev/random generator with data for the next read
   *
   * @param data The data to seed the generator with
   */
  void seed(char *data);

private:
  std::ifstream _random;
};
#endif
