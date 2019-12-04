#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "classfile.h"
#include "frame.h"
#include "methodarea.h"
#include "opcodes.h"
#include "object.h"

#define MAX_FRAMES  32
#define MAXHEAP     256
#define MAXSTATICS  256

typedef struct Static {
  char *class;
  char *name;
  char *type;
  ObjectField value;
} Static;

typedef struct JVM {
  uint32_t pc;
  Frame *frames[MAX_FRAMES];
  int32_t frame_index;    /* top of frame stack index */
  /* uint8_t *heap; */
  MethodArea *method_area;
  /* NativeMethodArea nma; */
  int32_t current_class_index;
  int32_t current_method_index;
  bool jmp;
  bool ret;
  uint64_t retval;

  void *heap[MAXHEAP];
  int32_t heap_index;

  Static *statics[MAXSTATICS];
  int32_t static_index;
} JVM;

/**
 * Initializes JVM memory area pointed to by jvm pointer.
 * @param jvm non-null pointer to jvm struct to be initialized
 */
void init_jvm(JVM *jvm);

/**
 * Deinitializes JVM memory area pointed to by jvm pointer.
 * Notably, heap, frames, and auxiliary structures are freed
 * @param jvm non-null pointer to jvm struct to be deinitialized
 */
void deinit_jvm(JVM *jvm);

/**
 * Load the classfile into the jvm's MethodArea
 * Classfile reference is directly assigned (will not be copied in any way).
 * Therefore the allocated memory must be persitent and is maintained by the user.
 * @param jvm non-null pointer to jvm to which cf will be loaded
 * @param cf classfile to be loaded
 */
void jvm_load_classfile(JVM *jvm, classfile *cf);

/**
 * Load the class with class_name into the jvm's MethodArea
 * File will be read from disk. An assertion will check whether the file can be read.
 * @param jvm non-null pointer to jvm to which class will be loaded
 * @param class_name name of the class to be loaded (without .class extension)
 */
void jvm_load_class(JVM *jvm, char *class_name);

/**
 * Set class which owns current method being run
 * Assumes class is already loaded
 * @param jvm non-null pointer to jvm to which class will be set
 * @param class_name name of the class to be set as current
 */
void jvm_set_current_class(JVM *jvm, char *class_name);

/**
 * Set current method to run
 * Assumes method belongs to class set as current.
 * @param jvm non-null pointer to jvm to which method will be set
 * @param method_name name of the method to be set as current
 */
void jvm_set_current_method(JVM *jvm, char *method_name);

void jvm_exec_clinit(JVM *jvm);

/**
 * Set the current class and current method members with index in MethodArea.
 * Assumes that the current class does contain the method required
 * @param jvm non-null pointer to jvm to which method will be set
 * @param class_index index to classfile in JVM's MethodArea
 * @param method_index index to the desired method in the classfile
 */
void jvm_load_method(JVM *jvm, uint32_t class_index, uint32_t method_index);

/**
 * Returns a reference to the class which runs the method being run
 * @param jvm pointer to jvm
 */
classfile *jvm_get_current_class(JVM *jvm);

/**
 * Returns the name of the class which runs the method being run
 * @param jvm pointer to jvm
 */
char *jvm_get_current_class_name(JVM *jvm);

/**
 * Returns a reference to the method being run
 * @param jvm pointer to jvm
 */
method_info *jvm_get_current_method(JVM *jvm);

/**
 * Returns the name of the method being run
 * @param jvm pointer to jvm
 */
char *jvm_get_current_method_name(JVM *jvm);

/**
 * Creates a frame for a call to the current method and pushes it onto the frame stack of jvm
 * @param jvm pointer to jvm
 */
void jvm_push_frame(JVM *jvm);

/**
 * Pop the current frame off the stack and free all its resources
 * @param jvm pointer to jvm
 */
void jvm_pop_frame(JVM *jvm);

/**
 * Returns a pointer to the frame on top of the stack
 * @param jvm pointer to jvm
 */
