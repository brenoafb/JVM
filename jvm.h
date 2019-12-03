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
#define MAXHEAP    256

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
  bool ret;
  uint64_t retval;

  void *heap[MAXHEAP];
  int32_t heap_index;
} JVM;

void init_jvm(JVM *jvm);
void deinit_jvm(JVM *jvm);

/* Load the classfile into the jvm's MethodArea */
void jvm_load_classfile(JVM *jvm, classfile *cf);

/* Load class with name (if needed) into jvm's MethodArea */
void jvm_load_class(JVM *jvm, char *class_name);

/* Set class which owns current method being run */
/* Assumes class is already loaded */
void jvm_set_current_class(JVM *jvm, char *class_name);

/* Set current method to run */
void jvm_set_current_method(JVM *jvm, char *method_name);

/* Set the current class and current method members */
/* Assumes that the current class does contain the method required */
void jvm_load_method(JVM *jvm, uint32_t class_index, uint32_t method_index);

/* Returns a reference to the class which runs the method being run */
classfile *jvm_get_current_class(JVM *jvm);

/* Returns the name of the class which runs the method being run */
char *jvm_get_current_class_name(JVM *jvm);

/* Returns a reference to the method being run */
method_info *jvm_get_current_method(JVM *jvm);

/* Returns the name of the method being run */
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

/* Save current frame context */
void jvm_save_context(JVM *jvm);

/* Restore context to previous frame (callee) */
void jvm_restore_context(JVM *jvm);

/* Add new pointer to jvm's heap table */
void jvm_add_to_heap(JVM *jvm, void *ptr);

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

void isub(Frame *f, uint32_t a0, uint32_t a1);
void iadd(Frame *f, uint32_t a0, uint32_t a1);

void return_func(Frame *f, uint32_t a0, uint32_t a1);
void ireturn(Frame *f, uint32_t a0, uint32_t a1);

void invokevirtual(Frame *f, uint32_t a0, uint32_t a1);
void invokestatic(Frame *f, uint32_t a0, uint32_t a1);

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
void iconst_4(Frame *f, uint32_t a0, uint32_t a1);
void iconst_5(Frame *f, uint32_t a0, uint32_t a1);
void iconst_m1(Frame *f, uint32_t a0, uint32_t a1);

void if_icmpeq(Frame *f, uint32_t a0, uint32_t a1);
void if_icmpne(Frame *f, uint32_t a0, uint32_t a1);
void if_icmplt(Frame *f, uint32_t a0, uint32_t a1);
void if_icmpge(Frame *f, uint32_t a0, uint32_t a1);
void if_icmpgt(Frame *f, uint32_t a0, uint32_t a1);
void if_icmple(Frame *f, uint32_t a0, uint32_t a1);

void lconst_0(Frame *f, uint32_t a0, uint32_t a1);
void lconst_1(Frame *f, uint32_t a0, uint32_t a1);

void lstore(Frame *f, uint32_t a0, uint32_t a1);
void lstore_0(Frame *f, uint32_t a0, uint32_t a1);
void lstore_1(Frame *f, uint32_t a0, uint32_t a1);
void lstore_2(Frame *f, uint32_t a0, uint32_t a1);
void lstore_3(Frame *f, uint32_t a0, uint32_t a1);

void lload(Frame *f, uint32_t a0, uint32_t a1);
void lload_0(Frame *f, uint32_t a0, uint32_t a1);
void lload_1(Frame *f, uint32_t a0, uint32_t a1);
void lload_2(Frame *f, uint32_t a0, uint32_t a1);
void lload_3(Frame *f, uint32_t a0, uint32_t a1);

void ladd(Frame *f, uint32_t a0, uint32_t a1);

void iinc(Frame *f, uint32_t a0, uint32_t a1);

void goto_func(Frame *f, uint32_t a0, uint32_t a1);

void fconst_0(Frame *f, uint32_t a0, uint32_t a1);
void fconst_1(Frame *f, uint32_t a0, uint32_t a1);
void fconst_2(Frame *f, uint32_t a0, uint32_t a1);

void fstore(Frame *f, uint32_t a0, uint32_t a1);
void fstore_0(Frame *f, uint32_t a0, uint32_t a1);
void fstore_1(Frame *f, uint32_t a0, uint32_t a1);
void fstore_2(Frame *f, uint32_t a0, uint32_t a1);
void fstore_3(Frame *f, uint32_t a0, uint32_t a1);

