#pragma once
#include <stdint.h>
#include "constant_info.h"

typedef struct {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint8_t *info; // n=attribute_length
} attribute_info;

typedef struct {
  uint16_t access_flags;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t attributes_count;
  attribute_info *attributes; //n=attributes_count
} field_info;

typedef struct {
  uint16_t access_flags;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t attributes_count;
  attribute_info *attributes; //n=attributes_count
} method_info;

typedef union {
  CONSTANT_Class_info               class_info;
  CONSTANT_Fieldref_info            fieldref_info;
  CONSTANT_Methodref_info           methodref_info;
  CONSTANT_InterfaceMethodref_info  interfacemethodref_info;
  CONSTANT_String_info              string_info;
  CONSTANT_Integer_info             integer_info;
  CONSTANT_Float_info               float_info;
  CONSTANT_Long_info                long_info;
  CONSTANT_Double_info              double_info;
  CONSTANT_NameAndType_info         nameandtype_info;
  CONSTANT_Utf8_info                utf8_info;
} CONSTANT_info;

typedef struct {
  uint8_t tag;
  CONSTANT_info info;
} cp_info;

