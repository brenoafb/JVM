#include "jvm.h"

operation optable[N_OPS] = {
			    [OP_nop] = nop,
			    [OP_ldc] = ldc,
			    [OP_istore] = istore,
	  [OP_istore_0] = istore_0,
			    [OP_istore_1] = istore_1,
			    [OP_istore_2] = istore_2,
			    [OP_istore_3] = istore_3,
			    [OP_iload] = iload,
			    [OP_iload_0] = iload_0,
			    [OP_iload_1] = iload_1,
			    [OP_iload_2] = iload_2,
			    [OP_iload_3] = iload_3,
			    [OP_iadd] = iadd,
			    [OP_isub] = isub,
			    [OP_return] = return_func,
			    [OP_ireturn] = ireturn,
			    [OP_invokevirtual] = invokevirtual,
			    [OP_invokestatic] = invokestatic,
			    [OP_getstatic] = getstatic,
			    [OP_ldc_w] = ldc_w,
			    [OP_ldc2_w] = ldc2_w,
	  [OP_dstore] = dstore,
	  [OP_dstore_0] = dstore_0,
			    [OP_dstore_1] = dstore_1,
			    [OP_dstore_2] = dstore_2,
			    [OP_dstore_3] = dstore_3,
	  [OP_dload] = dload,
	  [OP_dload_0] = dload_0,
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
			    [OP_lconst_0] = lconst_0,
			    [OP_lconst_1] = lconst_1,
			    [OP_lstore] = lstore,
			    [OP_lstore_0] = lstore_0,
			    [OP_lstore_1] = lstore_1,
			    [OP_lstore_2] = lstore_2,
			    [OP_lstore_3] = lstore_3,
			    [OP_lload] = lload,
			    [OP_lload_0] = lload_0,
			    [OP_lload_1] = lload_1,
			    [OP_lload_2] = lload_2,
			    [OP_lload_3] = lload_3,
			    [OP_ladd] = ladd,
			    [OP_iinc] = iinc,
			    [OP_goto] = goto_func,
			    [OP_fconst_0] = fconst_0,
			    [OP_fconst_1] = fconst_1,
			    [OP_fconst_2] = fconst_2,
			    [OP_fstore] = fstore,
			    [OP_fstore_0] = fstore_0,
			    [OP_fstore_1] = fstore_1,
			    [OP_fstore_2] = fstore_2,
			    [OP_fstore_3] = fstore_3,
			    [OP_fload] = fload,
			    [OP_fload_0] = fload_0,
			    [OP_fload_1] = fload_1,
			    [OP_fload_2] = fload_2,
			    [OP_fload_3] = fload_3,
			    [OP_fsub] = fsub,
			    [OP_fadd] = fadd,
			    [OP_fdiv] = fdiv,
			    [OP_ifeq] = ifeq,
			    [OP_ifne] = ifne,
			    [OP_iflt] = iflt,
			    [OP_ifge] = ifge,
			    [OP_ifgt] = ifgt,
			    [OP_ifle] = ifle,
			    [OP_i2f]  = i2f,
			    [OP_i2d]  = i2d,
			    [OP_i2b] = i2b,
			    [OP_i2c] = i2c,
			    [OP_i2l] = i2l,
			    [OP_i2s] = i2s,
			    [OP_sipush] = sipush,
			    [OP_aload] = aload,
			    [OP_aload_0] = aload_0,
			    [OP_aload_1] = aload_1,
			    [OP_aload_2] = aload_2,
			    [OP_aload_3] = aload_3,
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
		     [OP_ifeq] = 2,
		     [OP_ifne] = 2,
		     [OP_iflt] = 2,
		     [OP_ifge] = 2,
		     [OP_ifgt] = 2,
		     [OP_ifle] = 2,
		     [OP_multianewarray] = 3,
		     /*[OP_wide] = 3,*/
		     [OP_invokeinterface] = 4,
		     [OP_invokedynamic] = 4,
		     [OP_goto_w] = 4,
		     [OP_jsr_w] = 4,
		     /*[OP_lookupswitch] = 8,
		       [OP_tableswitch] = 16,*/
		     [OP_getstatic] = 2,
		     [OP_putstatic] = 2,
};

void init_jvm(JVM *jvm) {
  jvm->pc = 0;
  jvm->frame_index = 0;
  jvm->method_area = calloc(sizeof(MethodArea), 1);
  init_method_area(jvm->method_area);
  jvm->current_class_index = -1;
  jvm->current_method_index = -1;
  jvm->jmp = false;
  jvm->ret = false;
}

