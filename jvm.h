#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "classfile.h"
#include "frame.h"
#include "methodarea.h"
#include "opcodes.h"

#define MAX_FRAMES 32

typedef struct JVM {
  uint32_t pc;
  Frame *frames[MAX_FRAMES];
  int32_t frame_index;    /* top of frame stack index */
  /* uint8_t *heap; */
  MethodArea *method_area;
  /* NativeMethodArea nma; */
  int32_t current_class_index;
  int32_t current_method_index;
} JVM;

void init_jvm(JVM *jvm);
void deinit_jvm(JVM *jvm);

/* Load the classfile into the jvm's MethodArea */
void jvm_load_class(JVM *jvm, classfile *cf);
