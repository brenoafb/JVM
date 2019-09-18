#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
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
  attribute_info **attributes; //n=attributes_count
} classfile;

classfile read_class_file(FILE *fp);
void read_constant_pool(FILE *fp, cp_info cp[], int cpsize);
void read_constant_pool_entry(FILE *fp, cp_info *cp);
void cf_convert_endian(classfile *cf);
void print_class_file_summary(classfile *cf);

void deinit_cp_entry(cp_info *ptr);
void deinit_constant_pool(cp_info cp[], uint16_t cpsize);
void deinit_class_file(classfile *cf);
