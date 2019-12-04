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
			    [OP_imul] = imul,
			    [OP_idiv] = idiv,
			    [OP_ishl] = ishl,
			    [OP_ishr] = ishr,
          [OP_iushr] = iushr,
			    [OP_iand] = iand,
			    [OP_ior] = ior,
          [OP_irem] = irem,
          [OP_ineg] = ineg,
			    [OP_return] = return_func,
			    [OP_ireturn] = ireturn,
			    [OP_dreturn] = dreturn,
			    [OP_lreturn] = lreturn,
			    [OP_freturn] = freturn,
			    [OP_invokevirtual] = invokevirtual,
			    [OP_invokestatic] = invokestatic,
			    [OP_invokespecial] = invokespecial,
			    [OP_getstatic] = getstatic,
			    [OP_putstatic] = putstatic,
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
			    [OP_iconst_m1] = iconst_m1,
			    [OP_iconst_4] = iconst_4,
			    [OP_iconst_5] = iconst_5,
			    [OP_if_icmpeq] = if_icmpeq,
			    [OP_if_icmpne] = if_icmpne,
			    [OP_if_icmplt] = if_icmplt,
			    [OP_if_icmpge] = if_icmpge,
			    [OP_if_icmpgt] = if_icmpgt,
			    [OP_if_icmple] = if_icmple,
          [OP_ifnull] = ifnull,
          [OP_ifnonnull] = ifnonnull,
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
			    [OP_lsub] = lsub,
			    [OP_lmul] = lmul,
			    [OP_ldiv] = ldiv_,
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
          [OP_fmul] = fmul,
          [OP_frem] = frem,
          [OP_fneg] = fneg,
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
          [OP_aconst_null] = aconst_null,
			    [OP_aload] = aload,
			    [OP_aload_0] = aload_0,
			    [OP_aload_1] = aload_1,
			    [OP_aload_2] = aload_2,
			    [OP_aload_3] = aload_3,
			    [OP_astore] = astore,
			    [OP_astore_0] = astore_0,
			    [OP_astore_1] = astore_1,
			    [OP_astore_2] = astore_2,
			    [OP_astore_3] = astore_3,
			    [OP_newarray] = newarray,
			    [OP_aastore] = aastore,
			    [OP_aaload] = aaload,
			    [OP_iastore] = iastore,
			    [OP_iaload] = iaload,
			    [OP_fastore] = fastore,
			    [OP_faload] = faload,
			    [OP_lastore] = lastore,
			    [OP_laload] = laload,
			    [OP_dastore] = dastore,
			    [OP_daload] = daload,
			    [OP_bastore] = bastore,
			    [OP_baload] = baload,
			    [OP_d2f] = d2f,
			    [OP_d2i] = d2i,
			    [OP_d2l] = d2l,
			    [OP_f2d] = f2d,
			    [OP_f2i] = f2i,
			    [OP_f2l] = f2l,
			    [OP_l2d] = l2d,
			    [OP_l2f] = l2f,
			    [OP_l2i] = l2i,
			    [OP_multianewarray] = multianewarray,
			    [OP_anewarray] = anewarray,
			    [OP_dup] = dup,
			    [OP_new] = new,
			    [OP_getfield] = getfield,
			    [OP_putfield] = putfield,
          [OP_athrow] = athrow
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
  jvm->heap_index = -1;
  jvm->static_index = -1;
}

