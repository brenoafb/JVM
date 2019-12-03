#pragma once

#include <stdint.h>

typedef union {
  int8_t bytefield;
  uint16_t charfield;
  int16_t shortfield;
  int32_t intfield;
  int64_t longfield;
  float floatfield;
  double doublefield;
  void *ptrfield;
} ObjectField;

typedef struct Object {
  int size;
  ObjectField *fields;
} Object;
