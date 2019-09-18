#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "types.h"

uint16_t switch_endian(uint16_t x);
classfile read_class_file(FILE *fp);
void read_constant_pool(FILE *fp, cp_info cp[], int cpsize);
void read_constant_pool_entry(FILE *fp, cp_info *cp);
void cf_convert_endian(classfile *cf);
void print_class_file_summary(classfile *cf);

void deinit_cp_entry(cp_info *ptr);
void deinit_constant_pool(constant_pool *cp);
void deinit_class_file(classfile *cf);
