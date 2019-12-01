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
} Frame;

void init_frame(Frame *f, void *jvm, uint32_t n_locals, uint32_t n_operands, cp_info *cp);
void deinit_frame(Frame *f);

void push_stack(Frame *f, uint64_t operand);
uint64_t pop_stack(Frame *f);
uint64_t peek_stack(Frame *f);

void push_stack_double(Frame *f, double d);
double pop_stack_double(Frame *f);

void push_stack_long(Frame *f, int64_t x);
int64_t pop_stack_long(Frame *f);
