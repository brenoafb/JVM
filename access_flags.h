/**
 * @file access_flags.h
 * @brief Flags names
 * File containing functions that create flags lists with their names for each case necessary.
 *
 */

#ifndef ACCESS_FLAGS_H_
#define ACCESS_FLAGS_H_

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_FLAGS 32

/**
 * @brief List node.
 * Definition of node as the struct with same name.
 */
typedef struct ac_node ac_node;

/**
 * @brief Node structure.
 *
 * Node structure definition that stores a flag information and a pointer to the next node.
 */
struct ac_node {
    char* flag_name;
    uint32_t flag_code;
    ac_node* next;
};

/**
 * Possible flags of a class
 */
extern ac_node* AC_FLAGS_CLASS;

/**
 * Possible flags of a field
 */
extern ac_node* AC_FLAGS_FIELD;

/**
 * Possible flags of a method
 */
extern ac_node* AC_FLAGS_METHOD;

/**
 * Possible flags of inner_classes
 */
extern ac_node* AC_FLAGS_INNER_CLASSES;

/**
 * Returns a pointer to a string containing the name of the flag code.
 * @param ac_list ponteiro para nó de uma lista de flags.
 * @param code number code of the flag.
 */
char** get_flags_name(ac_node* ac_list, uint32_t code);

/**
 * Add a new node with a new flag to a list.
 * @param ac_list pointer to the flag list.
 * @param code number code of the flag.
 * @param name string with the name of the flag.
 */
void add_flag(ac_node** ac_list, uint32_t code, char* name);
void populate_ac_flags_class();
void populate_ac_flags_method();
void populate_ac_flags_inner_classes();

/**
 * Print flag name
 * @param ac_list flag list.
 * @param code number code of the flag.
 */
void print_flags(ac_node* ac_list, uint32_t code);

/**
 * Free the memory utilized by the lists.
 */
void deinit_ac_flags();

#endif
