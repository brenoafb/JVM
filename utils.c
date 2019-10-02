#include "utils.h"

uint16_t switch_endian_16(uint16_t x) {
  uint16_t tmp = x;
  tmp >>= 8;
  x <<= 8;
  return x + tmp;
}

uint16_t switch_endian_32(uint32_t x) {
  uint16_t lo = x;
  uint16_t hi = (x >> 8);
  lo = switch_endian_16(lo);
  hi = switch_endian_16(hi);

  return (hi << 8) + lo;
}
