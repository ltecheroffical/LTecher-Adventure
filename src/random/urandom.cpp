#include <fstream>

#include "random.h"

int Random::int_urandom()
{
  std::ifstream urandom("/dev/urandom", std::ios::in | std::ios::binary);
  if (check_ifstream_errors(urandom)) return 0;
  int random_number = 0;
  urandom.read(reinterpret_cast<char*>(&random_number), sizeof(random_number));
  urandom.close();
  return random_number;
}

float Random::float_urandom()
{
  std::ifstream urandom("/dev/urandom", std::ios::in | std::ios::binary);
  if (check_ifstream_errors(urandom)) return 0;
  float random_number = 0;
  urandom.read(reinterpret_cast<char*>(&random_number), sizeof(random_number));
  urandom.close();
  return random_number;
}

char Random::char_urandom()
{
  std::ifstream urandom("/dev/urandom", std::ios::in | std::ios::binary);
  if (check_ifstream_errors(urandom)) return 0;
  char random_number = 0;
  urandom.read(reinterpret_cast<char*>(&random_number), sizeof(random_number));
  urandom.close();
  return random_number;
}