Frame *jvm_peek_frame(JVM *jvm);

/** Run one jvm cycle
 * Returns 0 when return from main or clinit is called, 1 otherwise
 * @param jvm pointer to jvm
 */
int jvm_cycle(JVM *jvm);

/**
 * Runs until return from main or clinit is reached.
 * @param jvm pointer to jvm
 */
void jvm_run(JVM *jvm);

/**
 * Load current method into frame stack and run it
 * @param jvm pointer to jvm
 */
void jvm_run_method(JVM *jvm);

/**
 * Returns whether jvm is currently running a main method
 * @param jvm pointer to jvm
 */
int jvm_in_main(JVM *jvm);

/**
 * Returns whether jvm is currently running <clinit> method
 * @param jvm pointer to jvm
 */
bool jvm_in_clinit(JVM *jvm);

/**
 * Save current frame context
 * PC, current class and current method's indexes are saved to frame (typically the callee).
 * @param jvm pointer to jvm
 */
void jvm_save_context(JVM *jvm);

/**
 * Restore context to previous frame (callee)
 * PC and previous class' and method's indexes are restored.
 * @param jvm pointer to jvm
 */
void jvm_restore_context(JVM *jvm);

/**
 * Add new pointer to jvm's heap table
 * The heap space is for memory allocated during runtime.
 * When an object is allocated, it persists until the JVM is deinitialized.
 * Upon deinitialization, all heap memory is freed.
 * The heap uses a stack structure, where the latest placed pointers are freed first.
 * Therefore, nested structures must have their 'leafs' placed after the 'parents' (i.e. 2d,3d arrays)
 * @param jvm pointer to jvm
 * @param ptr pointer to be added to the heap
 */
void jvm_add_to_heap(JVM *jvm, void *ptr);

typedef void (*operation)(Frame *, uint32_t, uint32_t);

void nop(Frame *f, uint32_t a0, uint32_t a1);

void ldc(Frame *f, uint32_t a0, uint32_t a1);

void istore(Frame *f, uint32_t a0, uint32_t a1);
void istore_0(Frame *f, uint32_t a0, uint32_t a1);
void istore_1(Frame *f, uint32_t a0, uint32_t a1);
void istore_2(Frame *f, uint32_t a0, uint32_t a1);
void istore_3(Frame *f, uint32_t a0, uint32_t a1);

void iload(Frame *f, uint32_t a0, uint32_t a1);
void iload_0(Frame *f, uint32_t a0, uint32_t a1);
void iload_1(Frame *f, uint32_t a0, uint32_t a1);
void iload_2(Frame *f, uint32_t a0, uint32_t a1);
void iload_3(Frame *f, uint32_t a0, uint32_t a1);

void isub(Frame *f, uint32_t a0, uint32_t a1);
void iadd(Frame *f, uint32_t a0, uint32_t a1);
void idiv(Frame *f, uint32_t a0, uint32_t a1);
void imul(Frame *f, uint32_t a0, uint32_t a1);
void iand(Frame *f, uint32_t a0, uint32_t a1);
void ior(Frame *f, uint32_t a0, uint32_t a1);
void ishr(Frame *f, uint32_t a0, uint32_t a1);
void ishl(Frame *f, uint32_t a0, uint32_t a1);
void iushr(Frame *f, uint32_t a0, uint32_t a1);
void irem(Frame *f, uint32_t a0, uint32_t a1);
void ineg(Frame *f, uint32_t a0, uint32_t a1);

void return_func(Frame *f, uint32_t a0, uint32_t a1);
void ireturn(Frame *f, uint32_t a0, uint32_t a1);
void dreturn(Frame *f, uint32_t a0, uint32_t a1);
void lreturn(Frame *f, uint32_t a0, uint32_t a1);
void freturn(Frame *f, uint32_t a0, uint32_t a1);

void invokevirtual(Frame *f, uint32_t a0, uint32_t a1);
void invokestatic(Frame *f, uint32_t a0, uint32_t a1);

