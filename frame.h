#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "classfile.h"

typedef struct Frame {
  void *jvm;               /* pointer to respective jvm reference  */
  uint32_t n_locals;       /* computed at compile time             */
  uint64_t *locals;         /* array of local variables            */
  uint32_t n_operands;     /* computed at compile time             */
  uint64_t *operands;      /* stack of operands                    */
  uint32_t i;              /* top of stack index                   */
  cp_info *cp;             /* reference to constant pool of class  */
  uint32_t pc;             /* jvm's pc upon method call            */
  int32_t class_index;     /* class index in method area           */
  int32_t method_index;    /* method index in class                */
} Frame;

void init_frame(Frame *f, void *jvm, uint32_t n_locals, uint32_t n_operands, cp_info *cp,
		int32_t class_index, int32_t method_index);
void deinit_frame(Frame *f);

void push_stack(Frame *f, uint64_t operand);
uint64_t pop_stack(Frame *f);
uint64_t peek_stack(Frame *f);

void push_stack_double(Frame *f, double d);
double pop_stack_double(Frame *f);

void push_stack_long(Frame *f, int64_t x);
int64_t pop_stack_long(Frame *f);

void push_stack_float(Frame *f, float x);
float pop_stack_float(Frame *f);

void push_stack_int(Frame *f, int32_t x);
int32_t pop_stack_int(Frame *f);

void push_stack_pointer(Frame *f, void *ptr);
void *pop_stack_pointer(Frame *f);

void frame_set_local(Frame *f, uint32_t index, uint64_t value);
uint64_t frame_get_local(Frame *f, uint32_t index);

void frame_set_local_int(Frame *f, uint32_t index, int32_t value);
int32_t frame_get_local_int(Frame *f, uint32_t index);

void frame_set_local_double(Frame *f, uint32_t index, double value);
double frame_get_local_double(Frame *f, uint32_t index);

void frame_set_local_float(Frame *f, uint32_t index, float value);
float frame_get_local_float(Frame *f, uint32_t index);

void frame_set_local_long(Frame *f, uint32_t index, int64_t value);
int64_t frame_get_local_float(Frame *f, uint32_t index);
