#include "methodarea.h"

void init_method_area(MethodArea *ma) {
  ma->n_classes = 0;
}

void deinit_method_area(MethodArea *ma) {
  /* nothing to do so far */
}

void method_area_load_class(MethodArea *ma, classfile *cf) {
  assert(ma->n_classes < MAX_CLASSES);
  ma->classes[ma->n_classes++] = cf;
}
