/**
 * @file utils.h
 * @brief Utils functions
 * File containing functions that help reading the archive .class.
 *
 */

#pragma once
#include <stdint.h>
#include <stdio.h>

/**
 * Returns the 16-bit input with switched endianness.
 */
uint16_t switch_endian_16(uint16_t x);

/**
 * Returns the 32-bit input with switched endianness.
 */
uint32_t switch_endian_32(uint32_t x);

/**
 * Reads a 8-bit value from fp.
 */
uint8_t read_u1(FILE *fp);

/**
 * Reads a big endian 16-bit value from fp and switches its endianness.
 */
uint16_t read_u2(FILE *fp);

/**
 * Reads a big endian 32-bit value from fp and switches its endianness.
 */
uint32_t read_u4(FILE *fp);