void deinit_jvm(JVM *jvm) {
  deinit_method_area(jvm->method_area);
  free(jvm->method_area);
  while (jvm_peek_frame(jvm)) {
    jvm_pop_frame(jvm);
  }

  while (jvm->heap_index >= 0) {
    free(jvm->heap[(jvm->heap_index)--]);
  }

  while (jvm->static_index >= 0) {
    free(jvm->statics[(jvm->static_index)--]);
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

void jvm_exec_clinit(JVM *jvm) {
  classfile *class = jvm_get_current_class(jvm);
  int flag = 0;
  int i;
  for (i = 0; i < class->methods_count; i++) {
    method_info *method = &class->methods[i];
    char *curr_method_name = get_cp_string(class->constant_pool, method->name_index);
    if (strcmp(curr_method_name, "<clinit>") == 0) {
      flag = 1;
      jvm->current_method_index = i;
    }
  }

  if (flag) {
    jvm_push_frame(jvm);
    jvm_run(jvm);
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

  if (opcode == OP_tableswitch) {
    return tableswitch(jvm);
  }

  uint32_t a[3];
  int i;
  for (i = 0; i < opargs[opcode]; i++) {
    a[i] = code->code[jvm->pc+i+1];
  #ifdef DEBUG
      printf("load a%d: %d\n", i, a[i]);
  #endif
  }
  if (opcode == OP_multianewarray) {
    uint32_t index = (a[0] << 8) | a[1];
    multianewarray(f, index, a[2]);
  } else {
    optable[opcode](f, a[0], a[1]);
  }
  if (opcode == OP_return && jvm_in_main(jvm)) {
      #ifdef DEBUG
      printf("frame->i: %d\n", f->i);
      if (f->i > 0) printf("Final value in stack: %d (0x%x)\n", peek_stack(f), peek_stack(f));
      #endif
    flag = 0;
  } else if (opcode == OP_return && jvm_in_clinit(jvm)) {
    #ifdef DEBUG
    printf("Return from '%s' <clinit>\n", jvm_get_current_class(jvm));
    #endif
    flag = 0;
  }

  if (jvm->ret && !jvm_in_main(jvm) && !jvm_in_clinit(jvm)) {
    /* free called method's frame */
    jvm_pop_frame(jvm);
    jvm_restore_context(jvm);
    Frame *f = jvm_peek_frame(jvm);
    /* Push return value to callee's operand stack */
    if (opcode == OP_dreturn) {
      double d = *((double *) (&jvm->retval));
      push_stack_double(f, d);
    } else if (opcode == OP_lreturn) {
      int64_t l = *((int64_t *) (&jvm->retval));
      push_stack_long(f, l);
    } else if (opcode != OP_return) {
      push_stack(f, jvm->retval);
    }

    /* reset return flag */
    jvm->ret = false;
  }

  if (!jvm->jmp && opcode != OP_invokestatic
		&& opcode != OP_invokespecial) {
    jvm->pc += opargs[opcode] + 1;
  }
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

bool jvm_in_clinit(JVM *jvm) {
  char *str = jvm_get_current_method_name(jvm);
  return strcmp(str, "<clinit>") == 0;
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

void jvm_add_to_heap(JVM *jvm, void *ptr) {
  jvm->heap[++(jvm->heap_index)] = ptr;
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

void imul(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t v1 = pop_stack(f);
  int32_t v2 = pop_stack(f);
  push_stack(f, v1 * v2);
}
void idiv(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t v1 = pop_stack(f);
  int32_t v2 = pop_stack(f);

  if (v1 == 0) {
    printf("ArithmeticException: Can't be divided by Zero\n");
    exit(1);
  }

  push_stack(f, v2/v1);
}

void iand(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t v1 = pop_stack(f);
  int32_t v2 = pop_stack(f);
  push_stack(f, (v2) & (v1) );
}

void ior(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t v1 = pop_stack(f);
  int32_t v2 = pop_stack(f);
  push_stack(f, (v2) | (v1));
}

void ineg(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t d1 = pop_stack(f);
  int32_t result = -d1;
  push_stack(f, result);
}

void irem(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t d1 = pop_stack(f);
  int32_t d2 = pop_stack(f);
  int q = d2/d1;
  int32_t result = d2 - (d1 * q);
  push_stack(f, result);
}

void ishr(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t v1 = pop_stack(f);
  int32_t v2 = pop_stack(f);
  int32_t result_ishr =  (v2 >> (v1 & 0x1F));
  push_stack(f,  result_ishr);
}

void ishl(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t v1 = pop_stack(f);
  int32_t v2 = pop_stack(f);
  int32_t result_ishl =  (v2 << (v1 & 0x1F));
  push_stack(f, result_ishl);
}

void iushr(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t v1 = pop_stack(f);
  int32_t v2 = pop_stack(f);
  int32_t result_ishr =  (v2 >> (v1 & 0x1F)) + (2 << ~(v1 & 0x1F));
  push_stack(f,  result_ishr);
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
  int32_t retval = pop_stack_int(f);
  JVM *jvm = f->jvm;
  jvm->ret = true;
  jvm->retval = *((uint64_t *) (&retval));
  #ifdef DEBUG
  printf("ireturn (%d 0x%x)\n", retval, retval);
  #endif
}

void dreturn(Frame *f, uint32_t a0, uint32_t a1) {
  /* get value to be returned */
  double retval = pop_stack_double(f);
  JVM *jvm = f->jvm;
  jvm->ret = true;
  jvm->retval = *((uint64_t *) (&retval));
  #ifdef DEBUG
  printf("dreturn (%f 0x%x)\n", retval, retval);
  #endif
}

void lreturn(Frame *f, uint32_t a0, uint32_t a1) {
  /* get value to be returned */
  int64_t retval = pop_stack_long(f);
  JVM *jvm = f->jvm;
  jvm->ret = true;
  jvm->retval = *((uint64_t *) (&retval));
  #ifdef DEBUG
  printf("lreturn (%ld 0x%x)\n", retval, retval);
  #endif
}

void freturn(Frame *f, uint32_t a0, uint32_t a1) {
  /* get value to be returned */
  float retval = pop_stack_float(f);
  JVM *jvm = f->jvm;
  jvm->ret = true;
  jvm->retval = *((uint64_t *) (&retval));
  #ifdef DEBUG
  printf("freturn (%f 0x%x)\n", retval, retval);
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
    } else if (strcmp(type, "(Z)V") == 0) {
      /* print bool */
      int32_t boolean = pop_stack_int(f);
      #ifdef DEBUG
      printf("println(bool): %d\n", boolean);
      #else
      if (boolean) {
	printf("true\n");
      } else {
	printf("false\n");
      }
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
    } else if (strcmp(type, "(Z)V") == 0) {
      /* print bool */
      int32_t boolean = pop_stack_int(f);
      #ifdef DEBUG
      printf("print(bool): %d\n", boolean);
      #else
      if (boolean) {
	printf("true");
      } else {
	printf("false");
      }
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

  jvm_set_args(jvm, f, type);
}

void jvm_parse_types(char *type, char parsed[], int *count) {
  char buf[BUFSIZE];
  int i = 1;
  int j = 0;
  int k = 0;
  while (type[i] != ')') {
    switch (type[i]) {
    case 'I':
      parsed[j] = 'I';
      break;
    case 'J':
      parsed[j] = 'J';
      break;
    case 'F':
      parsed[j] = 'F';
      break;
    case 'D':
      parsed[j] = 'D';
      break;
    default:
      while (type[i] != ';') buf[k++] = type[i++];
      buf[k] = 0;
      if (strcmp(buf, "Ljava/lang/String;")) {
	parsed[j] = 'A';
      } else {
	#ifdef DEBUG
	printf("jvm_set_args: Unknown arg type %s\n", buf);
	#endif
      }
      break;
    }
    j++;
    i++;
  }
  *count = j;
}

void jvm_set_args(JVM *jvm, Frame *caller, char *type) {
  Frame *f1 = jvm_peek_frame(jvm);

  int32_t intarg;
  int64_t longarg;
  float floatarg;
  double doublearg;
  void *ptrarg;

  char parsed[BUFSIZE] = {0};
  int count = 0;
  jvm_parse_types(type, parsed, &count);
  #ifdef DEBUG
  printf("jvm_set_args: parsed types: %s\n", parsed);
  #endif


  int i, j;

  /* compute last arg's position in locals array (j) */
  for (i = j = 0; i < count; i++) {
    switch (parsed[i]) {
    case 'D':
    case 'J':
      j++;
    default:
      j++;
      break;
    }
  }
  j-=1;

  /* loop backwards over args to pop in correct order */
  for (i = count-1; i >= 0; i--, j--) {
    switch (parsed[i]) {
    case 'I':
      intarg = pop_stack_int(caller);
      frame_set_local_int(f1, j, intarg);
      break;
    case 'J':
      longarg = pop_stack_long(caller);
      frame_set_local_long(f1, --j, longarg);
      break;
    case 'F':
      floatarg = pop_stack_float(caller);
      frame_set_local_float(f1, j, floatarg);
      break;
    case 'D':
      doublearg = pop_stack_double(caller);
      printf("Placing arg %f in local %d\n", doublearg, j-1);
      frame_set_local_double(f1, --j, doublearg);
      break;
    case 'A':
	ptrarg = pop_stack_pointer(caller);
	frame_set_local_pointer(f1, j, ptrarg);
	break;
    default:
      #ifdef DEBUG
      printf("jvm_set_args: Unknown type %c\n", parsed[i]);
      #endif
      break;
    }
  }
}

void invokespecial(Frame *f, uint32_t a0, uint32_t a1) {
  uint32_t index = (a0 << 8) | a1;
  CONSTANT_Methodref_info methodref_info = f->cp[index].info.methodref_info;
  uint16_t class_index = methodref_info.class_index;
  char *class_name = get_class_name_string(f->cp, class_index);
  uint16_t name_and_type_index = methodref_info.name_and_type_index;
  char *method_name = get_name_and_type_string(f->cp, name_and_type_index, 1);
  char *type = get_name_and_type_string(f->cp, name_and_type_index, 0);
#ifdef DEBUG
  printf("invokespecial: Methodref\t");
  printf("class: %s, name: %s, type: %s\n", class_name,
	 method_name, type);
#endif

  if (strcmp(class_name, "java/lang/Object") == 0) {
    /* ignore base object init */
    JVM *jvm = f->jvm;
    pop_stack_pointer(f);
    jvm->pc += opargs[OP_invokespecial] + 1;
  } else if (strcmp(method_name, "<init>") == 0) {
    JVM *jvm = f->jvm;
    jvm_save_context(jvm);
    jvm_load_class(jvm, class_name);
    jvm_set_current_class(jvm, class_name);
    jvm_set_current_method(jvm, method_name);
    jvm_push_frame(jvm);
    void *ref = pop_stack_pointer(f);
    frame_set_local_pointer(jvm_peek_frame(jvm), 0, ref);
  }
}

void getstatic(Frame *f, uint32_t a0, uint32_t a1) {
  uint32_t index = (a0 << 8) | a1;
  JVM *jvm = f->jvm;
  CONSTANT_Fieldref_info fieldref_info = f->cp[index].info.fieldref_info;
  uint16_t class_index = fieldref_info.class_index;
  uint16_t name_and_type_index = fieldref_info.name_and_type_index;

  char *classname = get_class_name_string(f->cp, class_index);
  char *name = get_name_and_type_string(f->cp, name_and_type_index, 1);
  char *type = get_name_and_type_string(f->cp, name_and_type_index, 0);

  #ifdef DEBUG
  printf("getstatic: classname=%s, name=%s, type=%s\n", classname, name, type);
  #endif

  if ((strcmp(classname, "java/lang/System") == 0)
      && (strcmp(name, "out") == 0)) {
    /* io operations will be handled by c code */
    /* push a dummy value onto the stack */
    push_stack(f, 0xcc0de);
  } else {
    Static *st = jvm_get_static(jvm, classname, name);

    assert(st);

    /* TODO: Add remaining types */
    if (strcmp(type, "I") == 0) {
      push_stack_int(f, st->value.intfield);
    } else if (strcmp(type, "J") == 0) {
      push_stack_long(f, st->value.longfield);
    } else if (strcmp(type, "F") == 0) {
      push_stack_float(f, st->value.floatfield);
    } else if (strcmp(type, "D") == 0) {
      push_stack_double(f, st->value.doublefield);
    } else if (strcmp(type, "Z") == 0) {
      push_stack(f, st->value.boolfield);
    } else if (strcmp(type, "S") == 0) {
      push_stack(f, st->value.shortfield);
    } else if (strcmp(type, "C") == 0) {
      push_stack(f, st->value.charfield);
    } else if (strcmp(type, "B") == 0) {
      push_stack(f, st->value.bytefield);
    } else {
      push_stack_pointer(f, st->value.ptrfield);
    }
  }
  return;
}

void putstatic(Frame *f, uint32_t a0, uint32_t a1) {
  uint32_t index = (a0 << 8) | a1;
  JVM *jvm = f->jvm;
  CONSTANT_Fieldref_info fieldref_info = f->cp[index].info.fieldref_info;
  uint16_t class_index = fieldref_info.class_index;
  uint16_t name_and_type_index = fieldref_info.name_and_type_index;

  char *classname = get_class_name_string(f->cp, class_index);
  char *name = get_name_and_type_string(f->cp, name_and_type_index, 1);
  char *type = get_name_and_type_string(f->cp, name_and_type_index, 0);

  #ifdef DEBUG
  printf("putstatic: classname=%s, name=%s, type=%s\n", classname, name, type);
  #endif

  Static *st = jvm_get_static(jvm, classname, name);

  if (!st) {
    st = jvm_push_static(jvm);
    st->class = classname;
    st->name = name;
    st->type = type;
  }

  if (strcmp(type, "I") == 0) {
    int32_t value = pop_stack_int(f);
    st->value.intfield = value;
  } else if (strcmp(type, "J") == 0) {
    int64_t value = pop_stack_long(f);
    st->value.longfield = value;
  } else if (strcmp(type, "F") == 0) {
    float value = pop_stack_float(f);
    st->value.floatfield = value;
  } else if (strcmp(type, "D") == 0) {
    double value = pop_stack_double(f);
    st->value.doublefield = value;
  } else if (strcmp(type, "S") == 0) {
    uint64_t pop = pop_stack(f);
    int16_t value = *((int16_t *) (&pop));
    st->value.shortfield = value;
  } else if (strcmp(type, "Z") == 0) {
    uint64_t pop = pop_stack(f);
    uint8_t value = *((uint8_t *) (&pop));
    st->value.boolfield = value;
  } else if (strcmp(type, "C") == 0) {
    uint64_t pop = pop_stack(f);
    uint16_t value = *((uint16_t *) (&pop));
    st->value.charfield = value;
  } else {
    void *value = pop_stack_pointer(f);
    st->value.ptrfield = value;
  }

}

Static *jvm_get_static(JVM *jvm, char *classname, char *name) {
  int i;
  for (i = 0; i <= jvm->static_index; i++) {
    if (strcmp(classname, jvm->statics[i]->class) == 0
	&& strcmp(name, jvm->statics[i]->name) == 0) {
      return jvm->statics[i];
    }
  }
  return NULL;
}

Static *jvm_push_static(JVM *jvm) {
  Static *s = calloc(sizeof(Static), 1);
  assert(s);
  jvm->statics[++(jvm->static_index)] = s;
  return s;
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
  uint64_t cat;

  index = (a0 << 8) + a1;
  /* push item from runtime constant pool */
  uint8_t tag = f->cp[index].tag;
  switch (tag) {
  case CONSTANT_Long:
    low_bytes = f->cp[index].info.long_info.low_bytes;
    high_bytes = f->cp[index].info.long_info.high_bytes;
    cat = (((uint64_t) high_bytes) << 32) | low_bytes;
    int64_t l = *((uint64_t *) (&cat));
    push_stack_long(f, l);
#ifdef DEBUG
    printf("ldc2_w: Push %ld from cp\n", l);
#endif
    break;
  case CONSTANT_Double:
    low_bytes = f->cp[index].info.double_info.low_bytes;
    high_bytes = f->cp[index].info.double_info.high_bytes;

    cat = (((uint64_t) high_bytes) << 32) | low_bytes;
    double d = *((double *) (&cat));
    push_stack_double(f, d);
#ifdef DEBUG
    printf("ldc2_w: Push %lf from cp\n", d);
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
  frame_set_local_double(f, a0+1, d);
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

void iconst_4(Frame *f, uint32_t a0, uint32_t a1) {
  push_stack_int(f, 4);
}

void iconst_5(Frame *f, uint32_t a0, uint32_t a1) {
  push_stack_int(f, 5);
}

void iconst_m1(Frame *f, uint32_t a0, uint32_t a1) {
  push_stack_int(f, -1);
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
  /* placeholder (longs don't need 2 slots in this implementation */
  frame_set_local_long(f, a0+1, x);
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
  int64_t result = (int64_t) (long_1 + long_2);
  push_stack_long(f, result);
}

void lsub(Frame *f, uint32_t a0, uint32_t a1) {
  int64_t long_2 = pop_stack_long(f);
  int64_t long_1 = pop_stack_long(f);
  int64_t result = long_1 - long_2;
  push_stack_long(f, result);
}

void lmul(Frame *f, uint32_t a0, uint32_t a1) {
  int64_t long_1 = pop_stack_long(f);
  int64_t long_2 = pop_stack_long(f);
  int64_t result = long_1 * long_2;
  push_stack_long(f, result);
}

void ldiv_(Frame *f, uint32_t a0, uint32_t a1) {
  int64_t long_2 = pop_stack_long(f);
  int64_t long_1 = pop_stack_long(f);
  int64_t result = long_1 / long_2;
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

void fmul(Frame *f, uint32_t a0, uint32_t a1) {
  float v1 = pop_stack_float(f);
  float v2 = pop_stack_float(f);
  float mul = v2 * v1;
  push_stack_float(f, mul);
}

void fneg(Frame *f, uint32_t a0, uint32_t a1) {
  float v1 = pop_stack_float(f);
  float result = -v1;
  push_stack_float(f, result);
}

void frem(Frame *f, uint32_t a0, uint32_t a1) {
  float v1 = pop_stack_float(f);
  float v2 = pop_stack_float(f);
  int q = v2/v1;
  float result = v2 - (v1 * q);
  push_stack_float(f, result);
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
  void* value = pop_stack_pointer(f);
  if (value <= 0) {
    JVM *jvm = f->jvm;
    jvm->pc += branchoffset;
    jvm->jmp = true;
  }
}

void ifnonnull(Frame *f, uint32_t a0, uint32_t a1) {
  int16_t branchoffset = (a0 << 8) | a1;
  void* value = pop_stack_pointer(f);
  if (value != NULL) {
    JVM *jvm = f->jvm;
    jvm->pc += branchoffset;
    jvm->jmp = true;
  }
}

void ifnull(Frame *f, uint32_t a0, uint32_t a1) {
  int16_t branchoffset = (a0 << 8) | a1;
  uint64_t pop = pop_stack(f);
  void* value = (void*) ((uint32_t) pop);
  if (value == NULL) {
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

int tableswitch(JVM *jvm) {
  Frame *f = jvm_peek_frame(jvm);
  method_info *method = jvm_get_current_method(jvm);
  Code_attribute *code = &method->attributes[0].info.code;

  uint32_t opcode = code->code[jvm->pc];
    uint32_t start = jvm->pc-1;
    /* skip padding */
    while ((jvm->pc - start) % 4 != 0) jvm->pc++;
    uint32_t default_bytes = 0;
    int i;
    for (i = 0; i < 4; i++) {
      default_bytes = (default_bytes << 4) | code->code[jvm->pc];
      jvm->pc++;
    }

    uint32_t low_bytes = 0;
    for (i = 0; i < 4; i++) {
      low_bytes = (low_bytes << 4) | code->code[jvm->pc];
      jvm->pc++;
    }

    uint32_t high_bytes = 0;
    for (i = 0; i < 4; i++) {
      high_bytes = (high_bytes << 4) | code->code[jvm->pc];
      jvm->pc++;
    }

    int32_t def = *((int32_t *) (&default_bytes));
    int32_t lo = *((int32_t *) (&low_bytes));
    int32_t hi = *((int32_t *) (&high_bytes));

    #ifdef DEBUG
    printf("tableswitch: def=%d(0x%x), lo=%d(0x%x), hi=%d(0x%x)\n",
	   def, def,
	   lo, lo,
	   hi, hi);
    #endif

    int32_t offsets[hi-lo+1];
    for (i = 0; i < hi-lo+1; i++) {
      uint32_t bytes = 0;
      int j;
      for (j = 0; j < 4; j++) {
	bytes = (bytes << 4) | code->code[jvm->pc];
	jvm->pc++;
      }
      offsets[i] = *((int32_t *) (&bytes));
      #ifdef DEBUG
      printf("\t%d (0x%x)\n", offsets[i], offsets[i]);
      #endif
    }

    int32_t value = pop_stack_int(f);
    if (value < lo || value > hi) {
      jvm->pc = start + def + 1;
    } else {
      jvm->pc = start + offsets[value - lo] + 1;
    }
    #ifdef DEBUG
    printf("\tpc=%d (0x%x)\n", jvm->pc, jvm->pc);
    #endif
    return 1;
}

void aconst_null (Frame *f, uint32_t a0, uint32_t a1) {
  push_stack_pointer(f, NULL);
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

void astore(Frame *f, uint32_t a0, uint32_t a1) {
  /* TODO */
  void *ref = pop_stack_pointer(f);
  frame_set_local_pointer(f, a0, ref);
}

void astore_0(Frame *f, uint32_t a0, uint32_t a1) {
  astore(f, 0, 0);
}

void astore_1(Frame *f, uint32_t a0, uint32_t a1) {
  astore(f, 1, 0);
}

void astore_2(Frame *f, uint32_t a0, uint32_t a1) {
  astore(f, 2, 0);
}

void astore_3(Frame *f, uint32_t a0, uint32_t a1) {
  astore(f, 3, 0);
}

void newarray(Frame *f, uint32_t a0, uint32_t a1) {
  /* TODO */
  int32_t count = pop_stack_int(f);
  size_t size = 0;
  switch (a0) {
    case T_BOOLEAN:
      size = sizeof(uint8_t);
      break;
    case T_CHAR:
      size = sizeof(uint16_t);
      break;
    case T_FLOAT:
      size = sizeof(float);
      break;
    case T_DOUBLE:
      size = sizeof(double);
      break;
    case T_BYTE:
      size = sizeof(int8_t);
      break;
    case T_SHORT:
      size = sizeof(int16_t);
      break;
    case T_INT:
      size = sizeof(uint32_t);
      break;
    case T_LONG:
      size = sizeof(int64_t);
      break;
    default:
      break;
  }

  void *mem = calloc(size, count);
  JVM *jvm = f->jvm;
  jvm_add_to_heap(jvm, mem);

  push_stack_pointer(f, mem);
}

void aastore(Frame *f, uint32_t a0, uint32_t a1) {
  void *value = pop_stack_pointer(f);
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);

  memcpy(arrayref + index*sizeof(void *), &value, sizeof(void *));
}

void aaload(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);
  void *value = 0;

  memcpy(&value, arrayref + index*sizeof(void *), sizeof(void *));
  push_stack_pointer(f, value);
}

void iastore(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t value = pop_stack_int(f);
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);

  memcpy(arrayref + index*sizeof(int32_t), &value, sizeof(int32_t));
}

void iaload(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);
  int32_t value = 0;

  memcpy(&value, arrayref + index*sizeof(int32_t), sizeof(int32_t));
  push_stack_int(f, value);
}

void fastore(Frame *f, uint32_t a0, uint32_t a1) {
  float value = pop_stack_float(f);
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);

  memcpy(arrayref + index*sizeof(float), &value, sizeof(float));
}

void faload(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);
  float value = 0;

  memcpy(&value, arrayref + index*sizeof(float), sizeof(float));
  push_stack_float(f, value);
}

void lastore(Frame *f, uint32_t a0, uint32_t a1) {
  int64_t value = pop_stack_long(f);
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);

  memcpy(arrayref + index*sizeof(int64_t), &value, sizeof(int64_t));
}

void laload(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);
  int64_t value = 0;

  memcpy(&value, arrayref + index*sizeof(int64_t), sizeof(int64_t));
  push_stack_long(f, value);
}

void dastore(Frame *f, uint32_t a0, uint32_t a1) {
  double value = pop_stack_double(f);
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);

  memcpy(arrayref + index*sizeof(double), &value, sizeof(double));
}

void daload(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);
  double value = 0;

  memcpy(&value, arrayref + index*sizeof(double), sizeof(double));
  push_stack_double(f, value);
}

void bastore(Frame *f, uint32_t a0, uint32_t a1) {
  int8_t value = pop_stack_byte(f);
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);

  memcpy(arrayref + index*sizeof(int8_t), &value, sizeof(int8_t));
}

void baload(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);
  int8_t value = 0;

  memcpy(&value, arrayref + index*sizeof(int8_t), sizeof(int8_t));
  push_stack_byte(f, value);
}

