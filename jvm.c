#include "jvm.h"

operation optable[N_OPS] = {
			    [OP_nop] = nop,
			    [OP_ldc] = ldc,
			    [OP_istore_1] = istore_1,
			    [OP_istore_2] = istore_2,
			    [OP_istore_3] = istore_3,
			    [OP_iload_1] = iload_1,
			    [OP_iload_2] = iload_2,
			    [OP_iadd] = iadd,
			    [OP_return] = return_func,
			    [OP_invokevirtual] = invokevirtual,
			    [OP_getstatic] = getstatic,
			    [OP_ldc2w_w] = ldc2_w,
			    [OP_dstore_1] = dstore_1,
			    [OP_dstore_2] = dstore_2,
			    [OP_dstore_3] = dstore_3,
			    [OP_dload_1] = dload_1,
			    [OP_dload_2] = dload_2,
			    [OP_dload_3] = dload_3,
			    [OP_dadd] = dadd,
			    [OP_dsub] = dsub,
			    [OP_dmul] = dmul,
			    [OP_ddiv] = ddiv,
			    [OP_dneg] = dneg,
};

int opargs[N_OPS] = {
		     [OP_ldc] = 1,

};

void init_jvm(JVM *jvm) {
  jvm->pc = 0;
  jvm->frame_index = 0;
  jvm->method_area = calloc(sizeof(MethodArea), 1);
  init_method_area(jvm->method_area);
  jvm->current_class_index = -1;
  jvm->current_method_index = -1;
}

void deinit_jvm(JVM *jvm) {
  deinit_method_area(jvm->method_area);
  free(jvm->method_area);
  int i;
  for (i = 0; i < jvm->frame_index; i++) {
    free(jvm->frames[i]);
  }
}

void jvm_load_class(JVM *jvm, classfile *cf) {
  method_area_load_class(jvm->method_area, cf);
}

void jvm_load_method(JVM *jvm, uint32_t class_index, uint32_t method_index) {
  jvm->current_class_index = class_index;
  jvm->current_method_index = method_index;
}

void jvm_push_frame(JVM *jvm) {
  classfile *class = jvm->method_area->classes[jvm->current_class_index];
  method_info *method = &class->methods[jvm->current_method_index];
  Code_attribute *code = &method->attributes[0].info.code;
  Frame *f = calloc(sizeof(Frame), 1);
  init_frame(f, code->max_locals, code->max_stack, class->constant_pool);
  jvm->frames[jvm->frame_index++] = f;
}

void jvm_pop_frame(JVM *jvm) {
  Frame *f = jvm->frames[--jvm->frame_index];
  deinit_frame(f);
  free(f);
}

Frame *jvm_peek_frame(JVM *jvm) {
  if (jvm->frame_index == 0) return NULL;
  return jvm->frames[jvm->frame_index-1];
}

int jvm_cycle(JVM *jvm) {
  int flag = 1;
  Frame *f = jvm_peek_frame(jvm);
  classfile *class = jvm->method_area->classes[jvm->current_class_index];
  method_info *method = &class->methods[jvm->current_method_index];
  Code_attribute *code = &method->attributes[0].info.code;

  uint32_t opcode = code->code[jvm->pc];
  printf("%d: 0x%x (%d)\n", jvm->pc, opcode, opargs[opcode]);
  uint32_t a[2];
  int i;
  for (i = 0; i < opargs[opcode]; i++) {
    a[i] = code->code[jvm->pc+i+1];
    printf("load a%d: %d\n", i, a[i]);
  }
  optable[opcode](f, a[0], a[1]);
  if (opcode == OP_return) {
    printf("frame->i: %d\n", f->i);
    printf("Final value in stack: %d (0x%x)\n", peek_stack(f), peek_stack(f));
    flag = 0;
  }
  jvm->pc += opargs[opcode] + 1;
  return flag;
}

void jvm_run(JVM *jvm) {
  while (jvm_cycle(jvm));
}

