/**
 * @file classfile.h
 * @brief Leitor / Exibidor
 * File containing the definition of a classfile, structure created from the data 
 * read from a .class file, and functions with the purpose of reading from the file (read), 
 * display the classfile created (print), retrieve of values from a created constant pool (get),
 * and free the memory allocated at the end of the programs execution.
 *
 */

#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "utils.h"
#include "types.h"
#include "access_flags.h"
#include "opcodes.h"

/**
 * Represents the class file.
 */
typedef struct {
  uint32_t magic;

  uint16_t minor_version;
  uint16_t major_version;

  uint16_t cpsize;
  cp_info *constant_pool; /* n=constant_pool_count-1 */

  uint16_t access_flags;

  uint16_t this_class;
  uint16_t super_class;

  uint16_t interfaces_count;
  CONSTANT_Class_info *interfaces; /* n=interfaces_count */

  uint16_t fields_count;
  field_info *fields; /* n=fieds_count */

  uint16_t methods_count;
  method_info *methods; /* n=methods_count */

  uint16_t attributes_count;
  attribute_info *attributes; /*n=attributes_count */
} classfile;

/**
 * Reads class file open in fp.
 * @param cf pointer to struct to which the data will be read to.
 * @param fp file pointer to open class file in read mode.
 */
void read_class_file(classfile *cf, FILE *fp);

/**
 * Reads the class file's constant pool.
 * @param fp file pointer situated at the first byte of the constant pool.
 * @param cp array to where the pool will be read.
 * @param cpsize size of the constant pool (as read from the class file).
 */
void read_constant_pool(FILE *fp, cp_info cp[], int cpsize);

/**
 * Read a single entry from the constant pool.
 */
void read_constant_pool_entry(FILE *fp, cp_info *cp);

/**
 * Read the interfaces table of the class file.
 */
void read_interfaces(FILE *fp, CONSTANT_Class_info interfaces[], uint16_t interfaces_count);

/**
 * Read the fields table of the class file.
 */
void read_fields(FILE *fp, field_info fields[], uint16_t fields_count, cp_info *cp);

/**
 * Read a single field entry from the fields table.
 */
void read_field_entry(FILE *fp, field_info *field, cp_info *cp);

/**
 * Read the methods table of the class file.
 */
void read_methods(FILE *fp, method_info methods[], uint16_t methods_count, cp_info *cp);

/**
 * Read a single method entry from the methods table.
 */
void read_method_entry(FILE *fp, method_info *method, cp_info *cp);

/**
 * Read class file attributes table.
 */
void read_attributes(FILE *fp, attribute_info attributes[], uint16_t attributes_count, cp_info *cp);

/**
 * Read a single entry from some attributes table.
 */
void read_attribute_info(FILE *fp, attribute_info *ptr, cp_info *cp);

/**
 * Read Code attribute.
 */
void read_code_attribute(Code_attribute *ptr, FILE *fp, cp_info *cp);

/**
 * Read ConstantValue attribute.
 */
void read_constantvalue_attribute(ConstantValue_attribute *ptr, FILE *fp);

/**
 * Read Exceptions attribute.
 */
void read_exceptions_attribute(Exceptions_attribute *ptr, FILE *fp);

/**
 * Read LineNumberTable attribute.
 */
void read_linenumbertable_attribute(LineNumberTable_attribute *ptr, FILE *fp);


void read_synthetic_attribute(attribute_info *ptr, FILE *fp);

void read_stackmaptable_attribute(StackMapTable_attribute *ptr, FILE *fp);

/**
 * Read SourceFile attribute.
 */
void read_sourcefile_attribute(SourceFile_attribute *ptr, FILE *fp);

/**
 * Read InnerClasses attribute.
 */
void read_innerclasses_attribute(InnerClasses_attribute *ptr, FILE *fp);

/**
 * Return string containing this class's name
 */
char *get_class_name(classfile *cf);

/**
 * Return string containing this class's name
 */
char *get_super_name(classfile *cf);

/**
 * Return pointer to string in constant pool table.
 * Entry in constant pool must have tag CONSTANT_Utf8.
 * Indices start at 1.
 */
char *get_cp_string(cp_info *cp, uint16_t index);

/**
 * Return pointer to string in constant pool table.
 * Entry in constant pool must have tag CONSTANT_Class.
 * Indices start at 1.
 */
