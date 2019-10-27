#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "classfile.h"
#include "frame.h"
#include "methodarea.h"

typedef struct JVM {
  uint32_t pc;
  Frame *frames;
  uint32_t fi;    /* top of frame stack index */
  /* uint8_t *heap; */
  MethodArea *method_area;
  /* NativeMethodArea nma; */
  uint32_t current_class_index;
  uint32_t current_method_index;
} JVM;

void init_jvm(JVM *jvm);
void deinit_jvm(JVM *jvm);

/* Load the classfile into the jvm's MethodArea */
void load_class(JVM *jvm, classfile *cf);
