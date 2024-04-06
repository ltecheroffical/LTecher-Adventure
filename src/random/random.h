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
   *
   * Security: This is not a secure way of randomness because it uses /dev/urandom that uses the previous random number as a seed
   */
  int int_urandom();
  /*
   * Returns a random number from /dev/urandom as 1 byte (unix only)
   *
   * Security: This is not a secure way of randomness because it uses /dev/urandom that uses the previous random number as a seed
   */
  char char_urandom();
  /*
   * Returns a random number from /dev/urandom as a 4 byte float (unix only)
   *
   * Security: This is not a secure way of randomness because it uses /dev/urandom that uses the previous random number as a seed
   */
  float float_urandom();


  /*
   * Returns a random number from /dev/random as a 4 byte integer (unix only, should be used for secure randomness)
   *
   * Security: This is a secure way of randomness because it uses /dev/random meant for secure randomness
   * Note: On BSD and macOS, /dev/random doesn't block if there is no user input
   */
  int int_random();
  /*
   * Returns a random number from /dev/random as 1 byte (unix only, should be used for secure randomness)
   *
   * Security: This is a secure way of randomness because it uses /dev/random meant for secure randomness
   * Note: On BSD and macOS, /dev/random doesn't block if there is no user input
   */
  char char_random();
  /*
   * Returns a random number from /dev/random as a 4 byte float (unix only, should be used for secure randomness)
   *
   * Security: This is a secure way of randomness because it uses /dev/random meant for secure randomness
   * Note: On BSD and macOS, /dev/random doesn't block if there is no user input
   */
  float float_random();


  /*
   * Returns a random number from a 17 bit row of bits as 1 byte (method used on atari's poki chips)
   *
   * Security: A hacker can find a pattern in the bits that is not random and exploit it
   */
  char char_atari();


  /*
   * Returns a random number from the current time in seconds from the epoch (1970-01-01 00:00:00 UTC) as a 4 byte integer
   *
   * Security: This is very unsecure and should not be used for secure randomness
   */
  int int_timerandom();
  /*
   * Returns a random number from the current time in seconds from the epoch (1970-01-01 00:00:00 UTC) as 1 byte
   *
   * Security: This is very unsecure and should not be used for secure randomness
   */
  char char_timerandom();
  /*
   * Returns a random number from the current time in seconds from the epoch (1970-01-01 00:00:00 UTC) as a 4 byte float
   *
   * Security: This is very unsecure and should not be used for secure randomness
   */
  float float_timerandom();
}
