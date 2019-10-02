#pragma once
#include <stdint.h>
#include <stdio.h>

uint16_t switch_endian_16(uint16_t x);
uint32_t switch_endian_32(uint32_t x);

uint8_t read_u1(FILE *fp);
uint16_t read_u2(FILE *fp);
uint32_t read_u4(FILE *fp);
