#include "constant_info.h"

void read_Class_info(CONSTANT_Class_info *ptr, FILE *fp) {
  CONSTANT_read_verify(Class);
  fread(&ptr->name_index, sizeof(uint16_t), 1, fp);
}

void read_Fieldref_info(CONSTANT_Fieldref_info *ptr, FILE *fp) {
  CONSTANT_read_verify(Fieldref);
  fread(&ptr->class_index, sizeof(uint16_t), 1, fp);
  fread(&ptr->name_and_type_index, sizeof(uint16_t), 1, fp);
}

void read_NameAndType_info(CONSTANT_NameAndType_info *ptr, FILE *fp) {
  CONSTANT_read_verify(NameAndType);
  fread(&ptr->name_index, sizeof(uint16_t), 1, fp);
  fread(&ptr->descriptor_index, sizeof(uint16_t), 1, fp);
}

void read_Utf8_info(CONSTANT_Utf8_info *ptr, FILE *fp) {
  CONSTANT_read_verify(Utf8);
  fread(&ptr->length, sizeof(uint16_t), 1, fp);
  ptr->length = switch_endian(ptr->length);
  ptr->bytes = calloc(ptr->length+1, sizeof(uint8_t));
  assert(ptr->bytes);
  fread(ptr->bytes, sizeof(uint8_t), ptr->length, fp);
  printf("\tRead utf8(%d/0x%x): %s\n", ptr->length, ptr->length, ptr->bytes);
}

void read_Methodref_info(CONSTANT_Methodref_info *ptr, FILE *fp) {
  CONSTANT_read_verify(Methodref);
  fread(&ptr->class_index, sizeof(uint16_t), 1, fp);
  fread(&ptr->name_and_type_index, sizeof(uint16_t), 1, fp);
}

void read_InterfaceMethodref_info(CONSTANT_InterfaceMethodref_info *ptr, FILE *fp) {
  CONSTANT_read_verify(InterfaceMethodref);
  fread(&ptr->class_index, sizeof(uint16_t), 1, fp);
  fread(&ptr->name_and_type_index, sizeof(uint16_t), 1, fp);
}

void read_String_info(CONSTANT_String_info *ptr, FILE *fp) {
  CONSTANT_read_verify(String);
  fread(&ptr->string_index, sizeof(uint16_t), 1, fp);
}

void read_Integer_info(CONSTANT_Integer_info *ptr, FILE *fp) {
  CONSTANT_read_verify(Integer);
  fread(&ptr->bytes, sizeof(uint32_t), 1, fp);
  // TODO Verify endinanness
}

void read_Float_info(CONSTANT_Float_info *ptr, FILE *fp) {
  CONSTANT_read_verify(Float);
  fread(&ptr->bytes, sizeof(uint32_t), 1, fp);
  // TODO Verify endinanness
}

void read_Long_info(CONSTANT_Long_info *ptr, FILE *fp) {
  CONSTANT_read_verify(Long);
  fread(&ptr->high_bytes, sizeof(uint32_t), 1, fp);
  fread(&ptr->low_bytes, sizeof(uint32_t), 1, fp);
  // TODO Verify endinanness
}

void read_Double_info(CONSTANT_Double_info *ptr, FILE *fp) {
  CONSTANT_read_verify(Double);
  fread(&ptr->high_bytes, sizeof(uint32_t), 1, fp);
  fread(&ptr->low_bytes, sizeof(uint32_t), 1, fp);
  // TODO Verify endinanness
}
