/*
 * A few macros to compare values
 */

#include <raylib.h>

#define CLRCMP(c1, c2) (((Color)c1).r == ((Color)c2).r &&\
  ((Color)c1).g == ((Color)c2).g &&\
  ((Color)c1).b == ((Color)c2).b)
#define CLRCMPA(c1, c2) (((Color)c1).r == ((Color)c2).r &&\
  ((Color)c1).g == ((Color)c2).g &&\
  ((Color)c1).b == ((Color)c2).b &&\
  ((Color)c1).a == ((Color)c2).a)

#define VEC2CMP(v1, v2) (((Vector2)v1).x == ((Vector2)v2).x &&\
  ((Vector2)v1).y == ((Vector2)v2).y &&\
  ((Vector2)v1).z == ((Vector2)v2).z)
