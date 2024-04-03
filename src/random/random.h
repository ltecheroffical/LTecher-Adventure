#include <fstream>

#pragma once

inline bool check_ifstream_errors(std::ifstream& stream)
{
  return !stream;
};

namespace Random
{
  /*
   * Returns a random number from /dev/urandom as a 4 byte integer (unix only)
   */
  int int_urandom();
  /*
   * Returns a random number from /dev/urandom as 1 byte (unix only)
   */
  char char_urandom();
  /*
   * Returns a random number from /dev/urandom as a 4 byte float (unix only)
   */
  float float_urandom();

  /*
   * Returns a random number from /dev/random as a 4 byte integer (unix only, should be used for secure randomness)
   */
  int int_random();
  /*
   * Returns a random number from /dev/random as 1 byte (unix only, should be used for secure randomness)
   */
  char char_random();
  /*
   * Returns a random number from /dev/random as a 4 byte float (unix only, should be used for secure randomness)
   */
  float float_random();

  /*
   * Returns a random number from a 17 bit row of bits as 1 byte (method used on atari's poki chips)
   */
  char char_atari();
}
