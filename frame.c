#include "frame.h"

void init_frame(Frame *f, void *jvm, uint32_t n_locals, uint32_t n_operands, cp_info *cp,
		int32_t class_index, int32_t method_index) {
  f->jvm = jvm;
  f->n_locals = n_locals;
  f->locals = calloc(sizeof(int64_t), n_locals);
  assert(f->locals);
  f->n_operands = n_operands;
  f->operands = calloc(sizeof(int64_t), n_operands);
  assert(f->operands);
  f->i = 0;
  f->cp = cp;

  f->class_index = class_index;
  f->method_index = method_index;
}

void deinit_frame(Frame *f) {
  free(f->locals);
  free(f->operands);
}

void push_stack(Frame *f, uint64_t operand) {
  assert(f->i < f->n_operands);
  f->operands[f->i++] = operand;
}

uint64_t pop_stack(Frame *f) {
  assert(f->i > 0);
  return f->operands[--f->i];
}

uint64_t peek_stack(Frame *f) {
  return f->operands[f->i];
}

void push_stack_double(Frame *f, double d) {
  uint64_t hex = *((uint64_t *) (& d));
  uint32_t hi = hex >> 32;
  uint32_t lo = hex;
  push_stack(f, lo);
  push_stack(f, hi);
}

double pop_stack_double(Frame *f) {
  uint64_t hi = pop_stack(f);
  uint64_t lo = pop_stack(f);
  uint64_t hex = (hi << 32) | lo;
  return *((double *)(& hex));
}

void push_stack_long(Frame *f, int64_t x) {
  uint64_t hex = *((uint64_t *) (& x));
  uint32_t hi = hex >> 32;
  uint32_t lo = hex;
  push_stack(f, lo);
  push_stack(f, hi);
}

int64_t pop_stack_long(Frame *f) {
  uint64_t hi = pop_stack(f);
  uint64_t lo = pop_stack(f);
  uint64_t hex = (hi << 32) | lo;
  return *((int64_t *)(& hex));
}
