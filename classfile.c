#include "classfile.h"

void read_class_file(classfile *cf, FILE *fp) {
  assert(cf);
  assert(fp);

  cf->magic = read_u4(fp);

  // minor/major version
  cf->minor_version = read_u2(fp);
  cf->major_version = read_u2(fp);

  #ifdef DEBUG
  printf("Magic: 0x%08x\n", cf->magic);
  printf("Minor: %d (0x%04x)\n", cf->minor_version, cf->minor_version);
  printf("Major: %d (0x%04x)\n", cf->major_version, cf->major_version);
  #endif

  // constant-pool

  cf->cpsize = read_u2(fp);
  cf->constant_pool = calloc(sizeof(cp_info), cf->cpsize);
  #ifdef DEBUG
  printf("cpsize: %d (0x%04x)\n", cf->cpsize, cf->cpsize);
  #endif
  read_constant_pool(fp, cf->constant_pool, cf->cpsize);

  // access flags, this/super class
  cf->access_flags = read_u2(fp);
  cf->this_class = read_u2(fp);
  cf->super_class = read_u2(fp);

  #ifdef DEBUG
  printf("Access flags: 0x%04x\n", cf->access_flags);
  printf("This class: 0x%04x\n", cf->this_class);
  printf("Super class: 0x%04x\n", cf->super_class);
  #endif

  // interfaces
  cf->interfaces_count = read_u2(fp);
  #ifdef DEBUG
  printf("Interfaces count: %d (0x%04x)\n", cf->interfaces_count, cf->interfaces_count);
  #endif

  if (cf->interfaces_count > 0) {
    // not reading interface table yet
  }

  // fields
  cf->fields_count = read_u2(fp);
  #ifdef DEBUG
  printf("Fields count: %d (0x%04x)\n", cf->fields_count, cf->fields_count);
  #endif

  cf->fields = calloc(sizeof(field_info), cf->fields_count);
  if (cf->fields_count > 0) {
    read_fields(fp, cf->fields, cf->fields_count, cf->constant_pool);
  }

  // methods
  cf->methods_count = read_u2(fp);
  #ifdef DEBUG
  printf("Methods count: %d (0x%04x)\n", cf->methods_count, cf->methods_count);
  #endif

  cf->methods = calloc(sizeof(method_info), cf->methods_count);
  if (cf->methods_count > 0) {
    read_methods(fp, cf->methods, cf->methods_count, cf->constant_pool);
  }

  // attributes
  cf->attributes_count = read_u2(fp);
  #ifdef DEBUG
  printf("Attributes count: %d (0x%04x)\n", cf->attributes_count, cf->attributes_count);
  #endif

  cf->attributes = calloc(sizeof(attribute_info), cf->attributes_count);
  if (cf->attributes_count > 0) {
    read_attributes(fp, cf->attributes, cf->attributes_count, cf->constant_pool);
  }
}

void read_constant_pool(FILE *fp, cp_info cp[], int cpsize) {
  for (int i = 0; i < cpsize - 1; i++) {
    cp_info *ptr = &cp[i];
    ptr->tag = read_u1(fp);
    #ifdef DEBUG
    printf("\t%d\t0x%02x\n", i+1, ptr->tag);
    #endif
    read_constant_pool_entry(fp, ptr);
  }
}

