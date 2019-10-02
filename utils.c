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

uint8_t read_u1(FILE *fp) {
  uint8_t x;
  fread(&x, sizeof(uint8_t), 1, fp);
  return x;
}

uint16_t read_u2(FILE *fp) {
  uint16_t x;
  fread(&x, sizeof(uint16_t), 1, fp);
  return switch_endian_16(x);
}

uint32_t read_u4(FILE *fp) {
  uint32_t x;
  fread(&x, sizeof(uint32_t), 1, fp);
  return switch_endian_32(x);
}
