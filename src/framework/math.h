#include <math.h>

#ifndef FRAMEWORK_MATH_H
#define FRAMEWORK_MATH_H

typedef struct Vec2 {
  float x;
  float y;
} Vec2;

inline Vec2 vec2_normalize(Vec2 v) {
  float length = sqrt(v.x * v.x + v.y * v.y);
  if(length != 0) {
    v.x /= length;
    v.y /= length;
  }
  return v;
};

inline Vec2 vec2_add(Vec2 a, Vec2 b) {
  return { a.x + b.x, a.y + b.y };;
}

inline Vec2 vec2_sub(Vec2 a, Vec2 b) {
  return { a.x - b.x, a.y - b.y };
}

inline Vec2 vec2_mul(Vec2 a, Vec2 b) {
  return { a.x * b.x, a.y * b.y };
}

inline Vec2 vec2_div(Vec2 a, Vec2 b) {
  return { a.x / b.x, a.y / b.y };
}
#endif 