void read_constant_pool_entry(FILE *fp, cp_info *cp) {
  assert(fp);
  assert(cp);

  switch (cp->tag) {
  case CONSTANT_Class:
    read_Class_info(&cp->info.class_info, fp);
    break;
  case CONSTANT_Fieldref:
    read_Fieldref_info(&cp->info.fieldref_info, fp);
    break;
  case CONSTANT_Methodref:
    read_Methodref_info(&cp->info.methodref_info, fp);
    break;
  case CONSTANT_InterfaceMethodref:
    read_InterfaceMethodref_info(&cp->info.interfacemethodref_info, fp);
    break;
  case CONSTANT_String:
    read_String_info(&cp->info.string_info, fp);
    break;
  case CONSTANT_Integer:
    read_Integer_info(&cp->info.integer_info, fp);
    break;
  case CONSTANT_Float:
    read_Float_info(&cp->info.float_info, fp);
    break;
  case CONSTANT_Long:
    read_Long_info(&cp->info.long_info, fp);
    break;
  case CONSTANT_Double:
    read_Double_info(&cp->info.double_info, fp);
    break;
  case CONSTANT_NameAndType:
    read_NameAndType_info(&cp->info.nameandtype_info, fp);
    break;
  case CONSTANT_Utf8:
    read_Utf8_info(&cp->info.utf8_info, fp);
    break;
  default:
    printf("Warning: unknown tag %x\n", cp->tag);
    break;
  }
}

void read_fields(FILE *fp, field_info fields[], uint16_t fields_count, cp_info *cp) {
  for (int i = 0; i < fields_count; i++) {
    field_info *ptr = &fields[i];
    read_field_entry(fp, ptr, cp);
  }
}

void read_field_entry(FILE *fp, field_info *field, cp_info *cp) {
  assert(fp);
  assert(field);
  assert(cp);

  field->access_flags = read_u2(fp);
  field->name_index = read_u2(fp);
  field->descriptor_index = read_u2(fp);
  field->attributes_count = read_u2(fp);

  #ifdef DEBUG
  printf("\tAccess\tName\tDesc\tAttrCount\n");
  printf("\t0x%04x\t0x%04x\t0x%04x\t0x%04x\n", field->access_flags,
	 field->name_index,
	 field->descriptor_index,
	 field->attributes_count);
  #endif

  field->attributes = calloc(sizeof(attribute_info), field->attributes_count);
  assert(field->attributes);

  read_attributes(fp, field->attributes, field->attributes_count, cp);
}

void read_methods(FILE *fp, method_info methods[], uint16_t methods_count, cp_info *cp) {
  for (int i = 0; i < methods_count; i++) {
    method_info *ptr = &methods[i];
    read_method_entry(fp, ptr, cp);
  }
}

void read_method_entry(FILE *fp, method_info *method, cp_info *cp) {
  read_field_entry(fp, (field_info *) method, cp);
}


void read_attributes(FILE *fp, attribute_info attributes[], uint16_t attributes_count, cp_info *cp) {
  for (int i = 0; i < attributes_count; i++) {
    attribute_info *ptr = &attributes[i];
    read_attribute_info(fp, ptr, cp);
  }
}

void read_attribute_info(FILE *fp, attribute_info *ptr, cp_info *cp) {
  assert(fp);
  assert(ptr);
  assert(cp);

  ptr->attribute_name_index = read_u2(fp);

  ptr->attribute_length = read_u4(fp);


  char *str = get_cp_string(cp, ptr->attribute_name_index - 1);

  #ifdef DEBUG
  printf("\t\tAttr: 0x%04x 0x%08x %s\n", ptr->attribute_name_index,
	 ptr->attribute_length,
	 str);
  #endif

  if (strcmp("Code", str) == 0) {
    read_code_attribute(&ptr->info.code, fp, cp);
  } else if (strcmp("ConstantValue", str) == 0) {
    read_constantvalue_attribute(&ptr->info.constantvalue, fp);
  } else if (strcmp("Exceptions", str) == 0) {
    read_exceptions_attribute(&ptr->info.exceptions, fp);
  } else if (strcmp("LineNumberTable", str) == 0) {
    read_linenumbertable_attribute(&ptr->info.linenumbertable, fp);
  } else {
    printf("Warning: unknown attribute type %s\n", str);
  }
}