void jvm_run_method(JVM *jvm) {
  classfile *class = jvm->method_area->classes[jvm->current_class_index];
  method_info *method = &class->methods[jvm->current_method_index];
  Code_attribute *code = &method->attributes[0].info.code;
  Frame *f = calloc(sizeof(Frame), 1);
  init_frame(f, code->max_locals, code->max_stack, class->constant_pool);

  printf("Current class: %s\n", get_class_name(jvm->method_area->classes[0]));
  printf("Current method: %s\n", get_cp_string(class->constant_pool, method->name_index));
  printf("Current method descriptor: %s\n", get_cp_string(class->constant_pool, method->descriptor_index));
  printf("Max locals:%d\nMax stack: %d\n", code->max_locals, code->max_stack);

  while (1) {
    uint32_t opcode = code->code[jvm->pc];
    printf("%d: 0x%x (%d)\n", jvm->pc, opcode, opargs[opcode]);
    uint32_t a[2];
    int i;
    for (i = 0; i < opargs[opcode]; i++) {
      a[i] = code->code[jvm->pc+i+1];
      printf("load a%d: %d\n", i, a[i]);
    }
    optable[opcode](f, a[0], a[1]);
    if (opcode == OP_return) {
      printf("frame->i: %d\n", f->i);
      printf("Final value in stack: %d (0x%x)\n", peek_stack(f), peek_stack(f));
      break;
    }
    jvm->pc += opargs[opcode] + 1;
  }

  deinit_frame(f);
  free(f);
}

void nop(Frame *f, uint32_t a0, uint32_t a1) {
  /* do nothing */
  return;
}

void ldc(Frame *f, uint32_t a0, uint32_t a1) {
  /* push item from runtime constant pool */
  uint8_t tag = f->cp[a0].tag;
  switch (tag) {
  case CONSTANT_Integer:
    printf("Push %d from cp\n", f->cp[a0].info.integer_info.bytes);
    push_stack(f, f->cp[a0].info.integer_info.bytes);
    break;
  default:
    break;
  }
}

void istore_1(Frame *f, uint32_t a0, uint32_t a1) {
  /* store int into local variable 1 */
  int32_t op = pop_stack(f);
  f->locals[1] = op;
}

void istore_2(Frame *f, uint32_t a0, uint32_t a1) {
  /* store int into local variable 2 */
  int32_t op = pop_stack(f);
  f->locals[2] = op;
}

void istore_3(Frame *f, uint32_t a0, uint32_t a1) {
  /* store int into local variable 3 */
  int32_t op = pop_stack(f);
  f->locals[3] = op;
}

void iload_1(Frame *f, uint32_t a0, uint32_t a1) {
  /* Load int from local variable 1 */
  int32_t op = f->locals[1];
  push_stack(f, op);
}

void iload_2(Frame *f, uint32_t a0, uint32_t a1) {
  /* Load int from local variable 2 */
  int32_t op = f->locals[2];
  push_stack(f, op);
}

void iadd(Frame *f, uint32_t a0, uint32_t a1) {
  /* add int */
  push_stack(f, pop_stack(f) + pop_stack(f));
}

void return_func(Frame *f, uint32_t a0, uint32_t a1) {
  /* nothing to do for now */
  printf("return\n");
}

void invokevirtual(Frame *f, uint32_t a0, uint32_t a1) {
  /* TODO */
  return;
}

void getstatic(Frame *f, uint32_t a0, uint32_t a1) {
  /* TODO */
  return;
}


void ldc2_w(Frame *f, uint32_t a0, uint32_t a1) {
  /* TODO */
  return;
}


void dstore_1(Frame *f, uint32_t a0, uint32_t a1) {
  /* TODO */
  return;
}

void dstore_2(Frame *f, uint32_t a0, uint32_t a1) {
  /* TODO */
  return;
}

void dstore_3(Frame *f, uint32_t a0, uint32_t a1) {
  /* TODO */
  return;
}


void dload_1(Frame *f, uint32_t a0, uint32_t a1) {
  /* TODO */
  return;
}

void dload_2(Frame *f, uint32_t a0, uint32_t a1) {
  /* TODO */
  return;
}

void dload_3(Frame *f, uint32_t a0, uint32_t a1) {
  /* TODO */
  return;
}


void dadd(Frame *f, uint32_t a0, uint32_t a1) {
  /* TODO */
  return;
}

void dsub(Frame *f, uint32_t a0, uint32_t a1) {
  /* TODO */
  return;
}

void ddiv(Frame *f, uint32_t a0, uint32_t a1) {
  /* TODO */
  return;
}

void dmul(Frame *f, uint32_t a0, uint32_t a1) {
  /* TODO */
  return;
}

void dneg(Frame *f, uint32_t a0, uint32_t a1) {
  /* TODO */
  return;
}
