#include "classfile.h"

classfile read_class_file(FILE *fp) {
  classfile cf = {0};

  if (!fp) return cf;

  int8_t x[4];
  fread(x, sizeof(int8_t), 4, fp);
  cf.magic = x[3] + ((x[2]+1) << 8) + ((x[1]+1) << 16) + ((x[0]+1) << 24);

  fread(&cf.minor_version, sizeof(uint16_t), 1, fp);
  fread(&cf.major_version, sizeof(uint16_t), 1, fp);

  fread(&cf.cpsize, sizeof(uint16_t), 1, fp);
  uint16_t cpsize = switch_endian(cf.cpsize);
  cf.constant_pool = calloc(sizeof(cp_info), cf.cpsize);
  read_constant_pool(fp, cf.constant_pool, cpsize);
  // fseek(fp, cf.cpsize, SEEK_CUR);

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

void read_constant_pool(FILE *fp, cp_info cp[], int cpsize) {
  printf("cpsize=%d (0x%x)\n", cpsize, cpsize);
  for (int i = 0; i < cpsize - 1; i++) {
    cp_info *ptr = &cp[i];
    fread(&ptr->tag, sizeof(uint8_t), 1, fp);
    read_constant_pool_entry(fp, ptr);
  }
}

void read_constant_pool_entry(FILE *fp, cp_info *cp) {
  assert(fp);
  assert(cp);

  switch (cp->tag) {
  case CONSTANT_Class:
    printf("Reading class\n");
    read_Class_info(&cp->info.class_info, fp);
    break;
  case CONSTANT_Fieldref:
    printf("Reading fieldref\n");
    read_Fieldref_info(&cp->info.fieldref_info, fp);
    break;
  case CONSTANT_Methodref:
    printf("Reading methodref\n");
    read_Methodref_info(&cp->info.methodref_info, fp);
    break;
  case CONSTANT_InterfaceMethodref:
    printf("Reading interfacemethodref\n");
    read_InterfaceMethodref_info(&cp->info.interfacemethodref_info, fp);
    break;
  case CONSTANT_String:
    printf("Reading string\n");
    read_String_info(&cp->info.string_info, fp);
    break;
  case CONSTANT_Integer:
    printf("Reading integer\n");
    read_Integer_info(&cp->info.integer_info, fp);
    break;
  case CONSTANT_Float:
    printf("Reading float\n");
    read_Float_info(&cp->info.float_info, fp);
    break;
  case CONSTANT_Long:
    printf("Reading long\n");
    read_Long_info(&cp->info.long_info, fp);
    break;
  case CONSTANT_Double:
    printf("Reading double\n");
    read_Double_info(&cp->info.double_info, fp);
    break;
  case CONSTANT_NameAndType:
    printf("Reading nameandtype\n");
    read_NameAndType_info(&cp->info.nameandtype_info, fp);
    break;
  case CONSTANT_Utf8:
    printf("Reading utf8\n");
    read_Utf8_info(&cp->info.utf8_info, fp);
    break;
  default:
    printf("Warning: unknown tag %x\n", cp->tag);
    break;
  }
}

void read_attribute_info(FILE *fp, attribute_info *ptr, cp_info *cp) {
  assert(fp);
  assert(ptr);
  assert(cp);

  fread(&ptr->attribute_name_index, sizeof(uint16_t), 1, fp);
  fread(&ptr->attribute_length, sizeof(uint32_t), 1, fp);

  char *str = get_cp_string(cp, ptr->attribute_name_index);

  if (strcmp("Code", str)) {
    // TODO read code attribute
  } else if (strcmp("ConstantValue", str)) {
    // TODO read ConstantValue attribute
  } else if (strcmp("Exceptions", str)) {
    // TODO read Exceptions attribute
  } else {
    // TODO unknown attribute
    printf("Warning: unknown attribute type %s\n", str);
  }
}

char *get_cp_string(cp_info *cp, uint16_t index) {
  assert(cp);

  cp_info *entry = &cp[index];
  assert(entry->tag == CONSTANT_Utf8);
  
  return entry->info.utf8_info.bytes;
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

void deinit_cp_entry(cp_info *ptr) {
  assert(ptr);
  if (ptr->tag == CONSTANT_Utf8) {
    CONSTANT_Utf8_info *info = &ptr->info.utf8_info;
    free(info->bytes);
  }
}

void deinit_constant_pool(cp_info cp[], uint16_t cpsize) {
  assert(cp);
  for (int i = 0; i < cpsize; i++) {
    deinit_cp_entry(&cp[i]);
  }
}

void deinit_class_file(classfile *cf) {
  deinit_constant_pool(cf->constant_pool, cf->cpsize);
  free(cf->constant_pool);
  // TODO free interfaces
  // TODO free fields
}