void read_code_attribute(Code_attribute *ptr, FILE *fp, cp_info *cp) {
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
    read_attribute_info(fp, &ptr->attributes[i], cp);
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

void read_linenumbertable_attribute(LineNumberTable_attribute *ptr, FILE *fp) {
  assert(ptr);
  assert(fp);

  ptr->line_number_table_length = read_u2(fp);
  ptr->line_number_table = calloc(2*sizeof(uint16_t), ptr->line_number_table_length);

  #ifdef DEBUG
  printf("\t\tLineNumberTable length: 0x%04x\n", ptr->line_number_table_length);
  #endif

  if (ptr->line_number_table_length > 0) {
    assert(ptr->line_number_table);
  }

  for (uint16_t i = 0; i < ptr->line_number_table_length; i++) {
    ptr->line_number_table[i].start_pc = read_u2(fp);
    ptr->line_number_table[i].line_number = read_u2(fp);
    #ifdef DEBUG
    printf("\t\t\t0x%04x\t0x%04x\n", ptr->line_number_table[i].start_pc,
	   ptr->line_number_table[i].line_number);
    #endif
  }
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

void deinit_class_file(classfile *cf) {

  deinit_fields(cf->fields, cf->fields_count, cf->constant_pool);
  free(cf->fields);

  deinit_methods(cf->methods, cf->methods_count, cf->constant_pool);
  free(cf->methods);

  deinit_attributes(cf->attributes, cf->attributes_count, cf->constant_pool);
  free(cf->attributes);

  deinit_constant_pool(cf->constant_pool, cf->cpsize);
  free(cf->constant_pool);

  // TODO free interfaces
}

void deinit_constant_pool(cp_info cp[], uint16_t cpsize) {
  for (int i = 0; i < cpsize; i++) {
    deinit_cp_entry(&cp[i]);
  }
}

void deinit_cp_entry(cp_info *ptr) {
  assert(ptr);
  if (ptr->tag == CONSTANT_Utf8) {
    CONSTANT_Utf8_info *info = &ptr->info.utf8_info;
    free(info->bytes);
  }
}


void deinit_fields(field_info fields[], uint16_t fields_count, cp_info *cp) {
  for (int i = 0; i < fields_count; i++) {
    deinit_field_entry(&fields[i], cp);
  }
}
void deinit_field_entry(field_info *ptr, cp_info *cp) {
  for (int i = 0; i < ptr->attributes_count; i++) {
    deinit_attribute_info(&ptr->attributes[i], cp);
  }
  free(ptr->attributes);
}

void deinit_methods(method_info methods[], uint16_t method_count, cp_info *cp) {
  for (int i = 0; i < method_count; i++) {
    deinit_method_entry(&methods[i], cp);
  }
}

void deinit_method_entry(method_info *ptr, cp_info *cp) {
  deinit_field_entry((field_info *) ptr, cp);
}

void deinit_attributes(attribute_info attributes[], uint16_t attributes_count, cp_info *cp) {
  for (int i = 0; i < attributes_count; i++) {
    deinit_attribute_info(&attributes[i], cp);
  }
}

void deinit_attribute_info(attribute_info *ptr, cp_info *cp) {
  if (!ptr) return;
  assert(cp);

  char *str = get_cp_string(cp, ptr->attribute_name_index - 1);

  if (strcmp("Code", str) == 0) {
    deinit_code_attribute(&ptr->info.code, cp);
  } else if (strcmp("Exceptions", str) == 0) {
    deinit_exceptions_attribute(&ptr->info.exceptions);
  } else if (strcmp("LineNumberTable", str) == 0) {
    deinit_linenumbertable_attribute(&ptr->info.linenumbertable);
  }
}

void deinit_code_attribute(Code_attribute *ptr, cp_info *cp) {
  free(ptr->code);
  free(ptr->exception_table);
  deinit_attributes(ptr->attributes, ptr->attributes_count, cp);
  free(ptr->attributes);
}

void deinit_exceptions_attribute(Exceptions_attribute *ptr) {
  free(ptr->exception_index_table);
}

void deinit_linenumbertable_attribute(LineNumberTable_attribute *ptr) {
  free(ptr->line_number_table);
}
