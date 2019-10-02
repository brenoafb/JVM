#include "constant_info.h"

void read_Class_info(CONSTANT_Class_info *ptr, FILE *fp) {
  CONSTANT_read_verify(Class);
  ptr->name_index = read_u2(fp);
}

void read_Fieldref_info(CONSTANT_Fieldref_info *ptr, FILE *fp) {
  CONSTANT_read_verify(Fieldref);
  ptr->class_index = read_u2(fp);
  ptr->name_and_type_index = read_u2(fp);
}

void read_NameAndType_info(CONSTANT_NameAndType_info *ptr, FILE *fp) {
  CONSTANT_read_verify(NameAndType);
  ptr->name_index = read_u2(fp);
  ptr->descriptor_index = read_u2(fp);
}

void read_Utf8_info(CONSTANT_Utf8_info *ptr, FILE *fp) {
  CONSTANT_read_verify(Utf8);
  ptr->length = read_u2(fp);
  ptr->bytes = calloc(ptr->length+1, sizeof(uint8_t));
  assert(ptr->bytes);
  fread(ptr->bytes, sizeof(uint8_t), ptr->length, fp);
  printf("\tRead utf8(%d/0x%x): %s\n", ptr->length, ptr->length, ptr->bytes);
}

void read_Methodref_info(CONSTANT_Methodref_info *ptr, FILE *fp) {
  CONSTANT_read_verify(Methodref);
  ptr->class_index = read_u2(fp);
  ptr->name_and_type_index = read_u2(fp);
}

void read_InterfaceMethodref_info(CONSTANT_InterfaceMethodref_info *ptr, FILE *fp) {
  CONSTANT_read_verify(InterfaceMethodref);
  ptr->class_index = read_u2(fp);
  ptr->name_and_type_index = read_u2(fp);
}

void read_String_info(CONSTANT_String_info *ptr, FILE *fp) {
  CONSTANT_read_verify(String);
  ptr->string_index = read_u2(fp);
}

void read_Integer_info(CONSTANT_Integer_info *ptr, FILE *fp) {
  CONSTANT_read_verify(Integer);
  ptr->bytes = read_u4(fp);
}

void read_Float_info(CONSTANT_Float_info *ptr, FILE *fp) {
  CONSTANT_read_verify(Float);
  ptr->bytes = read_u4(fp);
  // TODO That float was read correctly (i.e. as a float)
}

void read_Long_info(CONSTANT_Long_info *ptr, FILE *fp) {
  CONSTANT_read_verify(Long);
  ptr->high_bytes = read_u4(fp);
  ptr->low_bytes = read_u4(fp);
}

void read_Double_info(CONSTANT_Double_info *ptr, FILE *fp) {
  CONSTANT_read_verify(Double);
  ptr->high_bytes = read_u4(fp);
  ptr->low_bytes = read_u4(fp);
  // TODO That double was read correctly (i.e. as a double)
}
