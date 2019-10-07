#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "types.h"

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

void read_class_file(classfile *cf, FILE *fp);

void read_constant_pool(FILE *fp, cp_info cp[], int cpsize);
void read_constant_pool_entry(FILE *fp, cp_info *cp);

void read_fields(FILE *fp, field_info fields[], uint16_t fields_count, cp_info *cp);
void read_field_entry(FILE *fp, field_info *field, cp_info *cp);

void read_methods(FILE *fp, method_info methods[], uint16_t methods_count, cp_info *cp);
void read_method_entry(FILE *fp, method_info *method, cp_info *cp);

void read_attributes(FILE *fp, attribute_info attributes[], uint16_t attributes_count, cp_info *cp);
void read_attribute_info(FILE *fp, attribute_info *ptr, cp_info *cp);

void read_code_attribute(Code_attribute *ptr, FILE *fp, cp_info *cp);
void read_constantvalue_attribute(ConstantValue_attribute *ptr, FILE *fp);
void read_exceptions_attribute(Exceptions_attribute *ptr, FILE *fp);
void read_linenumbertable_attribute(LineNumberTable_attribute *ptr, FILE *fp);
void read_sourcefile_attribute(SourceFile_attribute *ptr, FILE *fp);

char *get_cp_string(cp_info *cp, uint16_t index);

void print_class_file_summary(classfile *cf);
void print_cp_detail(classfile *cf);

void deinit_cp_entry(cp_info *ptr);
void deinit_constant_pool(cp_info cp[], uint16_t cpsize);
void deinit_class_file(classfile *cf);

void deinit_fields(field_info fields[], uint16_t fields_count, cp_info *cp);
void deinit_field_entry(field_info *ptr, cp_info *cp);

void deinit_methods(method_info methods[], uint16_t method_count, cp_info *cp);
void deinit_method_entry(method_info *ptr, cp_info *cp);

void deinit_attributes(attribute_info attributes[], uint16_t attributes_count, cp_info *cp);
void deinit_attribute_info(attribute_info *ptr, cp_info *cp);

void deinit_code_attribute(Code_attribute *ptr, cp_info *cp);
void deinit_exceptions_attribute(Exceptions_attribute *ptr);
void deinit_linenumbertable_attribute(LineNumberTable_attribute *ptr);
