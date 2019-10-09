#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "classfile.h"

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
  read_class_file(&cf, fp);
  print_class_file_summary(&cf);
  print_cp_detail(&cf);
  deinit_class_file(&cf);

  fclose(fp);

  return 0;
}
