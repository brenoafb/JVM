#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "classfile.h"
#include "jvm.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s [class file]\n", argv[0]);
    return 0;
  }

  const char *filename = argv[1];
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    printf("Error opening file %s.\n", filename);
    return 1;
  }

  classfile cf = {0};
  JVM memory = {0};
  read_class_file(&cf, fp);
  init_jvm(&memory);

  jvm_load_class(&memory, &cf);


  deinit_jvm(&memory);
  deinit_class_file(&cf);
  deinit_ac_flags();

  fclose(fp);

  return 0;
}
