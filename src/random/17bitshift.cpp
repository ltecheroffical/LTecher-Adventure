#include <vector>

#include <app.h>

#include "random.h"

class AtariRandomHandler
{
  public:
    std::vector<bool> bits;

    inline static AtariRandomHandler singleton() {
      static AtariRandomHandler instance;
      return instance;
    };


  private:
    inline AtariRandomHandler() {
      // Initialize bits
      for (int i = 0; i < 17; i++)
      {
        // Use the current time as the starting bits
        this->bits.push_back(std::chrono::system_clock::now().time_since_epoch().count() % 2 == 0);
      }

      App::on_update.subscribe([this](float delta) {
        // Update atari random
        this->bits.push_back(this->bits[0] != this->bits[1]);
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
  printf("%d\n", random_number);
  return random_number;
}