#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "classfile.h"
#include "types.h"

#define MAX_CLASSES 32

typedef struct MethodArea {
  uint32_t n_classes;
  classfile *classes[MAX_CLASSES];
} MethodArea;

void init_method_area(MethodArea *ma);
void deinit_method_area(MethodArea *ma);
void method_area_load_class(MethodArea *ma, classfile *cf);
