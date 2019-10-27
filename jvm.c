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
}

/* Load the classfile into the jvm's MethodArea */
void jvm_load_class(JVM *jvm, classfile *cf) {
  method_area_load_class(jvm->method_area, cf);
}
