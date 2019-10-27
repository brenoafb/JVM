#include "frame.h"

void init_frame(Frame *f, uint32_t n_locals, uint32_t n_operands, cp_info *cp) {
  assert(f);
  f->n_locals = n_locals;
  f->locals = calloc(sizeof(uint32_t), n_locals);
  assert(f->locals);
  f->n_operands = n_operands;
  f->operands = calloc(sizeof(uint32_t), n_operands);
  assert(f->operands);
  f->i = 0;
  f->cp = cp;
}

void deinit_frame(Frame *f) {
  assert(f);
  free(f->locals);
  free(f->operands);
}