void d2f(Frame *f, uint32_t a0, uint32_t a1) {
  double dval = pop_stack_double(f);
  float fval = dval;
  push_stack_float(f, fval);
}

void d2i(Frame *f, uint32_t a0, uint32_t a1) {
  double dval = pop_stack_double(f);
  int32_t ival = dval;
  push_stack_int(f, ival);
}


void d2l(Frame *f, uint32_t a0, uint32_t a1) {
  double dval = pop_stack_double(f);
  int64_t lval = dval;
  push_stack_long(f, lval);
}

void f2d(Frame *f, uint32_t a0, uint32_t a1) {
  float fval = pop_stack_float(f);
  double dval = fval;
  push_stack_double(f, dval);
}

void f2i(Frame *f, uint32_t a0, uint32_t a1) {
  float fval = pop_stack_float(f);
  int32_t ival = fval;
  push_stack_int(f, ival);
}

void f2l(Frame *f, uint32_t a0, uint32_t a1) {
  float fval = pop_stack_float(f);
  int64_t lval = fval;
  push_stack_long(f, lval);
}

void l2d(Frame *f, uint32_t a0, uint32_t a1) {
  int64_t lval = pop_stack_long(f);
  double dval = lval;
  push_stack_double(f, dval);
}

void l2f(Frame *f, uint32_t a0, uint32_t a1) {
  int64_t lval = pop_stack_long(f);
  float fval = lval;
  push_stack_float(f, fval);
}

