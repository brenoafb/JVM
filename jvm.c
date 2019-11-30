#include "jvm.h"

operation optable[N_OPS] = {
			    [OP_nop] = nop,
			    [OP_ldc] = ldc,
			    [OP_istore] = istore,
			    [OP_istore_1] = istore_1,
			    [OP_istore_2] = istore_2,
			    [OP_istore_3] = istore_3,
			    [OP_iload] = iload,
			    [OP_iload_1] = iload_1,
			    [OP_iload_2] = iload_2,
			    [OP_iload_3] = iload_3,
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
			    [OP_drem] = drem,
			    [OP_bipush] = bipush,
			    [OP_iconst_0] = iconst_0,
			    [OP_iconst_1] = iconst_1,
			    [OP_iconst_2] = iconst_2,
			    [OP_iconst_3] = iconst_3,
			    [OP_if_icmpeq] = if_icmpeq,
			    [OP_if_icmpne] = if_icmpne,
			    [OP_if_icmplt] = if_icmplt,
			    [OP_if_icmpge] = if_icmpge,
			    [OP_if_icmpgt] = if_icmpgt,
			    [OP_if_icmple] = if_icmple,
};

int opargs[N_OPS] = {
		     [OP_if_icmpeq] = 2,
		     [OP_if_icmpne] = 2,
		     [OP_if_icmplt] = 2,
		     [OP_if_icmpge] = 2,
		     [OP_if_icmpgt] = 2,
		     [OP_if_icmple] = 2,
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
  jvm->jmp = false;
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
  init_frame(f, jvm, code->max_locals, code->max_stack, class->constant_pool);
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
  int flag = 1;                  /* will be set to 0 if returns from main in this cycle */
  Frame *f = jvm_peek_frame(jvm);
  classfile *class = jvm->method_area->classes[jvm->current_class_index];
  method_info *method = &class->methods[jvm->current_method_index];
  Code_attribute *code = &method->attributes[0].info.code;

  uint32_t opcode = code->code[jvm->pc];
  jvm->jmp = false;

#ifdef DEBUG
  printf("%d: 0x%x (%d)\n", jvm->pc, opcode, opargs[opcode]);
#endif

  uint32_t a[2];
  int i;
  for (i = 0; i < opargs[opcode]; i++) {
    a[i] = code->code[jvm->pc+i+1];
#ifdef DEBUG
    printf("load a%d: %d\n", i, a[i]);
#endif
  }
  optable[opcode](f, a[0], a[1]);
  if (opcode == OP_return && jvm_in_main(jvm)) {
#ifdef DEBUG
    printf("frame->i: %d\n", f->i);
    if (f->i > 0) printf("Final value in stack: %d (0x%x)\n", peek_stack(f), peek_stack(f));
#endif

    flag = 0;
  }
  if (!jvm->jmp) jvm->pc += opargs[opcode] + 1;
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
  init_frame(f, jvm, code->max_locals, code->max_stack, class->constant_pool);

#ifdef DEBUG
  printf("Current class: %s\n", get_class_name(jvm->method_area->classes[0]));
  printf("Current method: %s\n", get_cp_string(class->constant_pool, method->name_index));
  printf("Current method descriptor: %s\n", get_cp_string(class->constant_pool, method->descriptor_index));
  printf("Max locals:%d\nMax stack: %d\n", code->max_locals, code->max_stack);
#endif

  while (1) {
    uint32_t opcode = code->code[jvm->pc];

#ifdef DEBUG
    printf("%d: 0x%x (%d)\n", jvm->pc, opcode, opargs[opcode]);
#endif

    uint8_t a[2];
    int i;
    for (i = 0; i < opargs[opcode]; i++) {
      a[i] = code->code[jvm->pc+i+1];

#ifdef DEBUG
      printf("load a%d: %d\n", i, a[i]);
#endif
    }
    optable[opcode](f, a[0], a[1]);
    if (opcode == OP_return) {
#ifdef DEBUG
      printf("frame->i: %d\n", f->i);
      if (f->i > 0) printf("Final value in stack: %d (0x%x)\n", peek_stack(f), peek_stack(f));
#endif
      break;
    }
    jvm->pc += opargs[opcode] + 1;
  }

  deinit_frame(f);
  free(f);
}

