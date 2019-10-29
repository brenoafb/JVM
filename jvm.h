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

/* Set the current class and current method members */
void jvm_load_method(JVM *jvm, uint32_t class_index, uint32_t method_index);

/* Load current method into frame and run it */
void jvm_run_method(JVM *jvm);

typedef void (*operation)(Frame *, uint32_t, uint32_t);

void nop(Frame *f, uint32_t a0, uint32_t a1);
void ldc(Frame *f, uint32_t a0, uint32_t a1);
void istore_1(Frame *f, uint32_t a0, uint32_t a1);
void istore_2(Frame *f, uint32_t a0, uint32_t a1);
void istore_3(Frame *f, uint32_t a0, uint32_t a1);
void iload_1(Frame *f, uint32_t a0, uint32_t a1);
void iload_2(Frame *f, uint32_t a0, uint32_t a1);
void iadd(Frame *f, uint32_t a0, uint32_t a1);
void return_func(Frame *f, uint32_t a0, uint32_t a1);

extern operation optable[N_OPS];
extern int opargs[N_OPS];