/**
 * Passes the arguments from the caller to the callee's local variables array
 * @param jvm pointer to jvm
 * @param caller pointer to caller's frame
 * @param type callee's type descriptor
 */
void jvm_set_args(JVM *jvm, Frame *caller, char *type);
void invokespecial(Frame *f, uint32_t a0, uint32_t a1);

void getstatic(Frame *f, uint32_t a0, uint32_t a1);
void putstatic(Frame *f, uint32_t a0, uint32_t a1);

/**
 * Returns reference to static variable with name belonging to classname
 * A null pointer is returned if not such static variable is found.
 * @param jvm pointer to jvm containing static variable
 * @param classname name of the class to which the variable belongs
 * @param name name of the static variable
 */
Static *jvm_get_static(JVM *jvm, char *classname, char *name);

/**
 * Returns reference to a newly allocted static variable.
 * The newly allocated static variable is placed in the jvm's static variables stats.
 * It persists until the jvm is deallocated.
 * @param jvm pointer to jvm containing static variable
 */
Static *jvm_push_static(JVM *jvm);

void ldc_w(Frame *f, uint32_t a0, uint32_t a1);
void ldc2_w(Frame *f, uint32_t a0, uint32_t a1);

void dstore(Frame *f, uint32_t a0, uint32_t a1);
void dstore_0(Frame *f, uint32_t a0, uint32_t a1);
void dstore_1(Frame *f, uint32_t a0, uint32_t a1);
void dstore_2(Frame *f, uint32_t a0, uint32_t a1);
void dstore_3(Frame *f, uint32_t a0, uint32_t a1);

void dload(Frame *f, uint32_t a0, uint32_t a1);
void dload_0(Frame *f, uint32_t a0, uint32_t a1);
void dload_1(Frame *f, uint32_t a0, uint32_t a1);
void dload_2(Frame *f, uint32_t a0, uint32_t a1);
void dload_3(Frame *f, uint32_t a0, uint32_t a1);

void dadd(Frame *f, uint32_t a0, uint32_t a1);
void dsub(Frame *f, uint32_t a0, uint32_t a1);
void ddiv(Frame *f, uint32_t a0, uint32_t a1);
void dmul(Frame *f, uint32_t a0, uint32_t a1);
void dneg(Frame *f, uint32_t a0, uint32_t a1);
void drem(Frame *f, uint32_t a0, uint32_t a1);

void bipush(Frame *f, uint32_t a0, uint32_t a1);

void iconst_0(Frame *f, uint32_t a0, uint32_t a1);
void iconst_1(Frame *f, uint32_t a0, uint32_t a1);
void iconst_2(Frame *f, uint32_t a0, uint32_t a1);
void iconst_3(Frame *f, uint32_t a0, uint32_t a1);
void iconst_4(Frame *f, uint32_t a0, uint32_t a1);
void iconst_5(Frame *f, uint32_t a0, uint32_t a1);
void iconst_m1(Frame *f, uint32_t a0, uint32_t a1);

void if_icmpeq(Frame *f, uint32_t a0, uint32_t a1);
void if_icmpne(Frame *f, uint32_t a0, uint32_t a1);
void if_icmplt(Frame *f, uint32_t a0, uint32_t a1);
void if_icmpge(Frame *f, uint32_t a0, uint32_t a1);
void if_icmpgt(Frame *f, uint32_t a0, uint32_t a1);
void if_icmple(Frame *f, uint32_t a0, uint32_t a1);

void lconst_0(Frame *f, uint32_t a0, uint32_t a1);
void lconst_1(Frame *f, uint32_t a0, uint32_t a1);

void lstore(Frame *f, uint32_t a0, uint32_t a1);
void lstore_0(Frame *f, uint32_t a0, uint32_t a1);
void lstore_1(Frame *f, uint32_t a0, uint32_t a1);
void lstore_2(Frame *f, uint32_t a0, uint32_t a1);
void lstore_3(Frame *f, uint32_t a0, uint32_t a1);

