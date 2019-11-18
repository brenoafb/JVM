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
          [OP_ldc_w] = ldc_w,
			    [OP_ldc2_w] = ldc2_w,
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
          [OP_iload] = 1,
          [OP_lload] = 1,
          [OP_fload] = 1,
          [OP_dload] = 1,
          [OP_aload] = 1,
          [OP_istore] = 1,
          [OP_lstore] = 1,
          [OP_fstore] = 1,
          [OP_dstore] = 1,
          [OP_astore] = 1,
          [OP_ret] = 1,
          [OP_bipush] = 1,
          [OP_newarray] = 1,
		      [OP_ldc_w] = 2,
		      [OP_ldc2_w] = 2,
		      [OP_getstatic] = 2,
          [OP_putstatic] = 2,
          [OP_getfield] = 2,
          [OP_putfield] = 2,
          [OP_invokevirtual] = 2,
          [OP_invokespecial] = 2,
          [OP_invokestatic] = 2,
          [OP_new] = 2,
          [OP_anewarray] = 2,
          [OP_checkcast] = 2,
          [OP_instanceof] = 2,
          [OP_iinc] = 2,
          [OP_sipush] = 2,
          [OP_goto] = 2,
          [OP_jsr] = 2,
          [OP_ifnull] = 2,
          [OP_ifnonnull] = 2,
          [OP_multianewarray] = 3,
          /*[OP_wide] = 3,*/
          [OP_invokeinterface] = 4,
          [OP_invokedynamic] = 4,
          [OP_goto_w] = 4,
          [OP_jsr_w] = 4,
          /*[OP_lookupswitch] = 8,
          [OP_tableswitch] = 16,*/

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
    uint8_t a[2];
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
  uint16_t index;
  char *str;
  /* push item from runtime constant pool */
  uint8_t tag = f->cp[a0].tag;
  switch (tag) {
  case CONSTANT_Integer:
    printf("Push %d from cp\n", f->cp[a0].info.integer_info.bytes);
    push_stack(f, f->cp[a0].info.integer_info.bytes);
    break;
  case CONSTANT_Float:
    printf("Push %f from cp\n", f->cp[a0].info.float_info.bytes);
    push_stack(f, f->cp[a0].info.float_info.bytes);
    break;
  case CONSTANT_String:
    index = f->cp[a0].info.string_info.string_index;
    str = get_cp_string(f->cp, index);
    printf("Push \'%s\' from cp\n", str);
    push_stack(f, str);
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
  uint32_t index = (a0 << 8) | a1;
  CONSTANT_Methodref_info methodref_info = f->cp[index].info.methodref_info;
  uint16_t class_index = methodref_info.class_index;
  uint16_t name_and_type_index = methodref_info.name_and_type_index;
  char *name = get_name_and_type_string(f->cp, name_and_type_index, 1);

  printf("invokevirtual: Methodref\t");
  printf("%s.%s:%s (#%d.#%d)\n", get_class_name_string(f->cp, class_index),
	 get_name_and_type_string(f->cp, name_and_type_index, 1),
	 get_name_and_type_string(f->cp, name_and_type_index, 0), class_index, name_and_type_index);

  if (strcmp(name, "println") == 0) {
    /* pop two arguments by default (placeholder) */
    /* first popped is string reference */
    char *str = pop_stack(f);
    printf("String printed is: \'%s\'\n", str);

    /* second popped is getstatic dummy value (see getstatic definition) */
    uint32_t dummy = pop_stack(f);
    printf("Dummy: %x\n", dummy);
  }

  return;
}

void getstatic(Frame *f, uint32_t a0, uint32_t a1) {
  /* TODO */
  uint32_t index = (a0 << 8) | a1;
  CONSTANT_Fieldref_info fieldref_info = f->cp[index].info.fieldref_info;
  uint16_t class_index = fieldref_info.class_index;
  uint16_t name_and_type_index = fieldref_info.name_and_type_index;

  char *class_name = get_class_name_string(f->cp, class_index);
  char *name = get_name_and_type_string(f->cp, name_and_type_index, 1);
  if ((strcmp(class_name, "java/lang/System") == 0)
      && (strcmp(name, "out") == 0)) {
    /* io operations will be handled by c code */
    /* push a dummy value onto the stack */
    push_stack(f, 0xbeefbeef);
  } else {
    /* TODO */
  }
  return;
}


void ldc_w(Frame *f, uint32_t a0, uint32_t a1) {
  uint16_t index, cp_index;
  char *str;

  index = (a0 << 8) + a1;
  /* push item from runtime constant pool */
  uint8_t tag = f->cp[index].tag;
  switch (tag) {
  case CONSTANT_Integer:
    printf("Push %d from cp\n", f->cp[index].info.integer_info.bytes);
    push_stack(f, f->cp[index].info.integer_info.bytes);
    break;
  case CONSTANT_Float:
    printf("Push %f from cp\n", f->cp[index].info.float_info.bytes);
    push_stack(f, f->cp[index].info.float_info.bytes);
    break;
  case CONSTANT_String:
    cp_index = f->cp[index].info.string_info.string_index;
    str = get_cp_string(f->cp, cp_index);
    printf("Push \'%s\' from cp\n", str);
    push_stack(f, str);
  default:
    break;
  }
  return;
}

void ldc2_w(Frame *f, uint32_t a0, uint32_t a1) {
  uint16_t index, cp_index;
  char *str;
  uint32_t high_bytes;
  uint32_t low_bytes;
  int64_t value = (((int64_t) high_bytes) << 32) + ((int64_t)low_bytes);

  index = (a0 << 8) + a1;
  /* push item from runtime constant pool */
  uint8_t tag = f->cp[index].tag;
  switch (tag) {
  case CONSTANT_Long:
    high_bytes = f->cp[index].info.long_info.high_bytes;
    push_stack(f, high_bytes);
    low_bytes = f->cp[index].info.long_info.low_bytes;
    push_stack(f, low_bytes);
    printf("Push %ld from cp\n", value);
    break;
  case CONSTANT_Double:
    high_bytes = f->cp[index].info.double_info.high_bytes;
    push_stack(f, high_bytes);
    low_bytes = f->cp[index].info.double_info.low_bytes;
    push_stack(f, low_bytes);
    printf("Push %lf from cp\n", value);
    break;
  default:
    break;
  }
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