void deinit_jvm(JVM *jvm) {
  deinit_method_area(jvm->method_area);
  free(jvm->method_area);
  while (jvm_peek_frame(jvm)) {
    jvm_pop_frame(jvm);
  }
}

void jvm_load_classfile(JVM *jvm, classfile *cf) {
  method_area_load_classfile(jvm->method_area, cf);
}

void jvm_load_class(JVM *jvm, char *class_name) {
  method_area_load_class(jvm->method_area, class_name);
}

void jvm_set_current_class(JVM *jvm, char *class_name) {
  int index = method_area_class_lookup(jvm->method_area, class_name);
  jvm->current_class_index = index;
}

void jvm_set_current_method(JVM *jvm, char *method_name) {
  classfile *class = jvm_get_current_class(jvm);
  int i;
  for (i = 0; i < class->methods_count; i++) {
    method_info *method = &class->methods[i];
    char *curr_method_name = get_cp_string(class->constant_pool, method->name_index);
    if (strcmp(curr_method_name, method_name) == 0) {
      jvm->current_method_index = i;
      return;
    }
  }
}

void jvm_load_method(JVM *jvm, uint32_t class_index, uint32_t method_index) {
  jvm->current_class_index = class_index;
  jvm->current_method_index = method_index;
}

classfile *jvm_get_current_class(JVM *jvm) {
  classfile *class = jvm->method_area->classes[jvm->current_class_index];
  return class;
}

char *jvm_get_current_class_name(JVM *jvm) {
  Frame *f = jvm_peek_frame(jvm);
  classfile *class = jvm_get_current_class(jvm);
  CONSTANT_Class_info class_info = f->cp[class->this_class].info.class_info;
  return get_cp_string(f->cp, class_info.name_index);
}

method_info *jvm_get_current_method(JVM *jvm) {
  classfile *class = jvm_get_current_class(jvm);
  method_info *method = &class->methods[jvm->current_method_index];
  return method;
}

char *jvm_get_current_method_name(JVM *jvm) {
  Frame *f = jvm_peek_frame(jvm);
  method_info *method = jvm_get_current_method(jvm);
  char *str = get_cp_string(f->cp, method->name_index);
  return str;
}

void jvm_push_frame(JVM *jvm) {
  classfile *class = jvm_get_current_class(jvm);
  method_info *method = jvm_get_current_method(jvm);
  Code_attribute *code = &method->attributes[0].info.code;
  Frame *f = calloc(sizeof(Frame), 1);
  init_frame(f, jvm, code->max_locals, code->max_stack, class->constant_pool,
	     jvm->current_class_index, jvm->current_method_index);
  jvm->frames[jvm->frame_index++] = f;
  jvm->pc = 0;
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
  method_info *method = jvm_get_current_method(jvm);
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

  if (jvm->ret) {
    /* free called method's frame */
    jvm_pop_frame(jvm);
    jvm_restore_context(jvm);
    /* Push return value to callee's operand stack */
    if (opcode != OP_return) {
      Frame *f = jvm_peek_frame(jvm);
      push_stack(f, jvm->retval);
    }
    /* reset flag */
    jvm->ret = false;
  }

  if (!jvm->jmp && opcode != OP_invokestatic) jvm->pc += opargs[opcode] + 1;
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
  init_frame(f, jvm, code->max_locals, code->max_stack, class->constant_pool, jvm->current_class_index,
	     jvm->current_method_index);

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
  char *str = jvm_get_current_method_name(jvm);
  return strcmp(str, "main") == 0;
}

void jvm_save_context(JVM *jvm) {
  Frame *f = jvm_peek_frame(jvm);
  f->pc = jvm->pc + 2;
  f->class_index = jvm->current_class_index;
  f->method_index = jvm->current_method_index;
}

void jvm_restore_context(JVM *jvm) {
  Frame *f = jvm_peek_frame(jvm);
  jvm->pc = f->pc;
  jvm->current_class_index = f->class_index;
  jvm->current_method_index = f->method_index;
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

    push_stack_pointer(f, str);
  default:
    break;
  }
}

void istore(Frame *f, uint32_t a0, uint32_t a1) {
  /* store int into local variable a0 */
  int32_t op = pop_stack(f);
  frame_set_local_int(f, a0, op);
}