void lload(Frame *f, uint32_t a0, uint32_t a1);
void lload_0(Frame *f, uint32_t a0, uint32_t a1);
void lload_1(Frame *f, uint32_t a0, uint32_t a1);
void lload_2(Frame *f, uint32_t a0, uint32_t a1);
void lload_3(Frame *f, uint32_t a0, uint32_t a1);

void ladd(Frame *f, uint32_t a0, uint32_t a1);
void lsub(Frame *f, uint32_t a0, uint32_t a1);
void lmul(Frame *f, uint32_t a0, uint32_t a1);
void ldiv_(Frame *f, uint32_t a0, uint32_t a1);

void iinc(Frame *f, uint32_t a0, uint32_t a1);

void goto_func(Frame *f, uint32_t a0, uint32_t a1);

void fconst_0(Frame *f, uint32_t a0, uint32_t a1);
void fconst_1(Frame *f, uint32_t a0, uint32_t a1);
void fconst_2(Frame *f, uint32_t a0, uint32_t a1);

void fstore(Frame *f, uint32_t a0, uint32_t a1);
void fstore_0(Frame *f, uint32_t a0, uint32_t a1);
void fstore_1(Frame *f, uint32_t a0, uint32_t a1);
void fstore_2(Frame *f, uint32_t a0, uint32_t a1);
void fstore_3(Frame *f, uint32_t a0, uint32_t a1);

void fload(Frame *f, uint32_t a0, uint32_t a1);
void fload_0(Frame *f, uint32_t a0, uint32_t a1);
void fload_1(Frame *f, uint32_t a0, uint32_t a1);
void fload_2(Frame *f, uint32_t a0, uint32_t a1);
void fload_3(Frame *f, uint32_t a0, uint32_t a1);

void fsub(Frame *f, uint32_t a0, uint32_t a1);
void fadd(Frame *f, uint32_t a0, uint32_t a1);
void fdiv(Frame *f, uint32_t a0, uint32_t a1);
void fmul(Frame *f, uint32_t a0, uint32_t a1);
void fneg(Frame *f, uint32_t a0, uint32_t a1);
void frem(Frame *f, uint32_t a0, uint32_t a1);

void ifeq(Frame *f, uint32_t a0, uint32_t a1);
void ifne(Frame *f, uint32_t a0, uint32_t a1);
void iflt(Frame *f, uint32_t a0, uint32_t a1);
void ifge(Frame *f, uint32_t a0, uint32_t a1);
void ifgt(Frame *f, uint32_t a0, uint32_t a1);
void ifle(Frame *f, uint32_t a0, uint32_t a1);
void ifnull(Frame *f, uint32_t a0, uint32_t a1);
void ifnonnull(Frame *f, uint32_t a0, uint32_t a1);

void i2f(Frame *f, uint32_t a0, uint32_t a1);
void i2d(Frame *f, uint32_t a0, uint32_t a1);

void i2b(Frame *f, uint32_t a0, uint32_t a1);
void i2c(Frame *f, uint32_t a0, uint32_t a1);
void i2l(Frame *f, uint32_t a0, uint32_t a1);
void i2s(Frame *f, uint32_t a0, uint32_t a1);

void sipush(Frame *f, uint32_t a0, uint32_t a1);

int tableswitch(JVM *jvm);

void aconst_null(Frame *f, uint32_t a0, uint32_t a);
void aload(Frame *f, uint32_t a0, uint32_t a1);
void aload_0(Frame *f, uint32_t a0, uint32_t a1);
void aload_1(Frame *f, uint32_t a0, uint32_t a1);
void aload_2(Frame *f, uint32_t a0, uint32_t a1);
void aload_3(Frame *f, uint32_t a0, uint32_t a1);

void astore(Frame *f, uint32_t a0, uint32_t a1);
void astore_0(Frame *f, uint32_t a0, uint32_t a1);
void astore_1(Frame *f, uint32_t a0, uint32_t a1);
void astore_2(Frame *f, uint32_t a0, uint32_t a1);
void astore_3(Frame *f, uint32_t a0, uint32_t a1);

