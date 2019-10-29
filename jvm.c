#include "jvm.h"

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

  uint32_t i;
  for (i = 0; i < code->code_length; i++) {
    uint32_t opcode = code->code[i];
    uint32_t a0, a1;
    switch (opcode) {
    case 0x12:    /* ldc */
      a0 = code->code[i+1];
      printf("%u\tldc\t\t#%u\n", i, a0);
      /* TODO run ldc */
      i++;
      break;
    case 0x3c:    /* istore_1 */
      printf("%u\tistore_1\n", i);
      /* TODO run istore_1 */
      break;
    case 0x3d:    /* istore_2 */
      printf("%u\tistore_2\n", i);
      /* TODO run istore_2 */
      break;
    case 0x3e:    /* istore_3 */
      printf("%u\tistore_3\n", i);
      /* TODO run istore_3 */
      break;
    case 0x1b:    /* iload_1 */
      printf("%u\tiload_1\n", i);
      /* TODO run iload_1 */
      break;
    case 0x1c:    /* iload_2 */
      printf("%u\tiload_2\n", i);
      /* TODO run iload_2 */
      break;
    case 0x60:    /* iadd */
      printf("%u\tiadd\n", i);
      /* TODO run iadd */
      break;
    case 0xb1:    /* return */
      printf("%u\treturn\n", i);
      /* TODO run return */
      break;
    }
  }
}
