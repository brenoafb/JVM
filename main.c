#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "classfile.h"
#include "jvm.h"

/** \mainpage JVM - 2019/2 - G6
 *
 * \section intro_sec Introduction
 *
 * This is the introduction.
 *
 * \section install_sec How to execute:
 *
 * \subsection step1 Step 1: Makefile
 *
 * Compile the program using the file Makefile or MakefileWin (depending on your platform)
 * with the make tool in your command prompt.
 *
 * \subsection step2 Step 2: Execution
 *
 * Run the resulting execute file with ./main.out \['file.class' without the posfix '.class'\] (le/i)
 * \n where le and i choose if will be displayed the reader and exhibitor (le), the interpreter result (i) or both (no param).
 *
 * \section students_sec Information
 *
 * \subsection topic1 Students:
 *  Giordano S. Monteiro - 17/0011160\n
 *  Filipi Teles da Silva - 12/0117754\n
 *  Breno A. F. Bortolli - 17/0007014\n
 *  Igor Bispo de Morais - 17/0050432\n
 * \subsection topic2 University
 * Universidade de Brasília
 * \subsection topic3 Course
 * Software Básico - 2019/2 - Marcelo Ladeira
 */

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

  FILE *fp = fopen(filename, "rb");
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
