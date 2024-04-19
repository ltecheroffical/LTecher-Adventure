/*
 * LTecher Adventure (c) 2024
 *
 * This file belongs to the LTecher Adventure project
 */

#include <vector>

#include "irandom_generator.h"

#ifndef CRANDOM_H
#define CRANDOM_H

enum class CRandomType {
  INT,
  FLOAT,
  CHAR
};

#define SEED_COUNT_CONSIDERED_LOW 6

/*
 * Generates random numbers using the C stdlib
 */
class CRandom : public IRandomGenerator {
public:
  CRandom();
  ~CRandom() = default;

  int random_int() override;
  float random_float() override;
  char random_char() override;
  
  /*
   * Determines if the random number generator will generate new numbers
   *
   * If it returns false, then seed the random number generator
   *
   * @param type The type of random number
   *
   * @returns True if the random number generator will generate new numbers
   */
  bool can_generate(CRandomType type);

  /*
   * Seeds the random number generator
   *
   * @param seed The seed to use
   */
  void seed(uint8_t seed);

  /*
   * Gets the seed of the random number generator
   */
  inline int get_seed_count() { return _seed.size(); };

private:
  /*
   * Why is it a vector? To have more than one seed!
   */
   std::vector<uint8_t> _seed;

   bool try_get_seed(uint8_t *seed);
};
#endif
