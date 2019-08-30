#include "utils.h"

classfile read_class_file(FILE *fp) {
  classfile cf = {0};

  if (!fp) return cf;

  int8_t x[4];
  fread(x, sizeof(int8_t), 4, fp);
  cf.magic = x[3] + ((x[2]+1) << 8) + ((x[1]+1) << 16) + ((x[0]+1) << 24);

  fread(&cf.minor_version, sizeof(uint16_t), 1, fp);
  fread(&cf.major_version, sizeof(uint16_t), 1, fp);

  fread(&cf.cpsize, sizeof(uint16_t), 1, fp);
  // not reading constant pool table yet
  fseek(fp, cf.cpsize, SEEK_CUR);

  fread(&cf.access_flags, sizeof(uint16_t), 1, fp);
  fread(&cf.this_class, sizeof(uint16_t), 1, fp);
  fread(&cf.super_class, sizeof(uint16_t), 1, fp);

  fread(&cf.interfaces_count, sizeof(uint16_t), 1, fp);
  // not reading interface table yet
  fseek(fp, cf.interfaces_count, SEEK_CUR);

  fread(&cf.fields_count, sizeof(uint16_t), 1, fp);
  // not reading field table yet
  fseek(fp, cf.fields_count, SEEK_CUR);

  fread(&cf.methods_count, sizeof(uint16_t), 1, fp);
  // not reading method table yet
  fseek(fp, cf.methods_count, SEEK_CUR);

  fread(&cf.attributes_count, sizeof(uint16_t), 1, fp);
  // not reading attribute table yet

  fclose(fp);

  cf_convert_endian(&cf);

  return cf;
}

void cf_convert_endian(classfile *cf) {
  cf->minor_version    = switch_endian(cf->minor_version);
  cf->major_version    = switch_endian(cf->major_version);
  cf->cpsize           = switch_endian(cf->cpsize);
  cf->access_flags     = switch_endian(cf->access_flags);
  cf->this_class       = switch_endian(cf->this_class);
  cf->super_class      = switch_endian(cf->super_class);
  cf->interfaces_count = switch_endian(cf->interfaces_count);
  cf->fields_count     = switch_endian(cf->fields_count);
  cf->methods_count    = switch_endian(cf->methods_count);
  cf->attributes_count = switch_endian(cf->attributes_count);
}

uint16_t switch_endian(uint16_t x) {
  uint16_t tmp = x;
  tmp >>= 8;
  x <<= 8;
  return x + tmp;
}

void print_class_file_summary(classfile *cf) {
  if (!cf) return;
  printf("magic=%x\n", cf->magic);

  printf("minor=%x\n", cf->minor_version);
  printf("major=%x\n", cf->major_version);

  printf("cpsize=%d\n", cf->cpsize);

  printf("access_flags=%d\n", cf->access_flags);;
  printf("this_class=%d\n", cf->this_class);
  printf("super_class=%d\n", cf->super_class);
  printf("interfaces_count=%d\n", cf->interfaces_count);

  printf("fields_count=%d\n", cf->fields_count);
  printf("methods_count=%d\n", cf->methods_count);
  printf("attributes_count=%d\n", cf->attributes_count);
}
