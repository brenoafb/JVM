#include "utils.h"

uint16_t switch_endian(uint16_t x) {
  uint16_t tmp = x;
  tmp >>= 8;
  x <<= 8;
  return x + tmp;
}