char *get_class_name_string(cp_info *cp, uint16_t class_index);

/**
 * Return pointer to string in constant pool table, choice betweem descriptor(0) and name(1).
 * Entry in constant pool must have tag CONSTANT_NameAndType.
 * Indices start at 1.
 */
char *get_name_and_type_string(cp_info *cp, uint16_t index, uint8_t choice);

/**
 * Print class file summary.
 * i.e. Prints the values read but not the tables.
 */
void print_class_file_summary(classfile *cf);

/**
 * Print class file detail.
 */
void print_class_file_detail(classfile *cf);

/**
 * Print constant pool detail.
 * Prints the type of each entry.
 * If an entry has type Utf8, the corresponding string is printed.
 */
void print_cp_detail(classfile *cf);

void print_interfaces_detail(classfile *cf);

void print_fields_detail(classfile *cf);

void print_methods_detail(classfile *cf);

void print_attributes_detail(attribute_info *ptr, cp_info *cp);

void print_code_attribute(Code_attribute *ptr, cp_info *cp);

void print_linenumber_attribute(LineNumberTable_attribute *ptr);

void print_exception_attribute(Exceptions_attribute *ptr, cp_info *cp, struct ExcTable* excT);

void print_synthetic_attribute(Synthetic_attribute* ptr, cp_info *cp);

void print_innerclasses_attribute(InnerClasses_attribute *ptr,cp_info *cp);

void print_stackmaptable_attribute(StackMapTable_attribute *ptr);
/**
 * Deinitializes a single constant pool entry.
 */
void deinit_cp_entry(cp_info *ptr);

/**
 * Deinitializes the constant pool.
 */
void deinit_constant_pool(cp_info cp[], uint16_t cpsize);

/**
 * Denitializes the class file struct.
 */
void deinit_class_file(classfile *cf);

/**
 * Deinitializes interfaces table.
 */
void deinit_interfaces(CONSTANT_Class_info *interfaces);

/**
 * Deinitializes fields table.
 * @param cp points to a valid constant pool (i.e. read, not deinitialized)
 */
void deinit_fields(field_info fields[], uint16_t fields_count, cp_info *cp);

/**
 * Deinitializes single field entry.
 * @param cp points to a valid constant pool (i.e. read, not deinitialized)
 */
void deinit_field_entry(field_info *ptr, cp_info *cp);

/**
 * Deinitializes methods table.
 * @param cp points to a valid constant pool (i.e. read, not deinitialized)
 */
void deinit_methods(method_info methods[], uint16_t method_count, cp_info *cp);

/**
 * Deinitializes single method entry.
 * @param cp points to a valid constant pool (i.e. read, not deinitialized)
 */
void deinit_method_entry(method_info *ptr, cp_info *cp);

/**
 * Deinitializes attributes table
 * @param cp points to a valid constant pool (i.e. read, not deinitialized)
 */
void deinit_attributes(attribute_info attributes[], uint16_t attributes_count, cp_info *cp);

/**
 * Deinitializes single attribute entry.
 * @param cp points to a valid constant pool (i.e. read, not deinitialized)
 */
void deinit_attribute_info(attribute_info *ptr, cp_info *cp);

/**
 * Deinitializes Code attribute entry.
 * @param cp points to a valid constant pool (i.e. read, not deinitialized)
 */
void deinit_code_attribute(Code_attribute *ptr, cp_info *cp);

/**
 * Deinitializes Exceptions attribute entry.
 * @param cp points to a valid constant pool (i.e. read, not deinitialized)
 */
void deinit_exceptions_attribute(Exceptions_attribute *ptr);

/**
 * Deinitializes LineNumberTable attribute entry.
 * @param cp points to a valid constant pool (i.e. read, not deinitialized)
 */
void deinit_linenumbertable_attribute(LineNumberTable_attribute *ptr);

/**
 * Deinitializes InnerClasses attribute entry.
 * @param cp points to a valid constant pool (i.e. read, not deinitialized)
 */
void deinit_innerclasses_attribute(InnerClasses_attribute *ptr);

/**
* Montagem da versão da classe
*/
void print_java_version (uint16_t major,  uint16_t minor);

/**
* Printa um elemento referenciado da constant pool
*/
void print_cp_element (cp_info *cp, uint16_t i);