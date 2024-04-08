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

float LTMath::wrapf(float value, float min, float max)
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

int LTMath::clamp(int value, int min, int max)
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

float LTMath::clampf(float value, float min, float max)
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