void fload(Frame *f, uint32_t a0, uint32_t a1);
void fload_0(Frame *f, uint32_t a0, uint32_t a1);
void fload_1(Frame *f, uint32_t a0, uint32_t a1);
void fload_2(Frame *f, uint32_t a0, uint32_t a1);
void fload_3(Frame *f, uint32_t a0, uint32_t a1);

void fsub(Frame *f, uint32_t a0, uint32_t a1);
void fadd(Frame *f, uint32_t a0, uint32_t a1);
void fdiv(Frame *f, uint32_t a0, uint32_t a1);

void ifeq(Frame *f, uint32_t a0, uint32_t a1);
void ifne(Frame *f, uint32_t a0, uint32_t a1);
void iflt(Frame *f, uint32_t a0, uint32_t a1);
void ifge(Frame *f, uint32_t a0, uint32_t a1);
void ifgt(Frame *f, uint32_t a0, uint32_t a1);
void ifle(Frame *f, uint32_t a0, uint32_t a1);

void i2f(Frame *f, uint32_t a0, uint32_t a1);
void i2d(Frame *f, uint32_t a0, uint32_t a1);

void i2b(Frame *f, uint32_t a0, uint32_t a1);
void i2c(Frame *f, uint32_t a0, uint32_t a1);
void i2l(Frame *f, uint32_t a0, uint32_t a1);
void i2s(Frame *f, uint32_t a0, uint32_t a1);

void sipush(Frame *f, uint32_t a0, uint32_t a1);

int tableswitch(JVM *jvm);
void aload(Frame *f, uint32_t a0, uint32_t a1);
void aload_0(Frame *f, uint32_t a0, uint32_t a1);
void aload_1(Frame *f, uint32_t a0, uint32_t a1);
void aload_2(Frame *f, uint32_t a0, uint32_t a1);
void aload_3(Frame *f, uint32_t a0, uint32_t a1);

void astore(Frame *f, uint32_t a0, uint32_t a1);
void astore_0(Frame *f, uint32_t a0, uint32_t a1);
void astore_1(Frame *f, uint32_t a0, uint32_t a1);
void astore_2(Frame *f, uint32_t a0, uint32_t a1);
void astore_3(Frame *f, uint32_t a0, uint32_t a1);

void newarray(Frame *f, uint32_t a0, uint32_t a1);

void aastore(Frame *f, uint32_t a0, uint32_t a1);
void aaload(Frame *f, uint32_t a0, uint32_t a1);

void iastore(Frame *f, uint32_t a0, uint32_t a1);
void iaload(Frame *f, uint32_t a0, uint32_t a1);

void fastore(Frame *f, uint32_t a0, uint32_t a1);
void faload(Frame *f, uint32_t a0, uint32_t a1);

void lastore(Frame *f, uint32_t a0, uint32_t a1);
void laload(Frame *f, uint32_t a0, uint32_t a1);

void dastore(Frame *f, uint32_t a0, uint32_t a1);
void daload(Frame *f, uint32_t a0, uint32_t a1);

void bastore(Frame *f, uint32_t a0, uint32_t a1);
void baload(Frame *f, uint32_t a0, uint32_t a1);

void d2f(Frame *f, uint32_t a0, uint32_t a1);
void d2i(Frame *f, uint32_t a0, uint32_t a1);
void d2l(Frame *f, uint32_t a0, uint32_t a1);

void f2d(Frame *f, uint32_t a0, uint32_t a1);
void f2i(Frame *f, uint32_t a0, uint32_t a1);
void f2l(Frame *f, uint32_t a0, uint32_t a1);

void l2d(Frame *f, uint32_t a0, uint32_t a1);
void l2f(Frame *f, uint32_t a0, uint32_t a1);
void l2i(Frame *f, uint32_t a0, uint32_t a1);

void multianewarray(Frame *f, uint32_t a0, uint32_t a1);


extern operation optable[N_OPS];
extern int opargs[N_OPS];

void jvm_alloc_array_2d(JVM *jvm, int32_t counts[], uint32_t size);
void jvm_alloc_array_3d(JVM *jvm, int32_t counts[], uint32_t size);
