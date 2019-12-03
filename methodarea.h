#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "classfile.h"
#include "types.h"

#define MAX_CLASSES 32
#define BUFSIZE 256

typedef struct MethodArea {
  uint32_t n_classes;
  classfile *classes[MAX_CLASSES];
} MethodArea;

void init_method_area(MethodArea *ma);
void deinit_method_area(MethodArea *ma);
void method_area_load_class(MethodArea *ma, char *class_name);
void method_area_load_classfile(MethodArea *ma, classfile *cf);

int method_area_class_lookup(MethodArea *ma, char *class_name);
int method_area_method_lookup(MethodArea *ma, int class_index, char *method_name, char *type);
