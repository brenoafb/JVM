#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

#define CONSTANT_Utf8                 1
#define CONSTANT_Integer              3
#define CONSTANT_Float                4
#define CONSTANT_Long                 5
#define CONSTANT_Double               6
#define CONSTANT_Class                7
#define CONSTANT_String               8
#define CONSTANT_Fieldref             9
#define CONSTANT_Methodref           10
#define CONSTANT_InterfaceMethodref  11
#define CONSTANT_NameAndType         12

#define CONSTANT_read_verify(type)      \
  assert(ptr);                          \
  assert(fp);                           \

/* id 7 */
typedef struct {
  uint16_t name_index;
} CONSTANT_Class_info;

/* id 9 */
typedef struct {
  uint16_t class_index;
  uint16_t name_and_type_index;
} CONSTANT_Fieldref_info;

/* id 10 */
typedef struct {
  uint16_t class_index;
  uint16_t name_and_type_index;
} CONSTANT_Methodref_info;

/* id 11 */
typedef struct {
  uint16_t class_index;
  uint16_t name_and_type_index;
} CONSTANT_InterfaceMethodref_info;

/* id 8 */
typedef struct {
  uint16_t string_index;
} CONSTANT_String_info;

/* id 3 */
typedef struct {
  uint32_t bytes;
} CONSTANT_Integer_info;

/* id 4 */
typedef struct {
  uint32_t bytes;
} CONSTANT_Float_info;

/* id 5 */
typedef struct {
  uint32_t high_bytes;
  uint32_t low_bytes;
} CONSTANT_Long_info;

/* id 6 */
typedef struct {
  uint32_t high_bytes;
  uint32_t low_bytes;
} CONSTANT_Double_info;

/* id 12 */
typedef struct {
  uint16_t name_index;
  uint16_t descriptor_index;
} CONSTANT_NameAndType_info;

/* id 1 */
typedef struct {
  uint16_t length;
  uint8_t *bytes;
} CONSTANT_Utf8_info;

void read_Class_info(CONSTANT_Class_info *ptr, FILE *fp);
void read_Fieldref_info(CONSTANT_Fieldref_info *ptr, FILE *fp);
void read_NameAndType_info(CONSTANT_NameAndType_info *ptr, FILE *fp);
void read_Utf8_info(CONSTANT_Utf8_info *ptr, FILE *fp);
void read_Methodref_info(CONSTANT_Methodref_info *ptr, FILE *fp);
void read_InterfaceMethodref_info(CONSTANT_InterfaceMethodref_info *ptr, FILE *fp);
void read_String_info(CONSTANT_String_info *ptr, FILE *fp);
void read_Integer_info(CONSTANT_Integer_info *ptr, FILE *fp);
void read_Float_info(CONSTANT_Float_info *ptr, FILE *fp);
void read_Long_info(CONSTANT_Long_info *ptr, FILE *fp);
void read_Double_info(CONSTANT_Double_info *ptr, FILE *fp);
