#ifndef ACCESS_FLAGS_H_
#define ACCESS_FLAGS_H_

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_FLAGS 32

typedef struct ac_node ac_node;

struct ac_node {
    char* flag_name;
    uint32_t flag_code;
    ac_node* next;
};

ac_node* AC_FLAGS_CLASS;
ac_node* AC_FLAGS_FIELD;
ac_node* AC_FLAGS_METHOD;

char** get_flags_name(ac_node* ac_list, uint32_t code);
void add_flag(ac_node** ac_list, uint32_t code, const char* name);
void populate_ac_flags_class();
void populate_ac_flags_method();
void print_flags(ac_node* ac_list, uint32_t code);


#endif