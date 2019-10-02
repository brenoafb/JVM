#include "classfile.h"

classfile read_class_file(FILE *fp) {
  classfile cf = {0};

  if (!fp) return cf;

  int8_t x[4];
  fread(x, sizeof(int8_t), 4, fp);
  cf.magic = x[3] + ((x[2]+1) << 8) + ((x[1]+1) << 16) + ((x[0]+1) << 24);

  // minor/major version
  fread(&cf.minor_version, sizeof(uint16_t), 1, fp);
  cf.minor_version = switch_endian_16(cf.minor_version);
  fread(&cf.major_version, sizeof(uint16_t), 1, fp);
  cf.major_version = switch_endian_16(cf.major_version);

  // constant-pool
  fread(&cf.cpsize, sizeof(uint16_t), 1, fp);
  cf.cpsize = switch_endian_16(cf.cpsize);
  cf.constant_pool = calloc(sizeof(cp_info), cf.cpsize);
  read_constant_pool(fp, cf.constant_pool, cf.cpsize);

  // access flags, this/super class
  fread(&cf.access_flags, sizeof(uint16_t), 1, fp);
  cf.access_flags = switch_endian_16(cf.access_flags);

  fread(&cf.this_class, sizeof(uint16_t), 1, fp);
  cf.this_class = switch_endian_16(cf.this_class);

  fread(&cf.super_class, sizeof(uint16_t), 1, fp);
  cf.super_class = switch_endian_16(cf.super_class);

  // interfaces
  fread(&cf.interfaces_count, sizeof(uint16_t), 1, fp);
  cf.interfaces_count = switch_endian_16(cf.interfaces_count);
  // not reading interface table yet
  fseek(fp, cf.interfaces_count, SEEK_CUR);

  // fields
  fread(&cf.fields_count, sizeof(uint16_t), 1, fp);
  cf.fields_count = switch_endian_16(cf.fields_count);
  cf.fields = calloc(sizeof(field_info), cf.fields_count);
  read_fields(fp, cf.fields, cf.fields_count, cf.constant_pool);

  // methods
  fread(&cf.methods_count, sizeof(uint16_t), 1, fp);
  cf.methods_count = switch_endian_16(cf.methods_count);
  cf.methods = calloc(sizeof(method_info), cf.methods_count);
  read_methods(fp, cf.methods, cf.methods_count, cf.constant_pool);

  // attributes
  fread(&cf.attributes_count, sizeof(uint16_t), 1, fp);
  cf.attributes_count = switch_endian_16(cf.attributes_count);
  cf.attributes = calloc(sizeof(attribute_info), cf.attributes_count);
  read_attributes(fp, cf.attributes, cf.attributes_count, cf.constant_pool);

  fclose(fp);

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

void read_fields(FILE *fp, field_info fields[], uint16_t fields_count, cp_info *cp) {
  printf("fields_count=%d (0x%x)\n", fields_count, fields_count);
  for (int i = 0; i < fields_count; i++) {
    field_info *ptr = &fields[i];
    read_field_entry(fp, ptr, cp);
  }
}

void read_field_entry(FILE *fp, field_info *field, cp_info *cp) {
  assert(fp);
  assert(field);
  assert(cp);

  fread(&field->access_flags, sizeof(uint16_t), 1, fp);
  field->access_flags = switch_endian_16(field->access_flags);

  fread(&field->name_index, sizeof(uint16_t), 1, fp);
  field->name_index = switch_endian_16(field->name_index);

  fread(&field->descriptor_index, sizeof(uint16_t), 1, fp);
  field->descriptor_index = switch_endian_16(field->descriptor_index);

  fread(&field->attributes_count, sizeof(uint16_t), 1, fp);
  field->attributes_count = switch_endian_16(field->attributes_count);

  field->attributes = calloc(sizeof(attribute_info), field->attributes_count);
  assert(field->attributes);

  read_attributes(fp, field->attributes, field->attributes_count, cp);
}

void read_methods(FILE *fp, method_info methods[], uint16_t methods_count, cp_info *cp) {
  printf("methods_count=%d (0x%x)\n", methods_count, methods_count);
  for (int i = 0; i < methods_count; i++) {
    method_info *ptr = &methods[i];
    read_method_entry(fp, ptr, cp);
  }
}

void read_method_entry(FILE *fp, method_info *method, cp_info *cp) {
  read_field_entry(fp, (field_info *) method, cp);
}


void read_attributes(FILE *fp, attribute_info attributes[], uint16_t attributes_count, cp_info *cp) {
  printf("attributes_count=%d (0x%x)\n", attributes_count, attributes_count);
  for (int i = 0; i < attributes_count; i++) {
    attribute_info *ptr = &attributes[i];
    read_attribute_info(fp, ptr, cp);
  }
}

void read_attribute_info(FILE *fp, attribute_info *ptr, cp_info *cp) {
  assert(fp);
  assert(ptr);
  assert(cp);

  fread(&ptr->attribute_name_index, sizeof(uint16_t), 1, fp);
  ptr->attribute_name_index = switch_endian_16(ptr->attribute_name_index);
  fread(&ptr->attribute_length, sizeof(uint32_t), 1, fp);
  ptr->attribute_length = switch_endian_16(ptr->attribute_length);

  char *str = get_cp_string(cp, ptr->attribute_name_index - 1);

  if (strcmp("Code", str)) {
    // TODO read code attribute
  } else if (strcmp("ConstantValue", str)) {
    // TODO read ConstantValue attribute
  } else if (strcmp("Exceptions", str)) {
    // TODO read Exceptions attribute
  } else {
    printf("Warning: unknown attribute type %s\n", str);
  }

  // not reading attributes for now
  fseek(fp, ptr->attribute_length, SEEK_CUR);
}

char *get_cp_string(cp_info *cp, uint16_t index) {
  assert(cp);

  cp_info *entry = &cp[index];
  assert(entry->tag == CONSTANT_Utf8);

  return (char *) entry->info.utf8_info.bytes;
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

void print_cp_detail(classfile *cf) {
  printf("Constant pool members:\n");
  for (int i = 0; i < cf->cpsize-1; i++) {
    printf("\t%d: ", i);
    switch(cf->constant_pool[i].tag) {
    case CONSTANT_Utf8                 :
      printf("Utf8: ");
      char *str = get_cp_string(cf->constant_pool, i);
      printf("\"%s\"\n", str);
      break;
    case CONSTANT_Integer              :
      printf("Integer\n");
      break;
    case CONSTANT_Float                :
      printf("Float\n");
      break;
    case CONSTANT_Long                 :
      printf("Long\n");
      break;
    case CONSTANT_Double               :
      printf("Double\n");
      break;
    case CONSTANT_Class                :
      printf("Class\n");
      break;
    case CONSTANT_String               :
      printf("String\n");
      break;
    case CONSTANT_Fieldref             :
      printf("Fieldref\n");
      break;
    case CONSTANT_Methodref            :
      printf("Methodref\n");
      break;
    case CONSTANT_InterfaceMethodref   :
      printf("InterfaceMethodref\n");
      break;
    case CONSTANT_NameAndType          :
      printf("NameAndType\n");
      break;
    }
  }
}

void deinit_cp_entry(cp_info *ptr) {
  assert(ptr);
  if (ptr->tag == CONSTANT_Utf8) {
    CONSTANT_Utf8_info *info = &ptr->info.utf8_info;
    free(info->bytes);
  }
}

void deinit_constant_pool(cp_info cp[], uint16_t cpsize) {
  for (int i = 0; i < cpsize; i++) {
    deinit_cp_entry(&cp[i]);
  }
}

void deinit_class_file(classfile *cf) {
  deinit_constant_pool(cf->constant_pool, cf->cpsize);
  free(cf->constant_pool);

  deinit_fields(cf->fields, cf->fields_count);
  free(cf->fields);

  deinit_methods(cf->methods, cf->methods_count);
  free(cf->methods);

  deinit_attributes(cf->attributes, cf->attributes_count);
  free(cf->attributes);

  // TODO free interfaces
}

void deinit_fields(field_info fields[], uint16_t fields_count) {
  for (int i = 0; i < fields_count; i++) {
    deinit_field_entry(&fields[i]);
  }
}
void deinit_field_entry(field_info *ptr) {
  for (int i = 0; i < ptr->attributes_count; i++) {
    deinit_attribute_info(&ptr->attributes[i]);
  }
  free(ptr->attributes);
}

void deinit_methods(method_info methods[], uint16_t method_count) {
  for (int i = 0; i < method_count; i++) {
    deinit_method_entry(&methods[i]);
  }
}

void deinit_method_entry(method_info *ptr) {
  deinit_field_entry((field_info *) ptr);
}

void deinit_attributes(attribute_info attributes[], uint16_t attributes_count) {
  for (int i = 0; i < attributes_count; i++) {
    deinit_attribute_info(&attributes[i]);
  }
}

void deinit_attribute_info(attribute_info *ptr) {
  // TODO
}
