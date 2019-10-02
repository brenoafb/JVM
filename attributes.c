#include "attributes.h"

void read_code_attribute(Code_attribute *ptr, FILE *fp) {
  assert(fp);
  assert(ptr);
  ptr->max_stack = read_u2(fp);
  ptr->max_locals = read_u2(fp);
  ptr->code_length = read_u4(fp);
  ptr->code = calloc(sizeof(uint8_t), ptr->code_length);

  for (uint32_t i = 0; i < ptr->code_length; i++) {
    ptr->code[i] = read_u2(fp);
  }

  ptr->exception_table_length = read_u2(fp);
  ptr->exception_table = calloc(4*sizeof(uint16_t), ptr->exception_table_length);

  for (uint16_t i = 0; i < ptr->exception_table_length; i++) {
    ptr->exception_table[i].start_pc = read_u2(fp);
    ptr->exception_table[i].end_pc = read_u2(fp);
    ptr->exception_table[i].handler_pc = read_u2(fp);
    ptr->exception_table[i].catch_type = read_u2(fp);
  }

  ptr->attributes_count = read_u2(fp);
  if (ptr->attributes_count != 0) {
    printf("Warning: CodeAttribute attributes_count is not zero (%d, 0x%x).\n",
	   ptr->attributes_count, ptr->attributes_count);
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
