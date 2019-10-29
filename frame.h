#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "classfile.h"

typedef struct Frame {
  uint32_t n_locals;      /* computed at compile time             */
  int32_t *locals;       /* array of local variables             */
  uint32_t n_operands;    /* computed at compile time             */
  int32_t *operands;      /* stack of operands                    */
  uint32_t i;             /* top of stack index                   */
  cp_info *cp;            /* reference to constant pool of class  */
} Frame;

void init_frame(Frame *f, uint32_t n_locals, uint32_t n_operands, cp_info *cp);
void deinit_frame(Frame *f);

void push_stack(Frame *f, int32_t operand);
int32_t pop_stack(Frame *f);
int32_t peek_stack(Frame *f);
