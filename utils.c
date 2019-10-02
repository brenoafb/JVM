#include "utils.h"

uint16_t switch_endian_16(uint16_t x) {
  return (x >> 8) | ((x << 8) & 0xff);
}

uint16_t switch_endian_32(uint32_t x) {
  return ((x >> 24)& 0xff)      |
	 ((x << 8) & 0xff0000)  |
	 ((x >> 8) & 0xff00)    |
	 ((x << 24)& 0xff000000);
}
