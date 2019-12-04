/**
 * @file methodarea.h
 * @brief Method Area functions
 * File containing functions that initialize and free the method area, load classes into it,
 * and realize consult operations.
 *
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "classfile.h"
#include "types.h"

#define MAX_CLASSES 32
#define BUFSIZE 256

typedef struct MethodArea {
  uint32_t n_classes;
  classfile *classes[MAX_CLASSES];
} MethodArea;

/**
 * Initializes MethodArea
 * @param ma non-null pointer to allocated MethodArea memory.
 */
void init_method_area(MethodArea *ma);

/**
 * Deinitializes MethodArea
 * Each of the classes contained is freed.
 * @param ma non-null pointer to a MethodArea instance.
 */
void deinit_method_area(MethodArea *ma);

/**
 * Loads class 'classname' into MethodArea instance 'ma'.
 * Class is only loaded if it is not already loaded.
 * An assertion verifies whether the file can be read.
 * Upon reading the file, the classfile reference is placed into the MethodArea.
 * @param ma pointer to methodarea instance.
 * @param class_name name of the class to be loaded (without .class extension)
 */
void method_area_load_class(MethodArea *ma, char *class_name);

/**
 * Loads classfile directly into the MethodArea instance 'ma'.
 * Deprecated.
 */
void method_area_load_classfile(MethodArea *ma, classfile *cf);

/**
 * Looks up whether MethodArea has class 'class_name' loaded.
 * If the class is loaded, an index to it in the MethodArea's classes array is returned.
 * Otherwise, -1 is returned.
 * @param ma pointer to MethodArea instance
 * @param class_name name of the class to be looked up
 */
int method_area_class_lookup(MethodArea *ma, char *class_name);

/**
 * Looks up whether class with index 'class_index' has method 'method_name' with descriptor 'type'
 * If the class contains the method, an index to it in the class' classfile is returned.
 * Otherwise, -1 is returned.
 * @param ma pointer to MethodArea instance
 * @param class_index index of the class in the MethodArea's classes array
 * @param method_name name of the method to be looked up
 * @param type type descriptor of the method to be looked up
 */
int method_area_method_lookup(MethodArea *ma, int class_index, char *method_name, char *type);
