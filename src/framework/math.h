#include <math.h>

#ifndef FRAMEWORK_MATH_H
#define FRAMEWORK_MATH_H

typedef struct Vec2 {
  float x;
  float y;
} Vec2;

/*
 * Normalizes a Vec2
 *
 * @param v The Vec2 to normalize
 *
 * @return The normalized Vec2
 */
inline Vec2 vec2_normalize(Vec2 v) {
  float length = (float)sqrt(v.x * v.x + v.y * v.y);
  if(length != 0) {
    v.x /= length;
    v.y /= length;
  }
  return v;
};

/*
 * Adds two Vec2
 *
 * @param a The first Vec2
 * @param b The second Vec2
 *
 * @return The sum of the two Vec2s
 */
inline Vec2 vec2_add(Vec2 a, Vec2 b) {
  return { a.x + b.x, a.y + b.y };;
}

/*
 * Adds a Vec2 and a float
 *
 * @param a The Vec2
 * @param b The float
 *
 * @return The sum of the Vec2 and the float
 */
inline Vec2 vec2_add(Vec2 a, float b) {
  return { a.x + b, a.y + b };
}


/*
 * Subtracts two Vec2
 *
 * @param a The first Vec2
 * @param b The second Vec2
 *
 * @return The difference of the two Vec2s
 */
inline Vec2 vec2_sub(Vec2 a, Vec2 b) {
  return { a.x - b.x, a.y - b.y };
}

/*
 * Subtracts a Vec2 and a float
 *
 * @param a The Vec2
 * @param b The float
 *
 * @return The difference of the Vec2 and the float
 */
inline Vec2 vec2_sub(Vec2 a, float b) {
  return { a.x - b, a.y - b };
}


/*
 * Multiplies two Vec2
 *
 * @param a The first Vec2
 * @param b The second Vec2
 *
 * @return The product of the two Vec2s
 */
inline Vec2 vec2_mul(Vec2 a, Vec2 b) {
  return { a.x * b.x, a.y * b.y };
}

/*
 * Multiplies a Vec2 and a float
 *
 * @param a The Vec2
 * @param b The float
 *
 * @return The product of the Vec2 and the float
 */
inline Vec2 vec2_mul(Vec2 a, float b) {
  return { a.x * b, a.y * b };
}

/*
 * Divides two Vec2
 *
 * @param a The first Vec2
 * @param b The second Vec2
 *
 * @return The quotient of the two Vec2s
 */
inline Vec2 vec2_div(Vec2 a, Vec2 b) {
  return { a.x / b.x, a.y / b.y };
}

/*
 * Divides a Vec2 and a float
 *
 * @param a The Vec2
 * @param b The float
 *
 * @return The quotient of the Vec2 and the float
 */
inline Vec2 vec2_div(Vec2 a, float b) {
  return { a.x / b, a.y / b };
}


/*
 * Compares two Vec2s
 *
 * @param a The first Vec2
 * @param b The second Vec2
 *
 * @return True if the two Vec2s are equal
 */
inline bool vec2_equals(Vec2 a, Vec2 b) {
  const float epsilon = 0.00001f;

  const bool x_equals = (a.x - b.x < epsilon) && (b.x - a.x < epsilon);
  const bool y_equals = (a.y - b.y < epsilon) && (b.y - a.y < epsilon);
  return x_equals && y_equals;
}


/*
 * Compares 2 floats
 * Why? https://en.wikipedia.org/wiki/Floating-point_error_mitigation
 *
 * @param a The first float
 * @param b The second float
 *
 * @return True if the floats are equal
 */
inline bool float_cmp(float a, float b) {
  const float epsilon = 0.00001f;
  return (a - b < epsilon) && (b - a < epsilon);
}
#endif 