void istore_0(Frame *f, uint32_t a0, uint32_t a1) {
  /* store int into local variable 0 */
  istore(f, 0, 0);
}

void istore_1(Frame *f, uint32_t a0, uint32_t a1) {
  /* store int into local variable 1 */
  istore(f, 1, 0);
}

void istore_2(Frame *f, uint32_t a0, uint32_t a1) {
  /* store int into local variable 2 */
  istore(f, 2, 0);
}

void istore_3(Frame *f, uint32_t a0, uint32_t a1) {
  /* store int into local variable 3 */
  istore(f, 3, 0);
}

void iload(Frame *f, uint32_t a0, uint32_t a1) {
  /* Load int from local variable a0 */
  int32_t op = frame_get_local_int(f, a0);
  push_stack(f, op);
}

void iload_0(Frame *f, uint32_t a0, uint32_t a1) {
  /* Load int from local variable 0 */
  iload(f, 0, 0);
}

void iload_1(Frame *f, uint32_t a0, uint32_t a1) {
  /* Load int from local variable 1 */
  iload(f, 1, 0);
}

void iload_2(Frame *f, uint32_t a0, uint32_t a1) {
  /* Load int from local variable 2 */
  iload(f, 2, 0);
}

void iload_3(Frame *f, uint32_t a0, uint32_t a1) {
  /* Load int from local variable 3 */
  iload(f, 3, 0);
}

void iadd(Frame *f, uint32_t a0, uint32_t a1) {
  push_stack(f, pop_stack(f) + pop_stack(f));
}

void isub(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t v1 = pop_stack(f);
  int32_t v2 = pop_stack(f);
  push_stack(f, v2 - v1);
}

void return_func(Frame *f, uint32_t a0, uint32_t a1) {
#ifdef DEBUG
  printf("return\n");
#endif

  JVM *jvm = f->jvm;
  if (!jvm_in_main(jvm)) {
    jvm->ret = true;
  }
}

void ireturn(Frame *f, uint32_t a0, uint32_t a1) {
  /* get value to be returned */
  int retval = pop_stack(f);
  JVM *jvm = f->jvm;
  jvm->ret = true;
  jvm->retval = retval;
  #ifdef DEBUG
  printf("ireturn (%d 0x%x)\n", retval, retval);
  #endif
}

