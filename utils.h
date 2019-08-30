#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "types.h"

uint16_t switch_endian(uint16_t x);
classfile read_class_file(FILE *fp);
void cf_convert_endian(classfile *cf);
void print_class_file_summary(classfile *cf);
