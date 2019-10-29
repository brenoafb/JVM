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
};

int opargs[N_OPS] = {
		     [OP_ldc] = 1,

};

void init_jvm(JVM *jvm) {
  jvm->pc = 0;
  jvm->frame_index = -1; /* no frames initially */
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

/* Load the classfile into the jvm's MethodArea */
void jvm_load_class(JVM *jvm, classfile *cf) {
  method_area_load_class(jvm->method_area, cf);
}

/* Set the current class and current method members */
void jvm_load_method(JVM *jvm, uint32_t class_index, uint32_t method_index) {
  jvm->current_class_index = class_index;
  jvm->current_method_index = method_index;
}

/* Load current method into frame and run it */
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
    uint32_t a[8];
    int i;
    for (i = 0; i < opargs[opcode]; i++) {
      a[i] = code->code[jvm->pc++];
    }
    optable[opcode](f, a[0], a[1]);
    if (opcode == OP_return) break;
    jvm->pc++;
  }
}

void nop(Frame *f, uint32_t a0, uint32_t a1) {
  /* do nothing */
  return;
}

void ldc(Frame *f, uint32_t a0, uint32_t a1) {
  /* push item from runtime constant pool */
  uint8_t tag = f->cp[a0].tag;
  printf("ldc: flag of #%d is %d\n", a0, tag);
  /* TODO push the correct item */
  push_stack(f, 0xbeef);
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
