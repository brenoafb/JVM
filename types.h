#pragma once
#include <stdint.h>
#include "constant_info.h"

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

typedef struct {
  uint16_t constantvalue_index;
} ConstantValue_attribute;

typedef struct {
  uint16_t max_stack;
  uint16_t max_locals;
  uint32_t code_length;
  uint8_t *code;  /* n=code_length */
  uint16_t exception_table_length;

  struct ExcTable{
  uint16_t start_pc;
  uint16_t end_pc;
  uint16_t handler_pc;
  uint16_t catch_type;
  } *exception_table;  /* n=exception_table_length */

  uint16_t attributes_count;
  struct attribute_info *attributes;  /* n=attributes_count */
} Code_attribute;

typedef struct {
  uint16_t number_of_exceptions;
  uint16_t *exception_index_table; /* n=number_of_exceptions */
} Exceptions_attribute;

typedef struct {
  uint16_t line_number_table_length;
  struct LineNTable{
    uint16_t start_pc;
    uint16_t line_number;
  } *line_number_table;
} LineNumberTable_attribute;

typedef struct {
  uint16_t index;
} SourceFile_attribute;

typedef struct {
  uint16_t index;
  uint32_t length;
} Synthetic_attribute;

typedef struct {
  uint16_t number_of_classes;
  struct {
    uint16_t inner_class_info_index;
    uint16_t outer_class_info_index;
    uint16_t inner_name_index;
    uint16_t inner_class_access_flags;
  } *classes; /* n=number_of_classes */
} InnerClasses_attribute;

typedef struct attribute_info {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  union {
    ConstantValue_attribute    constantvalue;
    Code_attribute             code;
    Exceptions_attribute       exceptions;
    LineNumberTable_attribute  linenumbertable;
    SourceFile_attribute       sourcefile;
    Synthetic_attribute synthetic;
    InnerClasses_attribute     innerclasses;
  } info;
} attribute_info;

typedef struct {
  uint16_t access_flags;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t attributes_count;
  attribute_info *attributes; /*n=attributes_count */
} field_info;

typedef struct {
  uint16_t access_flags;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t attributes_count;
  attribute_info *attributes; /*n=attributes_count */
} method_info;
