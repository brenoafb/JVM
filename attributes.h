#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "utils.h"

typedef struct {
  uint16_t constantvalue_index;
} ConstantValue_attribute;

typedef struct {
  uint16_t max_stack;
  uint16_t max_locals;
  uint32_t code_length;
  uint8_t *code;  // n=code_length
  uint16_t exception_table_length;

  struct {
  uint16_t start_pc;
  uint16_t end_pc;
  uint16_t handler_pc;
  uint16_t catch_type;
  } *exception_table;  // n=exception_table_length

  uint16_t attributes_count;
  // attribute_info *attributes;  // n=attributes_count
} Code_attribute;

typedef struct {
  uint16_t number_of_exceptions;
  uint16_t *exception_index_table; // n=number_of_exceptions
} Exceptions_attribute;

typedef struct {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  union {
    ConstantValue_attribute constant_value;
    Code_attribute code;
    Exceptions_attribute exceptions;
  } info;
} attribute_info;

void read_code_attribute(Code_attribute *ptr, FILE *fp);
void read_constant_value_attribute(ConstantValue_attribute *ptr, FILE *fp);
void read_exceptions_attribute(Exceptions_attribute *ptr, FILE *fp);