void invokevirtual(Frame *f, uint32_t a0, uint32_t a1) {
  uint32_t index = (a0 << 8) | a1;
  CONSTANT_Methodref_info methodref_info = f->cp[index].info.methodref_info;
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
      char *str = pop_stack_pointer(f);
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
      double db = pop_stack_double(f);
      #ifdef DEBUG
      printf("println(double): %f\n", db);
      #else
      printf("%f\n", db);
      #endif
    } else if (strcmp(type, "(J)V") == 0) {
      /* print long */
      int64_t x = pop_stack_long(f);
      #ifdef DEBUG
      printf("println(long): %ld\n", x);
      #else
      printf("%ld\n", x);
      #endif
    } else if (strcmp(type, "(F)V") == 0) {
      /* print float */
      float x = pop_stack_float(f);
      #ifdef DEBUG
      printf("println(float): %f\n", x);
      #else
      printf("%f\n", x);
      #endif
    } else if (strcmp(type, "(C)V") == 0) {
      /* print char */
      uint16_t ch = pop_stack(f);
      #ifdef DEBUG
      printf("println(char): %c\n", ch);
      #else
      printf("%c\n", ch);
      #endif
    }

    /* pop getstatic dummy value (view getstatic definition) */
    uint32_t dummy = pop_stack(f);
    #ifdef DEBUG
    printf("dummy: 0x%x\n", dummy);
    #endif
  } else if (strcmp(name, "print") == 0) {
    if (strcmp(type, "(Ljava/lang/String;)V") == 0) {
      /* print string */
      char *str = pop_stack_pointer(f);
      #ifdef DEBUG
      printf("print(String): \'%s\'\n", str);
      #else
      printf("%s", str);
      #endif

    } else if (strcmp(type, "(I)V") == 0) {
      /* print int */
      uint64_t value = pop_stack(f);
      int32_t integer = *((int32_t *) (&value));

      #ifdef DEBUG
      printf("print(Int): %d\n", integer);
      #else
      printf("%d", integer);
      #endif
    } else if (strcmp(type, "(D)V") == 0) {
      /* print double */
      double db = pop_stack_double(f);
      #ifdef DEBUG
      printf("print(double): %f\n", db);
      #else
      printf("%f", db);
      #endif
    } else if (strcmp(type, "(J)V") == 0) {
      /* print long */
      int64_t x = pop_stack_long(f);
      #ifdef DEBUG
      printf("print(long): %ld\n", x);
      #else
      printf("%ld", x);
      #endif
    } else if (strcmp(type, "(F)V") == 0) {
      /* print float */
      float x = pop_stack_float(f);
      #ifdef DEBUG
      printf("print(float): %f\n", x);
      #else
      printf("%f", x);
      #endif
    } else if (strcmp(type, "(C)V") == 0) {
      /* print char */
      uint16_t ch = pop_stack(f);
      #ifdef DEBUG
      printf("print(char): %c\n", ch);
      #else
      printf("%c", ch);
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

void invokestatic(Frame *f, uint32_t a0, uint32_t a1) {
  uint32_t index = (a0 << 8) | a1;
  CONSTANT_Methodref_info methodref_info = f->cp[index].info.methodref_info;
  uint16_t class_index = methodref_info.class_index;
  char *class_name = get_class_name_string(f->cp, class_index);
  uint16_t name_and_type_index = methodref_info.name_and_type_index;
  char *method_name = get_name_and_type_string(f->cp, name_and_type_index, 1);
  char *type = get_name_and_type_string(f->cp, name_and_type_index, 0);
#ifdef DEBUG
  printf("invokestatic: Methodref\t");
  printf("class: %s, name: %s, type: %s\n", class_name,
	 method_name, type);
#endif
  JVM *jvm = f->jvm;

  jvm_save_context(jvm);
  jvm_load_class(jvm, class_name);
  jvm_set_current_class(jvm, class_name);
  jvm_set_current_method(jvm, method_name);
  jvm_push_frame(jvm);

  if (strcmp(type, "(I)I") == 0) {
    Frame *f1 = jvm_peek_frame(jvm);
    int32_t arg = pop_stack(f);
    #ifdef DEBUG
    printf("invokestatic: arg = %d (0x%x)\n", arg, arg);
    #endif
    f1->locals[0] = arg;
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

    push_stack_pointer(f, str);
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

void dstore(Frame *f, uint32_t a0, uint32_t a1) {
  /* store a double into local variable a0 and a0 + 1 */
  double d = pop_stack_double(f);
  frame_set_local_double(f, a0, d);
  /* placeholder (doubles don't need 2 slots in this implementation */
  frame_set_local_double(f, a1, d);
}

void dstore_0(Frame *f, uint32_t a0, uint32_t a1) {
  /* store a double into local variable 0 and 1 */
  dstore(f, 0, 0);
}

void dstore_1(Frame *f, uint32_t a0, uint32_t a1) {
  /* store a double into local variable 1 and 2 */
  dstore(f, 1, 0);
}

void dstore_2(Frame *f, uint32_t a0, uint32_t a1) {
  /* store a double into local variable 2 and 3 */
  dstore(f, 2, 0);
}

void dstore_3(Frame *f, uint32_t a0, uint32_t a1) {
  /* store a double into local variable 3 and 4 */
  dstore(f, 3, 0);
}

void dload(Frame *f, uint32_t a0, uint32_t a1) {
  /* load double from local variable a0 and a0 + 1*/
  double d = frame_get_local_double(f, a0);
  push_stack_double(f, d);
}

void dload_0(Frame *f, uint32_t a0, uint32_t a1) {
  /* load double from local variable 0 and 1*/
  dload(f, 0, 0);
}

void dload_1(Frame *f, uint32_t a0, uint32_t a1) {
  /* load double from local variable 1 and 2*/
  dload(f, 1, 0);
}

void dload_2(Frame *f, uint32_t a0, uint32_t a1) {
  /* load double from local variable 2 and 3*/
  dload(f, 2, 0);
}

void dload_3(Frame *f, uint32_t a0, uint32_t a1) {
  /* load double from local variable 3 and 4*/
  dload(f, 3, 0);
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
  double result = d2 - d1;
  push_stack_double(f, result);
}

void ddiv(Frame *f, uint32_t a0, uint32_t a1) {
  double d1 = pop_stack_double(f);
  double d2 = pop_stack_double(f);
  double result = d2 / d1;
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
  int q = d2/d1;
  double result = d2 - (d1 * q);
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
  push_stack_int(f, 0);
}

void iconst_1(Frame *f, uint32_t a0, uint32_t a1) {
  push_stack_int(f, 1);
}

void iconst_2(Frame *f, uint32_t a0, uint32_t a1) {
  push_stack_int(f, 2);
}

void iconst_3(Frame *f, uint32_t a0, uint32_t a1) {
  push_stack_int(f, 3);
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

void lconst_0(Frame *f, uint32_t a0, uint32_t a1) {
  push_stack_long(f, 0);
}

void lconst_1(Frame *f, uint32_t a0, uint32_t a1) {
  push_stack_long(f, 1);
}

void lstore(Frame *f, uint32_t a0, uint32_t a1) {
  int64_t x = pop_stack_long(f);
  frame_set_local_long(f, a0, x);
}

void lstore_0(Frame *f, uint32_t a0, uint32_t a1) {
  lstore(f, 0, 0);
}

void lstore_1(Frame *f, uint32_t a0, uint32_t a1) {
  lstore(f, 1, 0);
}

void lstore_2(Frame *f, uint32_t a0, uint32_t a1) {
  lstore(f, 2, 0);
}

void lstore_3(Frame *f, uint32_t a0, uint32_t a1) {
  lstore(f, 3, 0);
}

void lload(Frame *f, uint32_t a0, uint32_t a1) {
  int64_t x = frame_get_local_long(f, a0);
  push_stack_long(f, x);
}

void lload_0(Frame *f, uint32_t a0, uint32_t a1) {
  lload(f, 0, 0);
}

void lload_1(Frame *f, uint32_t a0, uint32_t a1) {
  lload(f, 1, 0);
}

void lload_2(Frame *f, uint32_t a0, uint32_t a1) {
  lload(f, 2, 0);
}

void lload_3(Frame *f, uint32_t a0, uint32_t a1) {
  lload(f, 3, 0);
}

void ladd(Frame *f, uint32_t a0, uint32_t a1) {
  int64_t long_1 = pop_stack_long(f);
  int64_t long_2 = pop_stack_long(f);
  int64_t result = long_1 + long_2;
  push_stack_long(f, result);
}

void iinc(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t index = a0;
  int32_t c = ((int8_t) a1);
  f->locals[index] += c;
}

void goto_func(Frame *f, uint32_t a0, uint32_t a1) {
  int16_t branchoffset = (a0 << 8) | a1;
  #ifdef DEBUG
  printf("goto: %d (0x%x)\n", branchoffset, branchoffset);
  #endif

  JVM *jvm = f->jvm;
  jvm->pc += branchoffset;
  jvm->jmp = true;
}

void fconst_0(Frame *f, uint32_t a0, uint32_t a1) {
  push_stack_float(f, 0.0f);
}

void fconst_1(Frame *f, uint32_t a0, uint32_t a1) {
  push_stack_float(f, 1.0f);
}

void fconst_2(Frame *f, uint32_t a0, uint32_t a1) {
  push_stack_float(f, 2.0f);
}

void fstore(Frame *f, uint32_t a0, uint32_t a1) {
  float x = pop_stack_float(f);
  frame_set_local_float(f, a0, x);
}

void fstore_0(Frame *f, uint32_t a0, uint32_t a1) {
  fstore(f, 0, 0);
}

void fstore_1(Frame *f, uint32_t a0, uint32_t a1) {
  fstore(f, 1, 0);
}

void fstore_2(Frame *f, uint32_t a0, uint32_t a1) {
  fstore(f, 2, 0);
}

void fstore_3(Frame *f, uint32_t a0, uint32_t a1) {
  fstore(f, 3, 0);
}

void fload(Frame *f, uint32_t a0, uint32_t a1) {
  float x = frame_get_local_float(f, a0);
  push_stack_float(f, x);
}

void fload_0(Frame *f, uint32_t a0, uint32_t a1) {
  fload(f, 0, 0);
}

void fload_1(Frame *f, uint32_t a0, uint32_t a1) {
  fload(f, 1, 0);
}

void fload_2(Frame *f, uint32_t a0, uint32_t a1) {
  fload(f, 2, 0);
}

void fload_3(Frame *f, uint32_t a0, uint32_t a1) {
  fload(f, 3, 0);
}

void fsub(Frame *f, uint32_t a0, uint32_t a1) {
  float v1 = pop_stack_float(f);
  float v2 = pop_stack_float(f);
  push_stack_float(f, v2 - v1);
}

void fadd(Frame *f, uint32_t a0, uint32_t a1) {
  float v1 = pop_stack_float(f);
  float v2 = pop_stack_float(f);
  push_stack_float(f, v2 + v1);
}

void fdiv(Frame *f, uint32_t a0, uint32_t a1) {
  float v1 = pop_stack_float(f);
  float v2 = pop_stack_float(f);
  float div = v2 / v1;
  push_stack_float(f, div);
}

void ifeq(Frame *f, uint32_t a0, uint32_t a1) {
  int16_t branchoffset = (a0 << 8) | a1;
  uint64_t pop = pop_stack(f);
  int32_t value = (int32_t) ((uint32_t) pop);
  if (value == 0) {
    JVM *jvm = f->jvm;
    jvm->pc += branchoffset;
    jvm->jmp = true;
  }
}

void ifne(Frame *f, uint32_t a0, uint32_t a1) {
  int16_t branchoffset = (a0 << 8) | a1;
  uint64_t pop = pop_stack(f);
  int32_t value = (int32_t) ((uint32_t) pop);
  if (value != 0) {
    JVM *jvm = f->jvm;
    jvm->pc += branchoffset;
    jvm->jmp = true;
  }
}

void iflt(Frame *f, uint32_t a0, uint32_t a1) {
  int16_t branchoffset = (a0 << 8) | a1;
  uint64_t pop = pop_stack(f);
  int32_t value = (int32_t) ((uint32_t) pop);
  if (value < 0) {
    JVM *jvm = f->jvm;
    jvm->pc += branchoffset;
    jvm->jmp = true;
  }
}

void ifge(Frame *f, uint32_t a0, uint32_t a1) {
  int16_t branchoffset = (a0 << 8) | a1;
  uint64_t pop = pop_stack(f);
  int32_t value = (int32_t) ((uint32_t) pop);
  if (value >= 0) {
    JVM *jvm = f->jvm;
    jvm->pc += branchoffset;
    jvm->jmp = true;
  }
}

void ifgt(Frame *f, uint32_t a0, uint32_t a1) {
  int16_t branchoffset = (a0 << 8) | a1;
  uint64_t pop = pop_stack(f);
  int32_t value = (int32_t) ((uint32_t) pop);
  if (value > 0) {
    JVM *jvm = f->jvm;
    jvm->pc += branchoffset;
    jvm->jmp = true;
  }
}

void ifle(Frame *f, uint32_t a0, uint32_t a1) {
  int16_t branchoffset = (a0 << 8) | a1;
  uint64_t pop = pop_stack(f);
  int32_t value = (int32_t) ((uint32_t) pop);
  if (value <= 0) {
    JVM *jvm = f->jvm;
    jvm->pc += branchoffset;
    jvm->jmp = true;
  }
}

void i2f(Frame *f, uint32_t a0, uint32_t a1) {
  uint64_t pop = pop_stack(f);
  int32_t int_value = (int32_t) ((uint32_t) pop);
  float float_value = (float) int_value;
  push_stack_float(f, float_value);
}

void i2d(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t int_value = pop_stack_int(f);
  double double_value = (double) int_value;
  push_stack_double(f, double_value);
}

void i2b(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t intval = pop_stack_int(f);
  int8_t truncated = intval;
  int32_t result = truncated;
  push_stack_int(f, result);
}

void i2c(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t intval = pop_stack_int(f);
  uint16_t truncated = intval;
  int32_t result = truncated;
  push_stack_int(f, result);
}

void i2l(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t intval = pop_stack_int(f);
  int64_t longval = (int64_t) intval;
  push_stack_long(f, longval);
}

void i2s(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t intval = pop_stack_int(f);
  int16_t truncated = intval;
  int32_t result = truncated;
  push_stack_int(f, result);
}

void sipush(Frame *f, uint32_t a0, uint32_t a1) {
  int16_t sh = (a0 << 8) | a1;
  push_stack_int(f, sh);
}

void aload(Frame *f, uint32_t a0, uint32_t a1) {
  void *ref = frame_get_local_pointer(f, a0);
  push_stack_pointer(f, ref);
}

void aload_0(Frame *f, uint32_t a0, uint32_t a1) {
  aload(f, 0, 0);
}

void aload_1(Frame *f, uint32_t a0, uint32_t a1) {
  aload(f, 1, 0);
}

void aload_2(Frame *f, uint32_t a0, uint32_t a1) {
  aload(f, 2, 0);
}

void aload_3(Frame *f, uint32_t a0, uint32_t a1) {
  aload(f, 3, 0);
}
