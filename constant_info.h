/**
 * @file constant_info.h
 * @brief Constants definitions
 * File containing the definitions for each type of constant
 * and the structures with the information of the .class file main components.
 *
 */

#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

/**
 * @brief Info of type Class.
 *
 * Structure that stores specific information about a constant of type Class (id 7)
 */
/* id 7 */
typedef struct {
  uint16_t name_index;
} CONSTANT_Class_info;

/**
 * @brief Info of type Fieldref.
 *
 * Structure that stores specific information about a constant of type Fieldref (id 9)
 */
/* id 9 */
typedef struct {
  uint16_t class_index;
  uint16_t name_and_type_index;
} CONSTANT_Fieldref_info;

/**
 * @brief Info of type Methodref.
 *
 * Structure that stores specific information about a constant of type Methodref (id 10)
 */
/* id 10 */
typedef struct {
  uint16_t class_index;
  uint16_t name_and_type_index;
} CONSTANT_Methodref_info;

/**
 * @brief Info of type InterfaceMethodref.
 *
 * Structure that stores specific information about a constant of type InterfaceMethodref (id 11)
 */
/* id 11 */
typedef struct {
  uint16_t class_index;
  uint16_t name_and_type_index;
} CONSTANT_InterfaceMethodref_info;

/**
 * @brief Info of type String.
 *
 * Structure that stores specific information about a constant of type String (id 8)
 */
/* id 8 */
typedef struct {
  uint16_t string_index;
} CONSTANT_String_info;

/**
 * @brief Info of type Integer.
 *
 * Structure that stores specific information about a constant of type Integer (id 3)
 */
/* id 3 */
typedef struct {
  uint32_t bytes;
} CONSTANT_Integer_info;

/**
 * @brief Info of type Float.
 *
 * Structure that stores specific information about a constant of type Float (id 4)
 */
/* id 4 */
typedef struct {
  uint32_t bytes;
} CONSTANT_Float_info;

/**
 * @brief Info of type Long.
 *
 * Structure that stores specific information about a constant of type Long (id 5)
 */
/* id 5 */
typedef struct {
  uint32_t high_bytes;
  uint32_t low_bytes;
} CONSTANT_Long_info;

/**
 * @brief Info of type Double.
 *
 * Structure that stores specific information about a constant of type Double (id 6)
 */
/* id 6 */
typedef struct {
  uint32_t high_bytes;
  uint32_t low_bytes;
} CONSTANT_Double_info;

/**
 * @brief Info of type NameAndType.
 *
 * Structure that stores specific information about a constant of type Class (id 12)
 */
/* id 12 */
typedef struct {
  uint16_t name_index;
  uint16_t descriptor_index;
} CONSTANT_NameAndType_info;

/**
 * @brief Info of type Utf8.
 *
 * Structure that stores specific information about a constant of type Utf8 (id 1)
 */
/* id 1 */
typedef struct {
  uint16_t length;
  uint8_t *bytes;
} CONSTANT_Utf8_info;

/**
 * Get data from file and store in a Class_info structure.
 */
void read_Class_info(CONSTANT_Class_info *ptr, FILE *fp);

/**
 * Get data from file and store in a Fieldref_info structure.
 */
void read_Fieldref_info(CONSTANT_Fieldref_info *ptr, FILE *fp);

/**
 * Get data from file and store in a NameAndType_info structure.
 */
void read_NameAndType_info(CONSTANT_NameAndType_info *ptr, FILE *fp);

/**
 * Get data from file and store in a Utf8_info structure.
 */
void read_Utf8_info(CONSTANT_Utf8_info *ptr, FILE *fp);

/**
 * Get data from file and store in a Methodref_info structure.
 */
void read_Methodref_info(CONSTANT_Methodref_info *ptr, FILE *fp);

/**
 * Get data from file and store in a InterfaceMethodref_info structure.
 */
void read_InterfaceMethodref_info(CONSTANT_InterfaceMethodref_info *ptr, FILE *fp);

/**
 * Get data from file and store in a String_info structure.
 */
void read_String_info(CONSTANT_String_info *ptr, FILE *fp);

/**
 * Get data from file and store in a Integer_info structure.
 */
void read_Integer_info(CONSTANT_Integer_info *ptr, FILE *fp);

/**
 * Get data from file and store in a Float_info structure.
 */
void read_Float_info(CONSTANT_Float_info *ptr, FILE *fp);

/**
 * Get data from file and store in a Long_info structure.
 */
void read_Long_info(CONSTANT_Long_info *ptr, FILE *fp);

/**
 * Get data from file and store in a Double_info structure.
 */
void read_Double_info(CONSTANT_Double_info *ptr, FILE *fp);
