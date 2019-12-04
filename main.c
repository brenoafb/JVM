#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "classfile.h"
#include "jvm.h"

int main(int argc, char *argv[]) {
  if (argc != 2 && argc != 3) {
    printf("Usage: %s [class file] [i/le]\n", argv[0]);
    return 0;
  }

  char* option;

  if (argc == 2) {
    option = "default";
  } else {
    option = argv[2];

    if (strcmp(option, "le") && strcmp(option, "i")) {
      printf("\"%s\" is a invalid option\n", option);
      printf("valid options are \"le\" and \"i\"\n");

      return 1;
    }
  }

  char filename[BUFSIZE];
  char* class_name;
  strcpy(filename, argv[1]);
  strcat(filename, ".class");
  class_name = strrchr(argv[1], '/');

  if (class_name == NULL)
    class_name = argv[1];
  else
    class_name ++;

  FILE *fp = fopen(filename, "r");
  if (!fp) {
    printf("Error opening file %s.\n", filename);
    return 1;
  }

  classfile cf = {0};
  JVM memory = {0};
  read_class_file(&cf, fp);

  if (!strcmp(option, "default") || !strcmp(option, "le"))
    print_class_file_detail(&cf);

  if (!strcmp(option, "default") || !strcmp(option, "i")){
    init_jvm(&memory);

    jvm_load_class(&memory, argv[1]);
    jvm_set_current_class(&memory, class_name);
    jvm_exec_clinit(&memory);
    jvm_set_current_method(&memory, "main");

    jvm_push_frame(&memory);
    jvm_run(&memory);

    deinit_jvm(&memory);
  } 
  
  deinit_class_file(&cf);
  deinit_ac_flags();

  fclose(fp);

  return 0;
}
