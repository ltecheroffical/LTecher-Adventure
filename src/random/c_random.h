#include <vector>

#include "irandom_generator.h"

#ifndef CRANDOM_H
#define CRANDOM_H

enum class CRandomType {
  INT,
  FLOAT,
  CHAR
};

const uint8_t SEED_COUNT_CONSIDERED_LOW = 6;

/*
 * Generates random numbers using the C stdlib
 */
class CRandom : public IRandomGenerator {
public:
  CRandom() = default;
  ~CRandom() override = default;

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
  bool can_generate(const CRandomType type) const;

  /*
   * Seeds the random number generator
   *
   * @param seed The seed to use
   */
  void seed(const uint8_t seed);

  /*
   * Gets the seed of the random number generator
   */
  inline int get_seed_count() const { return _seed.size(); };

private:
  /*
   * Why is it a vector? To have more than one seed!
   */
   std::vector<uint8_t> _seed;

   bool try_get_seed(uint8_t *seed);
};
#endif
