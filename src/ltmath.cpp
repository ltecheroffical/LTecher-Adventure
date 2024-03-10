#include "ltmath.h"

int LTMath::wrap(int value, int min, int max)
{
  if (value < min)
  {
    return max;
  }
  else if (value > max)
  {
    return min;
  } 
  return value;
}