void l2i(Frame *f, uint32_t a0, uint32_t a1) {
  int64_t lval = pop_stack_long(f);
  int32_t ival = lval;
  push_stack_int(f, ival);
}

void multianewarray(Frame *f, uint32_t a0, uint32_t a1) {
  uint32_t index = a0;
  uint32_t dims = a1;
  int32_t counts[dims];
  uint32_t i;
  JVM *jvm = f->jvm;
  cp_info *entry = &f->cp[index];

  for (i = 0; i < dims; i++) {
    counts[i] = pop_stack_int(f);
  }

  /* assume 2d array */
  uint32_t size = 0;
  if (entry->tag == CONSTANT_Class) {
    CONSTANT_Class_info ci = entry->info.class_info;
    uint16_t name_index = ci.name_index;
    char *name = get_cp_string(f->cp, name_index);
    if (strcmp(name, "[[[I") == 0 || strcmp(name, "[[I") == 0) {
      /* int array */
      size = sizeof(int32_t);
    } else if (strcmp(name, "[[[J") == 0 || strcmp(name, "[[J") == 0) {
      /* long array */
      size = sizeof(int64_t);
    } else if (strcmp(name, "[[[F") == 0 || strcmp(name, "[[F") == 0) {
      /* float array */
      size = sizeof(float);
    } else if (strcmp(name, "[[[D") == 0 || strcmp(name, "[[D") == 0) {
      /* double array */
      size = sizeof(double);
    }
  }

  if (dims == 2) jvm_alloc_array_2d(jvm, counts, size);
  else if (dims == 3) jvm_alloc_array_3d(jvm, counts, size);
}

