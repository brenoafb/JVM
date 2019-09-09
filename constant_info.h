#pragma once
#include <stdint.h>

#define CONSTANT_Class                7
#define CONSTANT_Fieldref             9
#define CONSTANT_Methodref           10
#define CONSTANT_InterfaceMethodref  11
#define CONSTANT_String               8
#define CONSTANT_Integer              3
#define CONSTANT_Float                4
#define CONSTANT_Long                 5
#define CONSTANT_Double               6
#define CONSTANT_NameAndType         12
#define CONSTANT_Utf8                 1

// id 7
typedef struct {
  uint8_t tag;
  uint16_t name_index;
} CONSTANT_Class_info;

// id 9
typedef struct {
  uint8_t tag;
  uint16_t class_index;
  uint16_t name_and_type_index;
} CONSTANT_Fieldref_info;

// id 10
typedef struct {
  uint8_t tag;
  uint16_t class_index;
  uint16_t name_and_type_index;
} CONSTANT_Methodref_info;

// id 11
typedef struct {
  uint8_t tag;
  uint16_t class_index;
  uint16_t name_and_type_index;
} CONSTANT_InterfaceMethodref_info;

// id 8
typedef struct {
  uint8_t tag;
  uint16_t string_index;
} CONSTANT_String_info;

// id 3
typedef struct {
  uint8_t tag;
  uint32_t bytes;
} CONSTANT_Integer_info;

// id 4
typedef struct {
  uint8_t tag;
  uint32_t bytes;
} CONSTANT_Float_info;

// id 5
typedef struct {
  uint8_t tag;
  uint32_t high_bytes;
  uint32_t low_bytes;
} CONSTANT_Long_info;

// id 6
typedef struct {
  uint8_t tag;
  uint32_t high_bytes;
  uint32_t low_bytes;
} CONSTANT_Double_info;

// id 12
typedef struct {
  uint8_t tag;
  uint16_t name_index;
  uint16_t descriptor_index;
} CONSTANT_NameAndType_info;

// id 1
typedef struct {
  uint8_t tag;
  uint16_t length;
  uint8_t *bytes
} CONSTANT_Utf8_info;
