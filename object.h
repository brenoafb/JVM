/**
 * @file object.h
 * @brief Object definitions
 * File containing the definitions necessary to create a object.
 *
 */
#pragma once

#include <stdint.h>

/**
 * @brief Field or Attribute of an Object.
 *
 * Union to store generically attributes values.
 */
typedef union {
  uint8_t boolfield;
  int8_t bytefield;
  uint16_t charfield;
  int16_t shortfield;
  int32_t intfield;
  int64_t longfield;
  float floatfield;
  double doublefield;
  void *ptrfield;
} ObjectField;

/**
 * @brief Object.
 *
 * Structure to store a object from a class.
 */
typedef struct Object {
  int size;
  ObjectField *fields; /**<Attributes */
} Object;
