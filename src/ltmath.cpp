#include "ltmath.h"

float LTMath::wrap(float value, float min, float max)
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

float LTMath::clamp(float value, float min, float max)
{
  if (value > max)
  {
    return max;
  }
  else if (value < min)
  {
    return min;
  }
  return value;
}
