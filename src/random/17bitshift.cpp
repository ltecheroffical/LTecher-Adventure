#include <vector>

#include <app.h>

#include "random.h"

class AtariRandomHandler
{
  public:
    /*
     * All the bits that are currently in the vector
     */
    std::vector<bool> bits;

    inline static AtariRandomHandler singleton() {
      static AtariRandomHandler instance;
      return instance;
    };


  private:
    inline AtariRandomHandler() {
      // Initialize bits
      for (int i = 0; i < 18; i++)
      {
        // Use the current time as the starting bits
        this->bits.push_back(std::chrono::system_clock::now().time_since_epoch().count() % 2 == 0);
      }

      App::singleton().on_update.subscribe([this](float delta) {
        // Update atari random
        int index_end = this->bits.size();
        this->bits.push_back(this->bits[index_end - 8] != this->bits[index_end]);
        this->bits.erase(this->bits.begin());
      });
    };
};

char Random::char_atari()
{
  AtariRandomHandler atari_random = AtariRandomHandler::singleton();

  // Take 8 bits and convert it into char
  char random_number = 0;
  for (int i = 0; i < 8; i++)
  {
    random_number |= (atari_random.bits[i] << i);
  }
  return random_number;
}
