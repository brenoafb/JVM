#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "classfile.h"

typedef struct Frame {
  void *jvm;               /* pointer to respective jvm reference  */
  uint32_t n_locals;       /* computed at compile time             */
  int32_t *locals;         /* array of local variables             */
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