int jvm_in_main(JVM *jvm) {
  Frame *f = jvm_peek_frame(jvm);
  classfile *class = jvm->method_area->classes[jvm->current_class_index];
  method_info *method = &class->methods[jvm->current_method_index];
  char *str = get_cp_string(f->cp, method->name_index);
  return strcmp(str, "main") == 0;
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
#ifdef DEBUG
    printf("Push %d from cp\n", f->cp[a0].info.integer_info.bytes);
#endif

    push_stack(f, f->cp[a0].info.integer_info.bytes);
    break;
  case CONSTANT_Float:
#ifdef DEBUG
    printf("Push %f from cp\n", f->cp[a0].info.float_info.bytes);
#endif

    push_stack(f, f->cp[a0].info.float_info.bytes);
    break;
  case CONSTANT_String:
    index = f->cp[a0].info.string_info.string_index;
    str = get_cp_string(f->cp, index);

#ifdef DEBUG
    printf("Push \'%s\' from cp\n", str);
#endif

    push_stack(f, str);
  default:
    break;
  }
}

void istore(Frame *f, uint32_t a0, uint32_t a1) {
  /* store int into local variable a0 */
  int32_t op = pop_stack(f);
  f->locals[a0] = op;
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

void iload(Frame *f, uint32_t a0, uint32_t a1) {
  /* Load int from local variable a0 */
  int32_t op = f->locals[a0];
  push_stack(f, op);
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

void iload_3(Frame *f, uint32_t a0, uint32_t a1) {
  /* Load int from local variable 3 */
  int32_t op = f->locals[3];
  push_stack(f, op);
}

void iadd(Frame *f, uint32_t a0, uint32_t a1) {
  /* add int */
  push_stack(f, pop_stack(f) + pop_stack(f));
}

void return_func(Frame *f, uint32_t a0, uint32_t a1) {
  /* nothing to do for now */
#ifdef DEBUG
  printf("return\n");
#endif
}

void invokevirtual(Frame *f, uint32_t a0, uint32_t a1) {
  uint32_t index = (a0 << 8) | a1;
  CONSTANT_Methodref_info methodref_info = f->cp[index].info.methodref_info;
  uint16_t class_index = methodref_info.class_index;
  uint16_t name_and_type_index = methodref_info.name_and_type_index;
  char *name = get_name_and_type_string(f->cp, name_and_type_index, 1);
  char *type = get_name_and_type_string(f->cp, name_and_type_index, 0);

#ifdef DEBUG
  printf("invokevirtual: Methodref\t");
  printf("class: %s, name: %s, type: %s\n", get_class_name_string(f->cp, class_index),
	 name, type);
#endif

  if (strcmp(name, "println") == 0) {
    if (strcmp(type, "(Ljava/lang/String;)V") == 0) {
      /* print string */
      char *str = pop_stack(f);
#ifdef DEBUG
      printf("println(String): \'%s\'\n", str);
#else
      printf("%s\n", str);
#endif

    } else if (strcmp(type, "(I)V") == 0) {
      /* print int */
      uint64_t value = pop_stack(f);
      int32_t integer = *((int32_t *) (&value));

#ifdef DEBUG
      printf("println(Int): %d\n", integer);
#else
      printf("%d\n", integer);
#endif
    } else if (strcmp(type, "(D)V") == 0) {
      /* print double */
      uint64_t pop1 = pop_stack(f);
      uint64_t pop2 = pop_stack(f);
      uint64_t x = (pop1 << 32) | pop2;
      double db = *((double *) &x);
#ifdef DEBUG
      printf("println(double): %f\n", db);
#else
      printf("%f\n", db);
#endif
    }
    /* pop getstatic dummy value (view getstatic definition) */
    uint32_t dummy = pop_stack(f);
#ifdef DEBUG
    printf("dummy: 0x%x\n", dummy);
#endif
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
    push_stack(f, 0xcc0de);
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
#ifdef DEBUG
    printf("ldc_w: Push %d from cp\n", f->cp[index].info.integer_info.bytes);
#endif
    push_stack(f, f->cp[index].info.integer_info.bytes);
    break;
  case CONSTANT_Float:
#ifdef DEBUG
    printf("ldc_w: Push %f from cp\n", f->cp[index].info.float_info.bytes);
#endif
    push_stack(f, f->cp[index].info.float_info.bytes);
    break;
  case CONSTANT_String:
    cp_index = f->cp[index].info.string_info.string_index;
    str = get_cp_string(f->cp, cp_index);

#ifdef DEBUG
    printf("ldc_w: Push \'%s\' from cp\n", str);
#endif

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
    low_bytes = f->cp[index].info.long_info.low_bytes;
    push_stack(f, low_bytes);
    high_bytes = f->cp[index].info.long_info.high_bytes;
    push_stack(f, high_bytes);
#ifdef DEBUG
    printf("ldc2_w: Push %ld from cp\n", value);
#endif
    break;
  case CONSTANT_Double:
    low_bytes = f->cp[index].info.double_info.low_bytes;
    push_stack(f, low_bytes);
    high_bytes = f->cp[index].info.double_info.high_bytes;
    push_stack(f, high_bytes);
#ifdef DEBUG
    printf("ldc2_w: Push %lf from cp\n", value);
#endif
    break;
  default:
    break;
  }
  return;
}


void dstore_1(Frame *f, uint32_t a0, uint32_t a1) {
  /* store a double into local variable 1 and 2 */
  uint64_t half_n_1 = pop_stack(f);
  uint64_t half_n_2 = pop_stack(f);

  memcpy(f->locals + 1, &half_n_1, 4);
  memcpy(f->locals + 2, &half_n_2, 4);

  return;
}

void dstore_2(Frame *f, uint32_t a0, uint32_t a1) {
  /* store a double into local variable 2 and 3 */
  uint64_t half_n_1 = pop_stack(f);
  uint64_t half_n_2 = pop_stack(f);

  memcpy(f->locals + 2, &half_n_1, 4);
  memcpy(f->locals + 3, &half_n_2, 4);
  return;
}

void dstore_3(Frame *f, uint32_t a0, uint32_t a1) {
  /* store a double into local variable 3 and 4 */
  uint64_t half_n_1 = pop_stack(f);
  uint64_t half_n_2 = pop_stack(f);

  memcpy(f->locals + 3, &half_n_1, 4);
  memcpy(f->locals + 4, &half_n_2, 4);
  return;
}


void dload_1(Frame *f, uint32_t a0, uint32_t a1) {
  /* load double from local variable 1 and 2*/
  uint64_t half_n_1 = f->locals[1];
  uint64_t half_n_2 = f->locals[2];

  push_stack(f, half_n_2);
  push_stack(f, half_n_1);

  return;
}

void dload_2(Frame *f, uint32_t a0, uint32_t a1) {
  /* load double from local variable 2 and 3*/
  uint64_t half_n_1 = f->locals[2];
  uint64_t half_n_2 = f->locals[3];

  push_stack(f, half_n_2);
  push_stack(f, half_n_1);
  return;
}

void dload_3(Frame *f, uint32_t a0, uint32_t a1) {
  /* load double from local variable 3 and 4*/
  uint64_t half_n_1 = f->locals[3];
  uint64_t half_n_2 = f->locals[4];

  push_stack(f, half_n_2);
  push_stack(f, half_n_1);
  return;
}


void dadd(Frame *f, uint32_t a0, uint32_t a1) {
  double d1 = pop_stack_double(f);
  double d2 = pop_stack_double(f);
  double result = d1 + d2;
  push_stack_double(f, result);
}

void dsub(Frame *f, uint32_t a0, uint32_t a1) {
  double d1 = pop_stack_double(f);
  double d2 = pop_stack_double(f);
  double result = d1 - d2;
  push_stack_double(f, result);
}

void ddiv(Frame *f, uint32_t a0, uint32_t a1) {
  double d1 = pop_stack_double(f);
  double d2 = pop_stack_double(f);
  double result = d1 / d2;
  push_stack_double(f, result);
}

void dmul(Frame *f, uint32_t a0, uint32_t a1) {
  double d1 = pop_stack_double(f);
  double d2 = pop_stack_double(f);
  double result = d1 * d2;
  push_stack_double(f, result);
}
void dneg(Frame *f, uint32_t a0, uint32_t a1) {
  double d1 = pop_stack_double(f);
  double result = -d1;
  push_stack_double(f, result);
}

void drem(Frame *f, uint32_t a0, uint32_t a1) {
  double d1 = pop_stack_double(f);
  double d2 = pop_stack_double(f);
  int q = d1/d2;
  double result = d1 - (d2 * q);
  push_stack_double(f, result);
}

void bipush(Frame *f, uint32_t a0, uint32_t a1) {
  /* TODO */
  char byte = a0;
  int32_t sign_ext = byte;
  uint64_t value = *((uint64_t *) (&sign_ext));
  push_stack(f, value);
}

void iconst_0(Frame *f, uint32_t a0, uint32_t a1) {
  push_stack(f, 0);
}

void iconst_1(Frame *f, uint32_t a0, uint32_t a1) {
  push_stack(f, 1);
}

void iconst_2(Frame *f, uint32_t a0, uint32_t a1) {
  push_stack(f, 2);
}

void iconst_3(Frame *f, uint32_t a0, uint32_t a1) {
  push_stack(f, 3);
}

void if_icmpeq(Frame *f, uint32_t a0, uint32_t a1) {
  uint32_t pop1 = pop_stack(f);
  uint32_t pop2 = pop_stack(f);

  int32_t value2 = *((int32_t *) (&pop1));
  int32_t value1 = *((int32_t *) (&pop2));

  if (value1 == value2) {
    uint16_t offset = (a0 << 8) | a1;
    JVM *jvm = f->jvm;
    uint16_t new_addr = jvm->pc + offset;
#ifdef DEBUG
    printf("if_icmpeq: set pc to 0x%x (%u)\n", new_addr, new_addr);
#endif
    jvm->pc = new_addr;
    jvm->jmp = true;
  }
}

void if_icmpne(Frame *f, uint32_t a0, uint32_t a1) {
  uint32_t pop1 = pop_stack(f);
  uint32_t pop2 = pop_stack(f);

  int32_t value2 = *((int32_t *) (&pop1));
  int32_t value1 = *((int32_t *) (&pop2));

  if (value1 != value2) {
    uint16_t offset = (a0 << 8) | a1;
    JVM *jvm = f->jvm;
    uint16_t new_addr = jvm->pc + offset;
#ifdef DEBUG
    printf("if_icmpeq: set pc to 0x%x (%u)\n", new_addr, new_addr);
#endif
    jvm->pc = new_addr;
    jvm->jmp = true;
  }
}

void if_icmplt(Frame *f, uint32_t a0, uint32_t a1) {
  uint32_t pop1 = pop_stack(f);
  uint32_t pop2 = pop_stack(f);

  int32_t value2 = *((int32_t *) (&pop1));
  int32_t value1 = *((int32_t *) (&pop2));

  if (value1 < value2) {
    uint16_t offset = (a0 << 8) | a1;
    JVM *jvm = f->jvm;
    uint16_t new_addr = jvm->pc + offset;
#ifdef DEBUG
    printf("if_icmpeq: set pc to 0x%x (%u)\n", new_addr, new_addr);
#endif
    jvm->pc = new_addr;
    jvm->jmp = true;
  }
}

void if_icmpge(Frame *f, uint32_t a0, uint32_t a1) {
  uint32_t pop1 = pop_stack(f);
  uint32_t pop2 = pop_stack(f);

  int32_t value2 = *((int32_t *) (&pop1));
  int32_t value1 = *((int32_t *) (&pop2));

  if (value1 >= value2) {
    uint16_t offset = (a0 << 8) | a1;
    JVM *jvm = f->jvm;
    uint16_t new_addr = jvm->pc + offset;
#ifdef DEBUG
    printf("if_icmpge: set pc to 0x%x (%u)\n", new_addr, new_addr);
#endif
    jvm->pc = new_addr;
    jvm->jmp = true;
  }
}

void if_icmpgt(Frame *f, uint32_t a0, uint32_t a1) {
  uint32_t pop1 = pop_stack(f);
  uint32_t pop2 = pop_stack(f);

  int32_t value2 = *((int32_t *) (&pop1));
  int32_t value1 = *((int32_t *) (&pop2));

  if (value1 > value2) {
    uint16_t offset = (a0 << 8) | a1;
    JVM *jvm = f->jvm;
    uint16_t new_addr = jvm->pc + offset;
#ifdef DEBUG
    printf("if_icmpeq: set pc to 0x%x (%u)\n", new_addr, new_addr);
#endif
    jvm->pc = new_addr;
    jvm->jmp = true;
  }
}

void if_icmple(Frame *f, uint32_t a0, uint32_t a1) {
  uint32_t pop1 = pop_stack(f);
  uint32_t pop2 = pop_stack(f);

  int32_t value2 = *((int32_t *) (&pop1));
  int32_t value1 = *((int32_t *) (&pop2));

  if (value1 <= value2) {
    uint16_t offset = (a0 << 8) | a1;
    JVM *jvm = f->jvm;
    uint16_t new_addr = jvm->pc + offset;
#ifdef DEBUG
    printf("if_icmpeq: set pc to 0x%x (%u)\n", new_addr, new_addr);
#endif
    jvm->pc = new_addr;
    jvm->jmp = true;
  }
}