void jvm_alloc_array_2d(JVM *jvm, int32_t counts[], uint32_t size) {
  Frame *f = jvm_peek_frame(jvm);
  int32_t **ptr = calloc(sizeof(void *), counts[0]);
  int32_t i;
  for (i = 0; i < counts[0]; i++) {
    ptr[i] = calloc(size, counts[1]);
    jvm_add_to_heap(jvm, ptr[i]);
  }
  push_stack_pointer(f, ptr);
  jvm_add_to_heap(jvm, ptr);
}

void jvm_alloc_array_3d(JVM *jvm, int32_t counts[], uint32_t size) {
  Frame *f = jvm_peek_frame(jvm);
  int32_t ***ptr = calloc(sizeof(void *), counts[0]);
  int32_t i, j;
  for (i = 0; i < counts[0]; i++) {
    ptr[i] = calloc(sizeof(void *), counts[1]);
    for (j = 0; j < counts[1]; j++) {
      ptr[i][j] = calloc(size, counts[2]);
      jvm_add_to_heap(jvm, ptr[i][j]);
    }
    jvm_add_to_heap(jvm, ptr[i]);
  }
  push_stack_pointer(f, ptr);
  jvm_add_to_heap(jvm, ptr);
}

void anewarray(Frame *f, uint32_t a0, uint32_t a1) {
  int32_t index = (a0 << 8) | a1;
  int32_t count = pop_stack_int(f);

  /* TODO Resolve cp entry */
  void *ptr = calloc(sizeof(void *), count);
  JVM *jvm = f->jvm;
  jvm_add_to_heap(jvm, ptr);
  push_stack_pointer(f, ptr);
}

