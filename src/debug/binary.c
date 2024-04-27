#include <stdlib.h>

#include "binary.h"


char *hexdump(const void *buf, const size_t size) {
  static char hex[] = "0123456789abcdef";

  char *ptr = (char *)buf;

  char *str = malloc(size * 3 + 1);

  for (size_t i = 0; i < size; i++) {
    str[i * 3] = hex[(ptr[i] >> 4) & 0xf];
    str[i * 3 + 1] = hex[ptr[i] & 0xf];
    str[i * 3 + 2] = ' ';
  }

  str[size * 3] = 0;
  return str;
}
