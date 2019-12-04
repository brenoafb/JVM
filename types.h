/**
 * @file types.h
 * @brief Constant pool and Attributes definitions
 * File containing the definitions of the constant pool, attributes, fields and methods.
 *
 */

#pragma once
#include <stdint.h>
#include "constant_info.h"

/**
 * @brief Constant.
 *
 * Union to store generically a constant information, including its value.
 */
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

/**
 * @brief Info of a constant pool element.
 *
 * Structure that stores the tag and the info of a constant
 */
typedef struct {
  uint8_t tag;
  CONSTANT_info info;
} cp_info;

/**
 * @brief Attribute ConstantValue values and informations.
 *
 * Structure that stores information about a ConstantValue attribute
 */
typedef struct {
  uint16_t constantvalue_index;
} ConstantValue_attribute;

/**
 * @brief Attribute ConstantValue values and informations.
 *
 * Structure that stores information about a ConstantValue attribute
 */
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

/**
 * @brief Attribute ConstantValue
 *
 * Structure that stores information about a ConstantValue attribute
 */
typedef struct {
  uint16_t number_of_exceptions;
  uint16_t *exception_index_table; /* n=number_of_exceptions */
} Exceptions_attribute;

/**
 * @brief Attribute LineNumberTable
 *
 * Structure that stores information about a LineNumberTable attribute
 */
typedef struct {
  uint16_t line_number_table_length;
  struct LineNTable{
    uint16_t start_pc;
    uint16_t line_number;
  } *line_number_table;
} LineNumberTable_attribute;

/**
 * @brief Attribute SourceFile
 *
 * Structure that stores information (index) about a SourceFile attribute
 */
typedef struct {
  uint16_t index;
} SourceFile_attribute;

/**
 * @brief Attribute Synthetic
 *
 * Structure that represents a Synthetic attribute
 */
typedef struct {
} Synthetic_attribute;

/**
 * @brief Attribute InnerClasses
 *
 * Structure that stores information about an InnerClasses attribute
 */
typedef struct {
  uint16_t number_of_classes;
  struct {
    uint16_t inner_class_info_index;
    uint16_t outer_class_info_index;
    uint16_t inner_name_index;
    uint16_t inner_class_access_flags;
  } *classes; /* n=number_of_classes */
} InnerClasses_attribute;

/**
 * @brief Attribute StackMapTable
 *
 * Structure that stores information about a StackMapTable attribute
 */
typedef struct {
  uint16_t index;
  uint32_t length;
  uint16_t n_entries;
  /*TODO stack_map_frame*/
} StackMapTable_attribute;

/**
 * @brief Attribute general info.
 *
 * Structure that stores information about a Attribute of any type generically, 
 * including their common fields (ex: name_index, length)
 */
typedef struct attribute_info {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  union {
    ConstantValue_attribute    constantvalue;
    Code_attribute             code;
    Exceptions_attribute       exceptions;
    LineNumberTable_attribute  linenumbertable;
    SourceFile_attribute       sourcefile;
    Synthetic_attribute        synthetic;
    InnerClasses_attribute     innerclasses;
    StackMapTable_attribute stackmaptable;
  } info;
} attribute_info;

/**
 * @brief Field.
 *
 * Structure that stores information about a Field
 */
typedef struct {
  uint16_t access_flags;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t attributes_count;
  attribute_info *attributes; /*n=attributes_count */
} field_info;

/**
 * @brief Method.
 *
 * Structure that stores information about a Method
 */
typedef struct {
  uint16_t access_flags;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t attributes_count;
  attribute_info *attributes; /*n=attributes_count */
} method_info;
