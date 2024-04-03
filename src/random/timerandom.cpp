#include "random.h"

int Random::int_timerandom()
{
  // Take current time and convert into 8 bits 4 times (for a full integer)
  int random_number = 0;

  for (int i = 0; i < (sizeof(int) * 8); i++)
  {
    random_number |= (std::chrono::system_clock::now().time_since_epoch().count() % 2 == 0) << i;
  }

  return random_number;
}

float Random::float_timerandom()
{
  // Take current time and convert into 8 bits 4 times (for a full float)
  float random_number = 0;
  int int_random = Random::int_timerandom();
  
  random_number = reinterpret_cast<float&>(int_random);
  return random_number;
}

char Random::char_timerandom()
{
  // Take current time and convert into 8 bits
  char random_number = 0;
  
  for (int i = 0; i < 8; i++)
  {
    random_number |= (std::chrono::system_clock::now().time_since_epoch().count() % 2 == 0) << i;
  }
  return random_number;
}