void newarray(Frame *f, uint32_t a0, uint32_t a1);

void aastore(Frame *f, uint32_t a0, uint32_t a1);
void aaload(Frame *f, uint32_t a0, uint32_t a1);

void iastore(Frame *f, uint32_t a0, uint32_t a1);
void iaload(Frame *f, uint32_t a0, uint32_t a1);

void fastore(Frame *f, uint32_t a0, uint32_t a1);
void faload(Frame *f, uint32_t a0, uint32_t a1);

void lastore(Frame *f, uint32_t a0, uint32_t a1);
void laload(Frame *f, uint32_t a0, uint32_t a1);

void dastore(Frame *f, uint32_t a0, uint32_t a1);
void daload(Frame *f, uint32_t a0, uint32_t a1);

void bastore(Frame *f, uint32_t a0, uint32_t a1);
void baload(Frame *f, uint32_t a0, uint32_t a1);

void d2f(Frame *f, uint32_t a0, uint32_t a1);
void d2i(Frame *f, uint32_t a0, uint32_t a1);
void d2l(Frame *f, uint32_t a0, uint32_t a1);

void f2d(Frame *f, uint32_t a0, uint32_t a1);
void f2i(Frame *f, uint32_t a0, uint32_t a1);
void f2l(Frame *f, uint32_t a0, uint32_t a1);

void l2d(Frame *f, uint32_t a0, uint32_t a1);
void l2f(Frame *f, uint32_t a0, uint32_t a1);
void l2i(Frame *f, uint32_t a0, uint32_t a1);

void athrow(Frame *f, uint32_t a0, uint32_t a1);

void multianewarray(Frame *f, uint32_t a0, uint32_t a1);

extern operation optable[N_OPS];

/**
 * Allocates 2d array and places it in jvm's heap.
 * @param jvm pointer to jvm
 * @param counts array of length 2 containig length of each of the 2 dimensions
 * @param size size of each of the array's elements
 */
void jvm_alloc_array_2d(JVM *jvm, int32_t counts[], uint32_t size);

/**
 * Allocates 3d array and places it in jvm's heap.
 * @param jvm pointer to jvm
 * @param counts array of length 3 containig length of each of the 3 dimensions
 * @param size size of each of the array's elements
 */
void jvm_alloc_array_3d(JVM *jvm, int32_t counts[], uint32_t size);

void anewarray(Frame *f, uint32_t a0, uint32_t a1);

void dup(Frame *f, uint32_t a0, uint32_t a1);

void new(Frame *f, uint32_t a0, uint32_t a1);
void getfield(Frame *f, uint32_t a0, uint32_t a1);
void putfield(Frame *f, uint32_t a0, uint32_t a1);

/**
 * Returns a index to the field 'fieldname' in class 'classname' if found in jvm's MethodArea.
 * -1 is returned if the field is not found.
 * @param jvm pointer to jvm
 * @param classname name of the class to which the field belongs
 * @param fieldname name of the field
 */
int32_t jvm_get_field_index(JVM *jvm, char *classname, char *fieldname);

/**
 * Returns a reference to the field 'fieldname' in class 'classname' descriptor string.
 * NULL is returned if the field is not found.
 * @param jvm pointer to jvm
 * @param classname name of the class to which the field belongs
 * @param fieldname name of the field
 */
char *jvm_get_field_descriptor(JVM *jvm, char *classname, char *fieldname);

/**
 * Allocates new object of class 'classname' and places it onto the jvm's heap.
 * The object persists until the jvm is deinitialized.
 * The newly allocated object contains the number of fields corresponding to
 * instances of the class.
 * Each field is a union that can contain one of the primitive values or a reference.
 * @param jvm pointer to jvm
 * @param classname name of the class
 */
void jvm_alloc_object(JVM *jvm, char *classname);
