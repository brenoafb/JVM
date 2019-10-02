#include "attributes.h"

void read_code_attribute(Code_attribute *ptr, FILE *fp) {
  assert(fp);
  assert(ptr);
  assert(cp);

  ptr->max_stack = read_u2(fp);
  ptr->max_locals = read_u2(fp);
  ptr->code_length = read_u4(fp);
  ptr->code = calloc(sizeof(uint8_t), ptr->code_length);
  assert(ptr->code);

  #ifdef DEBUG
  printf("\t\t0x%04x 0x%04x 0x%08x\n", ptr->max_stack,
	 ptr->max_locals,
	 ptr->code_length);
  printf("\t\tInstructions:\n");
  #endif

  for (uint32_t i = 0; i < ptr->code_length; i++) {
    ptr->code[i] = read_u1(fp);
    #ifdef DEBUG
    printf("\t\t\t0x%02x\n", ptr->code[i]);
    #endif
  }

  ptr->exception_table_length = read_u2(fp);
  ptr->exception_table = calloc(4*sizeof(uint16_t), ptr->exception_table_length);
  if (ptr->exception_table_length > 0) {
    assert(ptr->exception_table_length);
  }

  #ifdef DEBUG
  printf("\t\tException count: 0x%04x\n", ptr->exception_table_length);
  if (ptr->exception_table_length > 0) {
    printf("\t\tExceptions\n");
    printf("\t\t\tStart\tEnd\tHandler\tCatch type\n");
  }
  #endif

  for (uint16_t i = 0; i < ptr->exception_table_length; i++) {
    ptr->exception_table[i].start_pc = read_u2(fp);
    ptr->exception_table[i].end_pc = read_u2(fp);
    ptr->exception_table[i].handler_pc = read_u2(fp);
    ptr->exception_table[i].catch_type = read_u2(fp);

    #ifdef DEBUG
    printf("\t\t\t0x%04x\t0x%04x\t0x%04x\t0x%04x\n", ptr->exception_table[i].start_pc,
	   ptr->exception_table[i].end_pc,
	   ptr->exception_table[i].handler_pc,
	   ptr->exception_table[i].catch_type);
    #endif
  }

  ptr->attributes_count = read_u2(fp);
  ptr->attributes = calloc(sizeof(attribute_info), ptr->attributes_count);

  #ifdef DEBUG
  printf("\t\tAttributes count: 0x%04x\n", ptr->attributes_count);
  #endif

  if (ptr->attributes_count != 0) {
    assert(ptr->attributes);
  }

  for (uint16_t i = 0; i < ptr->attributes_count; i++) {
    read_attribute_info(fp, &ptr->attributes_count[i], cp);
  }
}

void read_constantvalue_attribute(ConstantValue_attribute *ptr, FILE *fp) {
  assert(fp);
  assert(ptr);

  ptr->constantvalue_index = read_u2(fp);
}

void read_exceptions_attribute(Exceptions_attribute *ptr, FILE *fp) {
  assert(fp);
  assert(ptr);

  ptr->number_of_exceptions = read_u2(fp);
  ptr->exception_index_table = calloc(sizeof(uint16_t), ptr->number_of_exceptions);

  for (uint16_t i = 0; i < ptr->number_of_exceptions; i++) {
    ptr->exception_index_table[i] = read_u2(fp);
  }
}
