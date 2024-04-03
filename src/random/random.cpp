#include <fstream>

#include "random.h"

int Random::int_random()
{
  std::ifstream random("/dev/random", std::ios::in | std::ios::binary);
  if (check_ifstream_errors(random)) return 0;
  int random_number = 0;
  random.read(reinterpret_cast<char*>(&random_number), sizeof(random_number));
  random.close();
  return random_number;
}

float Random::float_random()
{
  std::ifstream random("/dev/random", std::ios::in | std::ios::binary);
  if (check_ifstream_errors(random)) return 0;
  float random_number = 0;
  random.read(reinterpret_cast<char*>(&random_number), sizeof(random_number));
  random.close();
  return random_number;
}

char Random::char_random()
{
  std::ifstream random("/dev/random", std::ios::in | std::ios::binary);
  if (check_ifstream_errors(random)) return 0;
  char random_number = 0;
  random.read(reinterpret_cast<char*>(&random_number), sizeof(random_number));
  random.close();
  return random_number;
}