void dup(Frame *f, uint32_t a0, uint32_t a1) {
  uint64_t pop = pop_stack(f);
  push_stack(f, pop);
  push_stack(f, pop);
}

void new(Frame *f, uint32_t a0, uint32_t a1) {
  uint32_t index = (a0 << 8) | a1;
  CONSTANT_Class_info *ci = &f->cp[index].info.class_info;
  char *name = get_cp_string(f->cp, ci->name_index);
  jvm_load_class(f->jvm, name);
  jvm_alloc_object(f->jvm, name);
}

void athrow(Frame *f, uint32_t a0, uint32_t a1) {
  uint64_t objref = pop_stack(f);

  if (!objref) {
    printf("NullPointerException\n");
    exit(1);
  }

  else {
    printf("UnimplementedException\n");
    exit(1);
  }
}

void getfield(Frame *f, uint32_t a0, uint32_t a1) {
  uint32_t index = (a0 << 8) | a1;

  Object *objectref = pop_stack_pointer(f);
  JVM *jvm = f->jvm;

  CONSTANT_Fieldref_info fieldref_info = f->cp[index].info.fieldref_info;
  uint32_t class_index = fieldref_info.class_index;
  uint32_t nameandtype_index = fieldref_info.name_and_type_index;

  CONSTANT_Class_info *class_info = &f->cp[class_index].info.class_info;
  CONSTANT_NameAndType_info *nameandtype_info = &f->cp[nameandtype_index].info.nameandtype_info;

  char *classname = get_cp_string(f->cp, class_info->name_index);
  char *fieldname = get_cp_string(f->cp, nameandtype_info->name_index);
  char *class_desc = get_cp_string(f->cp, nameandtype_info->descriptor_index);

  uint32_t field_index = jvm_get_field_index(jvm, classname, fieldname);
  char *field_desc = jvm_get_field_descriptor(jvm, classname, fieldname);

  if (strcmp(field_desc, "I") == 0) {
    /* field is int */
    int32_t value = objectref->fields[field_index].intfield;
    push_stack_int(f, value);
  } else if (strcmp(field_desc, "J") == 0) {
    int64_t value = objectref->fields[field_index].longfield;
    push_stack_long(f, value);
  } else if (strcmp(field_desc, "D") == 0) {
    double value = objectref->fields[field_index].doublefield;
    push_stack_double(f, value);
  } else if (strcmp(field_desc, "F") == 0) {
    float value = objectref->fields[field_index].floatfield;
    push_stack_float(f, value);
  } else if (strcmp(field_desc, "Z") == 0) {
    uint8_t value = objectref->fields[field_index].boolfield;
    push_stack(f, value);
  } else if (strcmp(field_desc, "S") == 0) {
    int16_t value = objectref->fields[field_index].shortfield;
    push_stack(f, *((uint64_t *) (&value)));
  } else if (strcmp(field_desc, "B") == 0) {
    int8_t value = objectref->fields[field_index].bytefield;
    push_stack(f, *((uint64_t *) (&value)));
  } else if (strcmp(field_desc, "C") == 0) {
    uint16_t value = objectref->fields[field_index].charfield;
    push_stack(f, value);
  } else {
    void *value = objectref->fields[field_index].ptrfield;
    push_stack_pointer(f, value);
  }

}

