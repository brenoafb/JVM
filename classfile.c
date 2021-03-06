#include "classfile.h"

void read_class_file(classfile *cf, FILE *fp) {
  assert(cf);
  assert(fp);

  cf->magic = read_u4(fp);
  if (cf->magic != 0xcafebabe) {
    printf("Warning: Not a valid class file (no 0xcafebabe)\n");
  }
  assert(cf->magic == 0xcafebabe);

  /* minor/major version */
  cf->minor_version = read_u2(fp);
  cf->major_version = read_u2(fp);

#ifdef DEBUG
  printf("Magic: 0x%08x\n", cf->magic);
  printf("Minor: %d (0x%04x)\n", cf->minor_version, cf->minor_version);
  printf("Major: %d (0x%04x)\n", cf->major_version, cf->major_version);
#endif

  /* constant-pool */

  cf->cpsize = read_u2(fp);
  cf->constant_pool = calloc(sizeof(cp_info), cf->cpsize);
#ifdef DEBUG
  printf("cpsize: %d (0x%04x)\n", cf->cpsize, cf->cpsize);
#endif
  read_constant_pool(fp, cf->constant_pool, cf->cpsize);

  /* access flags, this/super class */
  cf->access_flags = read_u2(fp);
  cf->this_class = read_u2(fp);
  cf->super_class = read_u2(fp);

#ifdef DEBUG
  printf("Access flags: 0x%04x\n", cf->access_flags);
  printf("This class: 0x%04x\n", cf->this_class);
  printf("Super class: 0x%04x\n", cf->super_class);
#endif

  /* interfaces */
  cf->interfaces_count = read_u2(fp);
#ifdef DEBUG
  printf("Interfaces count: %d (0x%04x)\n", cf->interfaces_count, cf->interfaces_count);
#endif

  cf->interfaces = calloc(sizeof(CONSTANT_Class_info), cf->interfaces_count);
  if (cf->interfaces_count > 0) {
    read_interfaces(fp, cf->interfaces, cf->interfaces_count);
  }

  /* fields */
  cf->fields_count = read_u2(fp);

#ifdef DEBUG
  printf("Fields count: %d (0x%04x)\n", cf->fields_count, cf->fields_count);
#endif

  cf->fields = calloc(sizeof(field_info), cf->fields_count);
  if (cf->fields_count > 0) {
    read_fields(fp, cf->fields, cf->fields_count, cf->constant_pool);
  }

  /* methods */
  cf->methods_count = read_u2(fp);
#ifdef DEBUG
  printf("Methods count: %d (0x%04x)\n", cf->methods_count, cf->methods_count);
#endif

  cf->methods = calloc(sizeof(method_info), cf->methods_count);
  if (cf->methods_count > 0) {
    read_methods(fp, cf->methods, cf->methods_count, cf->constant_pool);
  }

  /* attributes */
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
  int i;
  for (i = 1; i < cpsize; i++) {
    cp_info *ptr = &cp[i];
    ptr->tag = read_u1(fp);
#ifdef DEBUG
    printf("\t%d\t0x%02x\n", i, ptr->tag);
#endif
    read_constant_pool_entry(fp, ptr);
    if (ptr->tag == CONSTANT_Double ||
	ptr->tag == CONSTANT_Long) {
      /* Double/Longs occupy two slots in the constant pool */
      i++;
    }
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

void read_interfaces(FILE *fp, CONSTANT_Class_info interfaces[], uint16_t interfaces_count) {
  int i;
  for (i = 0; i < interfaces_count; i++) {
    CONSTANT_Class_info *ptr = &interfaces[i];
    ptr->name_index = read_u2(fp);
#ifdef DEBUG
    printf("\tIndex:\t0x%04x\n", ptr->name_index);
#endif
  }
}

void read_fields(FILE *fp, field_info fields[], uint16_t fields_count, cp_info *cp) {
  int i;
  for (i = 0; i < fields_count; i++) {
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
  int i;
  for (i = 0; i < methods_count; i++) {
    method_info *ptr = &methods[i];
    read_method_entry(fp, ptr, cp);
  }
}

void read_method_entry(FILE *fp, method_info *method, cp_info *cp) {
  read_field_entry(fp, (field_info *) method, cp);
}


void read_attributes(FILE *fp, attribute_info attributes[], uint16_t attributes_count, cp_info *cp) {
  int i;
  for (i = 0; i < attributes_count; i++) {
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


  char *str = get_cp_string(cp, ptr->attribute_name_index);

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
    fseek(fp, ptr->attribute_length, SEEK_CUR);
  } else if (strcmp("LineNumberTable", str) == 0) {
    read_linenumbertable_attribute(&ptr->info.linenumbertable, fp);
  } else if (strcmp("SourceFile", str) == 0) {
    read_sourcefile_attribute(&ptr->info.sourcefile, fp);
    assert(cp[ptr->info.sourcefile.index].tag == CONSTANT_Utf8);
  } else if (strcmp("InnerClasses", str) == 0) {
    read_innerclasses_attribute(&ptr->info.innerclasses, fp);
  } else if (strcmp("Synthetic", str) == 0) {
    read_synthetic_attribute(ptr, fp);
  } else if (strcmp("StackMapTable", str) == 0){
    /*fseek(fp, ptr->attribute_length, SEEK_CUR);*/
    read_stackmaptable_attribute(&ptr->info.stackmaptable, fp);
    fseek(fp, ptr->attribute_length - 2, SEEK_CUR); /*WARN Talvez o bug esteja aqui*/
  } else {
    printf("Warning: unknown attribute type %s\n", str);
  }
}

void read_code_attribute(Code_attribute *ptr, FILE *fp, cp_info *cp) {
  assert(fp);
  assert(ptr);
  assert(cp);

  uint32_t i;

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

  for (i = 0; i < ptr->code_length; i++) {
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
  printf("\t\tException count: %"PRIu16"\n", ptr->exception_table_length);
#endif

#ifdef DEBUG

  if (ptr->exception_table_length > 0) {
    printf("\t\tException table:\n");
    printf("\t\t\tfrom\tto\ttarget\ttype\n");
  }


#endif
  for (i = 0;i < ptr->exception_table_length;i++) {
    ptr->exception_table[i].start_pc = read_u2(fp);
    ptr->exception_table[i].end_pc = read_u2(fp);
    ptr->exception_table[i].handler_pc = read_u2(fp);
    ptr->exception_table[i].catch_type = read_u2(fp);

    uint16_t from = ptr->exception_table[i].start_pc;
    uint16_t to = ptr->exception_table[i].end_pc;
    uint16_t handler = ptr->exception_table[i].handler_pc;
    uint16_t type = ptr->exception_table[i].catch_type;

    char* type_str = "Class";

#ifdef DEBUG
    printf("\t\t\t%"PRIu16"\t%"PRIu16"\t%"PRIu16"\t%s\n", from, to, handler, type_str);
#endif

  }

  ptr->attributes_count = read_u2(fp);
  ptr->attributes = calloc(sizeof(attribute_info), ptr->attributes_count);

#ifdef DEBUG
  printf("\t\tAttributes count: %"PRIu16"\n", ptr->attributes_count);
#endif

  if (ptr->attributes_count != 0) {
    assert(ptr->attributes);
  }

  for (i = 0; i < ptr->attributes_count; i++) {
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

  uint16_t i;
  for (i = 0; i < ptr->number_of_exceptions; i++) {
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

  uint16_t i;
  for (i = 0; i < ptr->line_number_table_length; i++) {
    ptr->line_number_table[i].start_pc = read_u2(fp);
    ptr->line_number_table[i].line_number = read_u2(fp);
#ifdef DEBUG
    printf("\t\t\t0x%04x\t0x%04x\n", ptr->line_number_table[i].start_pc,
	   ptr->line_number_table[i].line_number);
#endif
  }
}

void read_synthetic_attribute(attribute_info *ptr, FILE *fp){
  assert(ptr);
  assert(fp);

  assert(!ptr->attribute_length);
}

void read_sourcefile_attribute(SourceFile_attribute *ptr, FILE *fp) {
  assert(ptr);
  assert(fp);

  ptr->index = read_u2(fp);
}

void read_innerclasses_attribute(InnerClasses_attribute *ptr, FILE *fp) {
  assert(ptr);
  assert(fp);

  ptr->number_of_classes = read_u2(fp);
  ptr->classes = calloc(4*sizeof(uint16_t), ptr->number_of_classes);

  #ifdef DEBUG
  printf("\t\tInnerClasses Number of classes: 0x%04x\n", ptr->number_of_classes);
  #endif

  uint16_t i;
  for (i = 0; i < ptr->number_of_classes; i++) {
    ptr->classes[i].inner_class_info_index = read_u2(fp);
    ptr->classes[i].outer_class_info_index = read_u2(fp);
    ptr->classes[i].inner_name_index = read_u2(fp);
    ptr->classes[i].inner_class_access_flags = read_u2(fp);

  #ifdef DEBUG
    printf("\t\t\t0x%04x\t0x%04x\t0x%04x\t0x%04x\n", ptr->classes[i].inner_class_info_index,
     ptr->classes[i].outer_class_info_index,
     ptr->classes[i].inner_name_index,
     ptr->classes[i].inner_class_access_flags);
  #endif
  }
}

void read_stackmaptable_attribute(StackMapTable_attribute *ptr, FILE *fp) {
  assert(ptr);
  assert(fp);

  ptr->n_entries = read_u2(fp);

 }

char *get_class_name(classfile *cf) {
  uint32_t index = cf->constant_pool[cf->this_class].info.class_info.name_index;
  return get_cp_string(cf->constant_pool, index);
}

char *get_super_name(classfile *cf) {
  uint32_t index = cf->constant_pool[cf->super_class].info.class_info.name_index;
  return get_cp_string(cf->constant_pool, index);
}

char *get_cp_string(cp_info *cp, uint16_t index) {
  assert(cp);

  cp_info *entry = &cp[index];
  assert(entry->tag == CONSTANT_Utf8);

  return (char *) entry->info.utf8_info.bytes;
}

char *get_class_name_string(cp_info *cp, uint16_t class_index) {
  assert(cp);

  cp_info *entry = &cp[class_index];
  assert(entry->tag == CONSTANT_Class);

  return get_cp_string(cp, entry->info.methodref_info.class_index);
}

char *get_name_and_type_string(cp_info *cp, uint16_t index, uint8_t choice) {
  assert(cp);

  cp_info *entry = &cp[index];
  assert(entry->tag == CONSTANT_NameAndType);

  if (choice)
    return get_cp_string(cp, entry->info.nameandtype_info.name_index);
  else
    return get_cp_string(cp, entry->info.nameandtype_info.descriptor_index);
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

void print_class_file_detail(classfile *cf) {
  cp_info *cp = cf->constant_pool;
  int class_name_index = cp[cf->this_class].info.class_info.name_index;

  printf("class %s\n", get_cp_string(cp, class_name_index));
  printf("\tminor version: %d\n", cf->minor_version);
  printf("\tmajor version: %d\n", cf->major_version);
  print_java_version(cf->major_version, cf->minor_version);

  populate_ac_flags_class();

  printf("\tflags: ");
  print_flags(AC_FLAGS_CLASS, cf->access_flags);

  printf("Constant pool:\n");
  print_cp_detail(cf);

  print_interfaces_detail(cf);

  print_fields_detail(cf);

  print_methods_detail(cf);

  int i;
  for (i = 0; i < cf->attributes_count; i++) {
    print_attributes_detail(&cf->attributes[i], cp);
  }
}

void print_cp_detail(classfile *cf) {
  int i;
  for (i = 1; i < cf->cpsize; i++) {
    printf("\t#%d\t= ", i);
    switch(cf->constant_pool[i].tag) {
    case CONSTANT_Utf8                 :
      printf("Utf8:\t");
      char *str = get_cp_string(cf->constant_pool, i);
      printf("%s\n", str);
      break;
    case CONSTANT_Integer              :
      printf("Integer\t");
      uint32_t x = cf->constant_pool[i].info.integer_info.bytes;
      printf("%d\n", x);
      break;
    case CONSTANT_Float                :
      printf("Float\t");
      uint32_t hi = cf->constant_pool[i].info.float_info.bytes;
      float f;

      memcpy(&f, &hi, sizeof(float));

      printf("%f\n", f);
      break;
    case CONSTANT_Long                 :
      printf("Long\t");
      hi = cf->constant_pool[i].info.long_info.high_bytes;
      uint64_t lo = cf->constant_pool[i].info.long_info.low_bytes;

      uint64_t lg = ((uint64_t) hi << 32) | lo;

      printf("%ld\n", lg);
      i++;
      break;
    case CONSTANT_Double               :
      printf("Double\t");
      hi = cf->constant_pool[i].info.double_info.high_bytes;
      lo = cf->constant_pool[i].info.double_info.low_bytes;

      uint64_t conc = (((uint64_t) hi) << 32) + ((uint64_t) lo);
      double db = *((double *) (&conc));
      printf("%lf\n", db);
      i++;
      break;
    case CONSTANT_Class                :
      printf("Class\t");
      uint16_t name_index = cf->constant_pool[i].info.class_info.name_index;
      printf("%s (#%d)\n", get_cp_string(cf->constant_pool, name_index), name_index);
      break;
    case CONSTANT_String               :
      printf("String\t");
      uint16_t string_index = cf->constant_pool[i].info.string_info.string_index;
      printf("%s (#%d)\n", get_cp_string(cf->constant_pool, string_index), string_index);
      break;
    case CONSTANT_Fieldref             :
      printf("Fieldref\t");
      uint16_t class_index = cf->constant_pool[i].info.fieldref_info.class_index;
      uint16_t name_and_type_index = cf->constant_pool[i].info.fieldref_info.name_and_type_index;
      printf("%s.%s:%s (#%d.#%d)\n", get_class_name_string(cf->constant_pool, class_index),
	get_name_and_type_string(cf->constant_pool, name_and_type_index, 1),
	get_name_and_type_string(cf->constant_pool, name_and_type_index, 0),
	class_index, name_and_type_index);
      break;
    case CONSTANT_Methodref            :
      printf("Methodref\t");
      class_index = cf->constant_pool[i].info.methodref_info.class_index;
      name_and_type_index = cf->constant_pool[i].info.methodref_info.name_and_type_index;
      printf("%s.%s:%s (#%d.#%d)\n", get_class_name_string(cf->constant_pool, class_index),
	get_name_and_type_string(cf->constant_pool, name_and_type_index, 1),
	get_name_and_type_string(cf->constant_pool, name_and_type_index, 0), class_index, name_and_type_index);
      break;
    case CONSTANT_InterfaceMethodref   :
      printf("InterfaceMethodref\t");
      class_index = cf->constant_pool[i].info.methodref_info.class_index;
      name_and_type_index = cf->constant_pool[i].info.methodref_info.name_and_type_index;
      printf("%s.%s:%s (#%d.#%d)\n", get_class_name_string(cf->constant_pool, class_index),
	get_name_and_type_string(cf->constant_pool, name_and_type_index, 1),
	get_name_and_type_string(cf->constant_pool, name_and_type_index, 0),
	class_index, name_and_type_index);
      break;
    case CONSTANT_NameAndType          :
      printf("NameAndType\t");
      name_index = cf->constant_pool[i].info.nameandtype_info.name_index;
      uint16_t descriptor_index = cf->constant_pool[i].info.nameandtype_info.descriptor_index;
      printf("%s:%s (#%d:#%d)\n", get_cp_string(cf->constant_pool, name_index),
	get_cp_string(cf->constant_pool, descriptor_index), name_index, descriptor_index);
      break;
    }
  }
}

void print_interfaces_detail(classfile *cf) {
  cp_info *cp = cf->constant_pool;
  int i;
  uint16_t class, class_name;

  printf("Interfaces: (Count: %d) {\n", cf->interfaces_count);
  for (i = 0; i < cf->interfaces_count; i++) {
    CONSTANT_Class_info *in = &cf->interfaces[i];

    /* Indexes to constant pool elements*/
    class = in->name_index;
    class_name = cp[class].info.class_info.name_index;

    printf("     %d)\n", i);
    printf("\t Class: %s\t(#%d)\n", get_cp_string(cp, class_name), in->name_index);
  }
  printf("}\n");
}

void print_fields_detail(classfile *cf) {
  cp_info *cp = cf->constant_pool;
  int i, j;

  printf("Fields: (Count: %d) {\n", cf->fields_count);
  for (i = 0; i < cf->fields_count; i++) {
    field_info *fi = &cf->fields[i];
    printf("     %d)\n", i);
    printf("\t Name: %s\n", get_cp_string(cp, fi->name_index));
    printf("\t Descriptor: %s\n", get_cp_string(cp, fi->descriptor_index));

    printf("\t Flags: 0x%04x\n", fi->access_flags);

    printf("\t Attributes Count: %d\n", fi->attributes_count);
    for (j = 0; j < fi->attributes_count; j++) {
      print_attributes_detail(&fi->attributes[j], cp);
    }
  }
  printf("}\n");
}

void print_methods_detail(classfile *cf) {
  cp_info *cp = cf->constant_pool;
  int i, j;

  populate_ac_flags_method();

  printf("Methods: (Count: %d) {\n", cf->methods_count);
  for (i = 0; i < cf->methods_count; i++) {
    method_info *m = &cf->methods[i];
    printf("\t%s\n", get_cp_string(cp, m->name_index));
    printf("\t Descriptor: %s\n", get_cp_string(cp, m->descriptor_index));

    printf("\t Flags: ");
    print_flags(AC_FLAGS_METHOD, m->access_flags);

    for (j = 0; j < m->attributes_count; j++) {
      print_attributes_detail(&m->attributes[j], cp);
    }
    printf("\n");
  }
  printf("}\n");
}

void print_attributes_detail(attribute_info *ptr, cp_info *cp) {
  char *str = get_cp_string(cp, ptr->attribute_name_index);

  printf("\t\t%s:\t (Lenght: %d) %c", str, ptr->attribute_length, (!strcmp(str, "SourceFile") ? ' ' : '\n'));

  if (strcmp("Code", str) == 0) {
    print_code_attribute(&ptr->info.code, cp);
  } else if (strcmp("ConstantValue", str) == 0) {
  } else if (strcmp("Exceptions", str) == 0) {
    print_exception_attribute(&ptr->info.exceptions,cp, ptr->info.code.exception_table);
  } else if (strcmp("LineNumberTable", str) == 0) {
    print_linenumber_attribute(&ptr->info.linenumbertable);
  } else if (!strcmp("Synthetic", str)){
    print_synthetic_attribute(&ptr->info.synthetic, cp);
  } else if (strcmp("InnerClasses", str) == 0) {
    print_innerclasses_attribute(&ptr->info.innerclasses, cp);
  } else if (strcmp("StackMapTable", str) == 0) {
    print_stackmaptable_attribute(&ptr->info.stackmaptable);
  } else if (strcmp("SourceFile", str) == 0) {
    printf("\"%s\"\n\n", get_cp_string(cp, ptr->info.sourcefile.index));
  }
}

void print_stackmaptable_attribute(StackMapTable_attribute *ptr) {
  printf("\t\tNum of entries: %d\n", ptr->n_entries);
}

void print_synthetic_attribute(Synthetic_attribute *ptr, cp_info *cp) {

}

void print_exception_attribute(Exceptions_attribute *ptr, cp_info *cp, struct ExcTable* excT) {
  int i = 0;
  uint16_t index_table;

  printf("\t\tfrom\tto\ttarget\ttype\n");

  for (;i < ptr->number_of_exceptions;i++) {
    index_table = ptr->exception_index_table[i];

    uint16_t from = (excT + index_table)->start_pc;
    uint16_t to = (excT + index_table)->end_pc;
    uint16_t target = (excT + index_table)->handler_pc;
    uint16_t handler_index = (excT + index_table)->handler_pc;

    char* handler = get_cp_string(cp, handler_index);

    printf("%"PRIu16"\t%"PRIu16"\t%"PRIu16"\t%s\n", from, to, target, handler);
  }
}

void print_linenumber_attribute(LineNumberTable_attribute *ptr) {
  int i = 0;

  struct LineNTable* ptr_crawler = ptr->line_number_table;

  for (; i < ptr->line_number_table_length;i++) {
    printf("\t\t line %d: %d\n", ptr_crawler->line_number, ptr_crawler->start_pc);
    ptr_crawler += 1;
  }
}

void print_code_attribute(Code_attribute *ptr, cp_info *cp) {
    printf("\t\t stack=%d, locals=%d\n",
	   ptr->max_stack,
	   ptr->max_locals);
    uint32_t i, f, param1, param2, param3, param4;
    uint32_t result;
    for (i = 0; i < ptr->code_length; i++) {
      f = i;
      printf("\t\t %d\t%s", i, strings_opcodes[ptr->code[i]]);
      switch (opargs[ptr->code[i]]){
	case 1:
	  if ((ptr->code[i] >= OP_iload && ptr->code[i] >= OP_aload) || ptr->code[i] == OP_ret)
	    printf (" %d", ptr->code[++i]);
	  else if (ptr->code[i] == OP_ldc){
	    printf (" #%u ", ptr->code[++i]);
	    print_cp_element (cp, ptr->code[i]);
	  }
	  else
	    printf (" %d", ptr->code[++i]);
	  break;
	case 2:
	  param1 = ptr->code[++i];
	  param2 = ptr->code[++i];
	  if ((ptr->code[f] >= OP_ifeq && ptr->code[f] <= OP_jsr) ||
	    ptr->code[f] == OP_ifnull || ptr->code[f] == OP_ifnonnull ||
	    ptr->code[f] == OP_sipush) {

	    result = (param1 << 8) + param2;
	    printf (" %d", (int16_t) result);
	  }
	  else if (ptr->code[f] == OP_iinc){
	    printf (" %u by %d", param1, (int8_t) param2);
	  }
	  else if (ptr->code[f] == OP_ldc_w || ptr->code[f] == OP_ldc2_w ||
	    (ptr->code[f] >= OP_getstatic && ptr->code[f] <= OP_invokestatic) ||
	    ptr->code[f] == OP_new || ptr->code[f] == OP_anewarray ||
	    ptr->code[f] == OP_checkcast || ptr->code[f] == OP_instanceof) {

	    result = (param1 << 8) + param2;
	    printf (" #%u ", result);
	    print_cp_element (cp, (uint16_t) result);
	  }
	  else {
	    printf (" %d", param1);
	    printf (" %d", param2);
	  }
	  break;
	case 3:
	  param1 = ptr->code[++i];
	  param2 = ptr->code[++i];
	  param3 = ptr->code[++i];
	  if (ptr->code[f] == OP_multianewarray) {
	    result = (param1 << 8) + param2;
	    printf (" #%u", result);
	    print_cp_element (cp, (uint16_t) result);
	    printf (" Dimensão: %u", param3);
	  }
	  else {
	    printf (" %d", param1);
	    printf (" %d", param2);
	    printf (" %d", param3);
	  }
	  break;
	case 4:
	  param1 = ptr->code[++i];
	  param2 = ptr->code[++i];
	  param3 = ptr->code[++i];
	  param4 = ptr->code[++i];
	  if (ptr->code[f] == OP_goto_w || ptr->code[f] == OP_jsr_w) {
	    result = (param1 << 24) + (param2 << 16) + (param3 << 8) + param4;
	    printf (" %d", (int32_t) result);
	  }
	  else if (ptr->code[f] == OP_invokedynamic || ptr->code[f] == OP_invokeinterface){
	    result = (param1 << 8) + param2;
	    printf (" #%u", result);
	    print_cp_element (cp, (uint16_t) result);
	    printf (" %d", param3);
	    printf (" %d", param4);
	  }
	  else {
	    printf (" %d", param1);
	    printf (" %d", param2);
	    printf (" %d", param3);
	    printf (" %d", param4);
	  }
	  break;
	case 0:
	  break;
	default:
	  break;
      }

      printf("\t(0x%x)\n", ptr->code[f]);
    }

    for (i = 0; i < ptr->attributes_count; i++) {
      print_attributes_detail(ptr->attributes, cp);
    }
}

void print_innerclasses_attribute(InnerClasses_attribute *ptr,cp_info *cp) {
  uint16_t innerclass;
  uint16_t outerclass;
  uint16_t innername;
  uint16_t access_flags;
  uint16_t innerclass_name;
  uint16_t outerclass_name;

  char *s_innername, *s_outerclass_name;

  populate_ac_flags_inner_classes();

  printf("\t\t Number of classes: %d\n",
     ptr->number_of_classes);
    uint32_t i;
    for (i = 0; i < ptr->number_of_classes; i++) {
      /* Indexes to constant pool elements*/
      innerclass = ptr->classes[i].inner_class_info_index;
      outerclass = ptr->classes[i].outer_class_info_index;
      innername = ptr->classes[i].inner_name_index;
      access_flags = ptr->classes[i].inner_class_access_flags;
      innerclass_name = cp[innerclass].info.class_info.name_index;
      outerclass_name = cp[outerclass].info.class_info.name_index;

      s_outerclass_name = (outerclass_name ? get_cp_string(cp, outerclass_name) : "Invalid constant pool reference.");
      s_innername = (innername ? get_cp_string(cp, innername) : "Invalid constant pool reference.");

      printf("\n\t\t  %d) InnerClass- %s (#%d);\n\t\t     OuterClass- %s (#%d);\n\t\t     InnerName- %s (#%d);\n\t\t     AccessFlags- (0x%04x) ",
	     i, get_cp_string(cp, innerclass_name), innerclass,
	     s_outerclass_name, outerclass,
	     s_innername, innername, access_flags);
       print_flags(AC_FLAGS_CLASS, access_flags);
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

  deinit_interfaces(cf->interfaces);

  /* TODO free interfaces */
}

void deinit_constant_pool(cp_info cp[], uint16_t cpsize) {
  int i;
  for (i = 1; i < cpsize; i++) {
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

void deinit_interfaces(CONSTANT_Class_info *interfaces) {
  if (!interfaces) return;
  free(interfaces);
}

void deinit_fields(field_info fields[], uint16_t fields_count, cp_info *cp) {
  int i;
  for (i = 0; i < fields_count; i++) {
    deinit_field_entry(&fields[i], cp);
  }
}
void deinit_field_entry(field_info *ptr, cp_info *cp) {
  int i;
  for (i = 0; i < ptr->attributes_count; i++) {
    deinit_attribute_info(&ptr->attributes[i], cp);
  }
  free(ptr->attributes);
}

void deinit_methods(method_info methods[], uint16_t method_count, cp_info *cp) {
  int i;
  for (i = 0; i < method_count; i++) {
    deinit_method_entry(&methods[i], cp);
  }
}

void deinit_method_entry(method_info *ptr, cp_info *cp) {
  deinit_field_entry((field_info *) ptr, cp);
}

void deinit_attributes(attribute_info attributes[], uint16_t attributes_count, cp_info *cp) {
  int i;
  for (i = 0; i < attributes_count; i++) {
    deinit_attribute_info(&attributes[i], cp);
  }
}

void deinit_attribute_info(attribute_info *ptr, cp_info *cp) {
  if (!ptr) return;
  assert(cp);

  char *str = get_cp_string(cp, ptr->attribute_name_index);

  if (strcmp("Code", str) == 0) {
    deinit_code_attribute(&ptr->info.code, cp);
  } else if (strcmp("Exceptions", str) == 0) {
    deinit_exceptions_attribute(&ptr->info.exceptions);
  } else if (strcmp("LineNumberTable", str) == 0) {
    deinit_linenumbertable_attribute(&ptr->info.linenumbertable);
  } else if (strcmp("InnerClasses", str) == 0) {
    deinit_innerclasses_attribute(&ptr->info.innerclasses);
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

void deinit_innerclasses_attribute(InnerClasses_attribute *ptr) {
  free(ptr->classes);
}
void print_java_version (uint16_t major,  uint16_t minor) {
  char* version = calloc(sizeof(char), 5);
  char* major_version;
  switch (major){
    case 52:
      major_version = "J2SE 8";
    break;
    case 51:
      major_version = "J2SE 7";
    break;
    case 50:
      major_version = "J2SE 6.0";
    break;
    case 49:
      major_version = "J2SE 5.0";
    break;
    case 48:
      major_version = "JDK 1.4";
    break;
    case 47:
      major_version = "JDK 1.3";
    break;
    case 46:
      major_version = "JDK 1.2";
    break;
    case 45:
      major_version = "JDK 1.1";
    break;
    default:
      major_version = "0";
    break;
  }
  sprintf(version, "%s.%d", major_version, minor);
  printf("\t%s\n",version);
  free(version);
}

void print_cp_element (cp_info *cp, uint16_t i){
  switch(cp[i].tag) {
    case CONSTANT_Utf8                 :
      printf(" ");
      char *str = get_cp_string(cp, i);
      printf("%s", str);
      break;
    case CONSTANT_Integer              :
      printf(" ");
      uint32_t x = cp[i].info.integer_info.bytes;
      printf("%d", x);
      break;
    case CONSTANT_Float                :
      printf(" ");
      uint32_t hi = cp[i].info.float_info.bytes;
      float f;

      memcpy(&f, &hi, sizeof(float));

      printf("%f", f);
      break;
    case CONSTANT_Long                 :
      printf(" ");
      hi = cp[i].info.long_info.high_bytes;
      uint64_t lo = cp[i].info.long_info.low_bytes;

      uint64_t lg = ((uint64_t) hi << 32) | lo;

      printf("%ld", lg);
      i++;
      break;
    case CONSTANT_Double               :
      printf(" ");
      hi = cp[i].info.double_info.high_bytes;
      lo = cp[i].info.double_info.low_bytes;

      uint64_t conc = ((uint64_t) hi << 32) + lo;
      double db;

      memcpy(&db, &conc, sizeof(double));

      printf("%lf", db);
      i++;
      break;
    case CONSTANT_Class                :
      printf(" ");
      uint16_t name_index = cp[i].info.class_info.name_index;
      printf("%s", get_cp_string(cp, name_index));
      break;
    case CONSTANT_String               :
      printf(" ");
      uint16_t string_index = cp[i].info.string_info.string_index;
      printf("%s", get_cp_string(cp, string_index));
      break;
    case CONSTANT_Fieldref             :
      printf(" ");
      uint16_t class_index = cp[i].info.fieldref_info.class_index;
      uint16_t name_and_type_index = cp[i].info.fieldref_info.name_and_type_index;
      printf("%s.%s:%s", get_class_name_string(cp, class_index),
	get_name_and_type_string(cp, name_and_type_index, 1),
	get_name_and_type_string(cp, name_and_type_index, 0));
      break;
    case CONSTANT_Methodref            :
      printf(" ");
      class_index = cp[i].info.methodref_info.class_index;
      name_and_type_index = cp[i].info.methodref_info.name_and_type_index;
      printf("%s.%s:%s", get_class_name_string(cp, class_index),
	get_name_and_type_string(cp, name_and_type_index, 1),
	get_name_and_type_string(cp, name_and_type_index, 0));
      break;
    case CONSTANT_InterfaceMethodref   :
      printf(" ");
      class_index = cp[i].info.methodref_info.class_index;
      name_and_type_index = cp[i].info.methodref_info.name_and_type_index;
      printf("%s.%s:%s", get_class_name_string(cp, class_index),
	get_name_and_type_string(cp, name_and_type_index, 1),
	get_name_and_type_string(cp, name_and_type_index, 0));
      break;
    case CONSTANT_NameAndType          :
      printf(" ");
      name_index = cp[i].info.nameandtype_info.name_index;
      uint16_t descriptor_index = cp[i].info.nameandtype_info.descriptor_index;
      printf("%s:%s", get_cp_string(cp, name_index),
	get_cp_string(cp, descriptor_index));
      break;
    }
}
