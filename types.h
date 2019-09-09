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

typedef struct {
  uint8_t tag;
  uint8_t *info;
} cp_info;

typedef struct {
  uint32_t magic;

  uint16_t minor_version;
  uint16_t major_version;

  uint16_t cpsize;
  cp_info *constant_pool; // n=constant_pool_count-1

  uint16_t access_flags;

  uint16_t this_class;
  uint16_t super_class;

  uint16_t interfaces_count;
  uint16_t *interfaces; // n=interfaces_count

  uint16_t fields_count;
  field_info *fields; // n=fieds_count

  uint16_t methods_count;
  method_info *methods; // n=methods_count

  uint16_t attributes_count;
  attribute_info *attributes; //n=attributes_count
} classfile;