void putfield(Frame *f, uint32_t a0, uint32_t a1) {
  JVM *jvm = f->jvm;
  uint32_t index = (a0 << 8) | a1;

  CONSTANT_Fieldref_info fieldref_info = f->cp[index].info.fieldref_info;
  uint32_t class_index = fieldref_info.class_index;
  uint32_t nameandtype_index = fieldref_info.name_and_type_index;

  CONSTANT_Class_info *class_info = &f->cp[class_index].info.class_info;
  CONSTANT_NameAndType_info *nameandtype_info = &f->cp[nameandtype_index].info.nameandtype_info;

  char *classname = get_cp_string(f->cp, class_info->name_index);
  char *fieldname = get_cp_string(f->cp, nameandtype_info->name_index);
  char *class_desc = get_cp_string(f->cp, nameandtype_info->descriptor_index);

  uint32_t field_index = jvm_get_field_index(jvm, classname, fieldname);
  char *field_desc = jvm_get_field_descriptor(jvm, classname, fieldname);

  if (strcmp(field_desc, "I") == 0) {
    int32_t value = pop_stack_int(f);
    Object *obj = pop_stack_pointer(f);
    obj->fields[field_index].intfield = value;
  } else if (strcmp(field_desc, "J") == 0) {
    int64_t value = pop_stack_long(f);
    Object *obj = pop_stack_pointer(f);
    obj->fields[field_index].longfield = value;
  } else if (strcmp(field_desc, "D") == 0) {
    double value = pop_stack_double(f);
    Object *obj = pop_stack_pointer(f);
    obj->fields[field_index].doublefield = value;
  } else if (strcmp(field_desc, "F") == 0) {
    float value = pop_stack_float(f);
    Object *obj = pop_stack_pointer(f);
    obj->fields[field_index].floatfield = value;
  } else if (strcmp(field_desc, "Z") == 0) {
    uint8_t value = pop_stack(f);
    Object *obj = pop_stack_pointer(f);
    obj->fields[field_index].boolfield = value;
  } else if (strcmp(field_desc, "S") == 0) {
    uint64_t value = pop_stack(f);
    Object *obj = pop_stack_pointer(f);
    obj->fields[field_index].shortfield = *((int16_t *) (&value));
  } else if (strcmp(field_desc, "C") == 0) {
    uint16_t value = pop_stack(f);
    Object *obj = pop_stack_pointer(f);
    obj->fields[field_index].shortfield = value;
  } else if (strcmp(field_desc, "B") == 0) {
    uint64_t value = pop_stack(f);
    Object *obj = pop_stack_pointer(f);
    obj->fields[field_index].bytefield = *((int8_t *) (&value));
  } else {
    void *value = pop_stack_pointer(f);
    Object *obj = pop_stack_pointer(f);
    obj->fields[field_index].ptrfield = value;
  }
}

