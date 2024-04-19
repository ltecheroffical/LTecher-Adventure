/*
 * LTecher Adventure (c) 2024
 *
 * This file belongs to the LTecher Adventure project
 */

#include <vector>
#include <string>

#ifndef IRANDOM_GENERATOR_H
#define IRANDOM_GENERATOR_H

/*
 * Base interface for all random generators
 */
class IRandomGenerator {
public:
  virtual ~IRandomGenerator() = default;
 
  /*
   * Generates a random integer for the generator
   *
   * @returns a random integer
   */
  virtual int random_int() = 0;
  /*
   * Generates a random character for the generator
   *
   * @returns a random character
   */
  virtual char random_char() = 0;
  /*
   * Generates a random float for the generator
   *
   * @returns a random float
   */
  virtual float random_float() = 0;

  /*
   * Gets a warning message from the generator
   */
  bool get_warning(std::string *warning) {
    if (!this->_warning_queue.empty()) {
      *warning = this->_warning_queue.front();
      this->_warning_queue.erase(this->_warning_queue.begin());
      return true;
    } else {
      return false;
    }
  }

protected:
  std::vector<std::string> _warning_queue;
};
#endif
