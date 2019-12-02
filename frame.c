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

void push_stack_float(Frame *f, float x) {
  uint32_t hex = *((uint32_t *) (& x));
  push_stack(f, hex);
}

float pop_stack_float(Frame *f) {
  uint32_t hex = pop_stack(f);
  return *((float *) (& hex));
}

void push_stack_int(Frame *f, int32_t x) {
  uint64_t push = *((uint64_t *) (&x));
  push_stack(f, push);
}

int32_t pop_stack_int(Frame *f) {
  uint64_t pop = pop_stack(f);
  int32_t int_value = *((int32_t *) (&pop));
  return int_value;
}

void push_stack_pointer(Frame *f, void *ptr) {
  push_stack(f, (uint64_t) ptr);
}

void *pop_stack_pointer(Frame *f) {
  uint64_t pop = pop_stack(f);
  return (void *) pop;
}

void frame_set_local(Frame *f, uint32_t index, uint64_t value);
  assert(index < f->n_locals);
  f->locals[index] = value;
}

uint64_t frame_get_local(Frame *f, uint32_t index) {
  assert(index < f->n_locals);
  return f->locals[index];
}

void frame_set_local_int(Frame *f, uint32_t index, int32_t value) {
  uint64_t x = *((uint64_t *) (& value));
  frame_set_local(f, x, index);
}

int32_t frame_get_local_int(Frame *f, uint32_t index) {
  uint64_t x = frame_get_local(f, index);
  return *((int32_t *) (&x));
}

void frame_set_local_double(Frame *f, uint32_t index, double value) {
  uint64_t x = *((uint64_t *) (& value));
  frame_set_local(f, x, index);
}

double frame_get_local_double(Frame *f, uint32_t index) {
  uint64_t x = frame_get_local(f, index);
  return *((double *) (&x));
}

void frame_set_local_float(Frame *f, uint32_t index, float value) {
  uint64_t x = *((uint64_t *) (& value));
  frame_set_local(f, x, index);
}

float frame_get_local_float(Frame *f, uint32_t index) {
  uint64_t x = frame_get_local(f, index);
  return *((float *) (&x));
}

void frame_set_local_long(Frame *f, uint32_t index, int64_t value) {
  uint64_t x = *((uint64_t *) (& value));
  frame_set_local(f, x, index);
}

int64_t frame_get_local_long(Frame *f, uint32_t index) {
  uint64_t x = frame_get_local(f, index);
  return *((int64_t *) (&x));
}

void frame_set_local_pointer(Frame *f, uint32_t index, void *value) {
  frame_set_local(f, index, ((uint64_t) value));
}

void* frame_get_local_pointer(Frame *f, uint32_t index) {
  uint64_t x = frame_get_local(f, index);
  return *((void **) (&x));
}
