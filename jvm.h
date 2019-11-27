#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
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
  bool jmp;
} JVM;

void init_jvm(JVM *jvm);
void deinit_jvm(JVM *jvm);

/* Load the classfile into the jvm's MethodArea */
void jvm_load_class(JVM *jvm, classfile *cf);

/* Set the current class and current method members */
void jvm_load_method(JVM *jvm, uint32_t class_index, uint32_t method_index);

classfile *jvm_get_current_class(JVM *jvm);

char *jvm_get_current_class_name(JVM *jvm);

method_info *jvm_get_current_method(JVM *jvm);

char *jvm_get_current_method_name(JVM *jvm);

/* Creates a class with the current method and pushes it into the frame stack */
void jvm_push_frame(JVM *jvm);

/* Pop the current frame off the stack and free all its resources */
void jvm_pop_frame(JVM *jvm);

/* Return a pointer to the frame on top of the stack */
Frame *jvm_peek_frame(JVM *jvm);

/* Run one jvm cycle */
/* Returns 0 when return is called, 1 otherwise */
int jvm_cycle(JVM *jvm);

/* Run until the end */
void jvm_run(JVM *jvm);

/* Load current method into frame and run it */
void jvm_run_method(JVM *jvm);

/* Returns whether jvm is currently running main method */
int jvm_in_main(JVM *jvm);

typedef void (*operation)(Frame *, uint32_t, uint32_t);

void nop(Frame *f, uint32_t a0, uint32_t a1);

void ldc(Frame *f, uint32_t a0, uint32_t a1);

void istore(Frame *f, uint32_t a0, uint32_t a1);
void istore_0(Frame *f, uint32_t a0, uint32_t a1);
void istore_1(Frame *f, uint32_t a0, uint32_t a1);
void istore_2(Frame *f, uint32_t a0, uint32_t a1);
void istore_3(Frame *f, uint32_t a0, uint32_t a1);

void iload(Frame *f, uint32_t a0, uint32_t a1);
void iload_0(Frame *f, uint32_t a0, uint32_t a1);
void iload_1(Frame *f, uint32_t a0, uint32_t a1);
void iload_2(Frame *f, uint32_t a0, uint32_t a1);
void iload_3(Frame *f, uint32_t a0, uint32_t a1);

void iadd(Frame *f, uint32_t a0, uint32_t a1);

void return_func(Frame *f, uint32_t a0, uint32_t a1);

void invokevirtual(Frame *f, uint32_t a0, uint32_t a1);

void getstatic(Frame *f, uint32_t a0, uint32_t a1);

void ldc_w(Frame *f, uint32_t a0, uint32_t a1);
void ldc2_w(Frame *f, uint32_t a0, uint32_t a1);

void dstore(Frame *f, uint32_t a0, uint32_t a1);
void dstore_0(Frame *f, uint32_t a0, uint32_t a1);
void dstore_1(Frame *f, uint32_t a0, uint32_t a1);
void dstore_2(Frame *f, uint32_t a0, uint32_t a1);
void dstore_3(Frame *f, uint32_t a0, uint32_t a1);

void dload(Frame *f, uint32_t a0, uint32_t a1);
void dload_0(Frame *f, uint32_t a0, uint32_t a1);
void dload_1(Frame *f, uint32_t a0, uint32_t a1);
void dload_2(Frame *f, uint32_t a0, uint32_t a1);
void dload_3(Frame *f, uint32_t a0, uint32_t a1);

void dadd(Frame *f, uint32_t a0, uint32_t a1);
void dsub(Frame *f, uint32_t a0, uint32_t a1);
void ddiv(Frame *f, uint32_t a0, uint32_t a1);
void dmul(Frame *f, uint32_t a0, uint32_t a1);
void dneg(Frame *f, uint32_t a0, uint32_t a1);
void drem(Frame *f, uint32_t a0, uint32_t a1);

void bipush(Frame *f, uint32_t a0, uint32_t a1);

void iconst_0(Frame *f, uint32_t a0, uint32_t a1);
void iconst_1(Frame *f, uint32_t a0, uint32_t a1);
void iconst_2(Frame *f, uint32_t a0, uint32_t a1);
void iconst_3(Frame *f, uint32_t a0, uint32_t a1);

void if_icmpeq(Frame *f, uint32_t a0, uint32_t a1);
void if_icmpne(Frame *f, uint32_t a0, uint32_t a1);
void if_icmplt(Frame *f, uint32_t a0, uint32_t a1);
void if_icmpge(Frame *f, uint32_t a0, uint32_t a1);
void if_icmpgt(Frame *f, uint32_t a0, uint32_t a1);
void if_icmple(Frame *f, uint32_t a0, uint32_t a1);

void fconst_0(Frame *f, uint32_t a0, uint32_t a1);
void fconst_1(Frame *f, uint32_t a0, uint32_t a1);
void fconst_2(Frame *f, uint32_t a0, uint32_t a1);

void dstore(Frame *f, uint32_t a0, uint32_t a1);
void fstore_0(Frame *f, uint32_t a0, uint32_t a1);
void fstore_1(Frame *f, uint32_t a0, uint32_t a1);
void fstore_2(Frame *f, uint32_t a0, uint32_t a1);
void fstore_3(Frame *f, uint32_t a0, uint32_t a1);

extern operation optable[N_OPS];
extern int opargs[N_OPS];