int32_t jvm_get_field_index(JVM *jvm, char *classname, char *fieldname) {
  int32_t class_index = method_area_class_lookup(jvm->method_area, classname);
  classfile *cf = jvm->method_area->classes[class_index];
  field_info *fields = cf->fields;
  int i;
  for (i = 0; i < cf->fields_count; i++) {
    char *curr_field = get_cp_string(cf->constant_pool, fields[i].name_index);
    char *desc = get_cp_string(cf->constant_pool, fields[i].descriptor_index);
    if (strcmp(curr_field, fieldname) == 0) {
      /* found desired field */
      return i;
    }
  }
  return -1;
}

char *jvm_get_field_descriptor(JVM *jvm, char *classname, char *fieldname) {
  int32_t class_index = method_area_class_lookup(jvm->method_area, classname);
  classfile *cf = jvm->method_area->classes[class_index];
  field_info *fields = cf->fields;
  int i;
  for (i = 0; i < cf->fields_count; i++) {
    char *curr_field = get_cp_string(cf->constant_pool, fields[i].name_index);
    char *desc = get_cp_string(cf->constant_pool, fields[i].descriptor_index);
    if (strcmp(curr_field, fieldname) == 0) {
      /* found desired field */
      return desc;
    }
  }
  return NULL;
}

void jvm_alloc_object(JVM *jvm, char *classname) {
  classfile *cf = jvm->method_area->classes[method_area_class_lookup(jvm->method_area, classname)];
  field_info *fields = cf->fields;

  Object *obj = calloc(sizeof(Object), 1);
  obj->size = cf->fields_count;
  obj->fields = calloc(sizeof(ObjectField), obj->size);
  jvm_add_to_heap(jvm, obj);
  jvm_add_to_heap(jvm, obj->fields);
  push_stack_pointer(jvm_peek_frame(jvm), obj);
}
