/**
 * @file frame.h
 * @brief Frame
 * File containing the definition of a frame structure and functions to realize 
 * operations to change it.
 *
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "classfile.h"

/**
 * @brief Frame structure.
 *
 * Structure that stores the information that defines and is utilized by a frame from a JVM.
 */
typedef struct Frame {
  void *jvm;               /**< pointer to respective jvm reference  */
  uint32_t n_locals;       /**< computed at compile time             */
  uint64_t *locals;         /**< array of local variables            */
  uint32_t n_operands;     /**< computed at compile time             */
  uint64_t *operands;      /**< stack of operands                    */
  uint32_t i;              /**< top of stack index                   */
  cp_info *cp;             /**< reference to constant pool of class  */
  uint32_t pc;             /**< jvm's pc upon method call            */
  int32_t class_index;     /**< class index in method area           */
  int32_t method_index;    /**< method index in class                */
} Frame;

/**
 * Initializes a frame pointed by a jvm
 */
void init_frame(Frame *f, void *jvm, uint32_t n_locals, uint32_t n_operands, cp_info *cp,
		int32_t class_index, int32_t method_index);

/**
 * Deinitializes frame memory area pointed to by jvm pointer.
 * Notably, locals, operands, and auxiliary structures are freed
 * @param f non-null pointer to a frame struct to be deinitialized
 */
void deinit_frame(Frame *f);

/**
 * Push an integer to the top of the frame operand stack.
 * @param operand integer operand to be added to the stack.
 * @param f pointer to the current frame.
 */
void push_stack(Frame *f, uint64_t operand);

/**
 * Pop an integer of the top of the frame operand stack.
 * @param f pointer to the current frame.
 */
uint64_t pop_stack(Frame *f);

/**
 * Return de value of an integer of the top of the frame operand stack.
 * @param f pointer to the current frame.
 */
uint64_t peek_stack(Frame *f);


/**
 * Push a double to the top of the frame operand stack.
 * @param operand double operand to be added to the stack.
 * @param f pointer to the current frame.
 */
void push_stack_double(Frame *f, double d);

/**
 * Pop a double of the top of the frame operand stack.
 * @param f pointer to the current frame.
 */
double pop_stack_double(Frame *f);


/**
 * Push a long to the top of the frame operand stack.
 * @param operand long operand to be added to the stack.
 * @param f pointer to the current frame.
 */
void push_stack_long(Frame *f, int64_t x);

/**
 * Pop a long of the top of the frame operand stack.
 * @param f pointer to the current frame.
 */
int64_t pop_stack_long(Frame *f);


/**
 * Push a float to the top of the frame operand stack.
 * @param operand float operand to be added to the stack.
 * @param f pointer to the current frame.
 */
void push_stack_float(Frame *f, float x);

/**
 * Pop a float of the top of the frame operand stack.
 * @param f pointer to the current frame.
 */
float pop_stack_float(Frame *f);

/**
 * Push a 32 bits integer to the top of the frame operand stack.
 * @param operand integer operand to be added to the stack.
 * @param f pointer to the current frame.
 */
void push_stack_int(Frame *f, int32_t x);

/**
 * Pop a 32 bits integer of the top of the frame operand stack.
 * @param f pointer to the current frame.
 */
int32_t pop_stack_int(Frame *f);


/**
 * Push a void pointer to the top of the frame operand stack.
 * @param operand pointer operand to be added to the stack.
 * @param f pointer to the current frame.
 */
void push_stack_pointer(Frame *f, void *ptr);

/**
 * Pop a void pointer of the top of the frame operand stack.
 * @param f pointer to the current frame.
 */
void *pop_stack_pointer(Frame *f);


/**
 * Push a byte to the top of the frame operand stack.
 * @param operand byte operand to be added to the stack.
 * @param f pointer to the current frame.
 */
void push_stack_byte(Frame *f, int8_t x);

/**
 * Pop a byte of the top of the frame operand stack.
 * @param f pointer to the current frame.
 */
int8_t pop_stack_byte(Frame *f);

void frame_set_local(Frame *f, uint32_t index, uint64_t value);
uint64_t frame_get_local(Frame *f, uint32_t index);

void frame_set_local_int(Frame *f, uint32_t index, int32_t value);
int32_t frame_get_local_int(Frame *f, uint32_t index);

void frame_set_local_double(Frame *f, uint32_t index, double value);
double frame_get_local_double(Frame *f, uint32_t index);

void frame_set_local_float(Frame *f, uint32_t index, float value);
float frame_get_local_float(Frame *f, uint32_t index);

void frame_set_local_long(Frame *f, uint32_t index, int64_t value);
int64_t frame_get_local_long(Frame *f, uint32_t index);

void frame_set_local_pointer(Frame *f, uint32_t index, void *value);
void* frame_get_local_pointer(Frame *f, uint32_t index);
