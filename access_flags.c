#include "access_flags.h"

ac_node* AC_FLAGS_CLASS;
ac_node* AC_FLAGS_FIELD;
ac_node* AC_FLAGS_METHOD;
ac_node* AC_FLAGS_INNER_CLASSES;

char** get_flags_name(ac_node* ac_list, uint32_t code) {
    char** flags_name = malloc(sizeof(char*) * MAX_FLAGS);
    int i = 0;

    while (ac_list){
        if ((ac_list->flag_code & code) == ac_list->flag_code) {
            flags_name[i] = ac_list->flag_name;
            i += 1;
        }

        ac_list = ac_list->next;
    }

    return flags_name;
}

void add_flag(ac_node** ac_list, uint32_t code, char* name) {
    ac_node* new_node = malloc(sizeof(ac_node));

    new_node->flag_name = name;

    new_node->flag_code = code;
    new_node->next = NULL;

    ac_node* ptr_crawler = *ac_list;

    if (!ptr_crawler) {
        *ac_list = new_node;
    } else {

        while (ptr_crawler) {
            if (!ptr_crawler->next) {
                ptr_crawler->next = new_node;
                break;
            }
            ptr_crawler = ptr_crawler->next;
        }
    }

    return;
}

void print_flags(ac_node* ac_list, uint32_t code){
    while (ac_list){
        if ((ac_list->flag_code & code) == ac_list->flag_code) {
            printf("%s ", ac_list->flag_name);
        }

        ac_list = ac_list->next;
    }

    printf("\n");
}

void populate_ac_flags_class() {
    add_flag(&AC_FLAGS_CLASS, 0x0001, "ACC_PUBLIC");
    add_flag(&AC_FLAGS_CLASS, 0x0010, "ACC_FINAL");
    add_flag(&AC_FLAGS_CLASS, 0x0020, "ACC_SUPER");
    add_flag(&AC_FLAGS_CLASS, 0x0200, "ACC_INTERFACE");
    add_flag(&AC_FLAGS_CLASS, 0x0400, "ACC_ABSTRACT");
    add_flag(&AC_FLAGS_CLASS, 0x1000, "ACC_SYNTHETIC");
    add_flag(&AC_FLAGS_CLASS, 0x2000, "ACC_ANNOTATION");
    add_flag(&AC_FLAGS_CLASS, 0x4000, "ACC_ENUM");
}

void populate_ac_flags_method() {
    add_flag(&AC_FLAGS_METHOD, 0x0001, "ACC_PUBLIC");
    add_flag(&AC_FLAGS_METHOD, 0x0002, "ACC_PRIVATE");
    add_flag(&AC_FLAGS_METHOD, 0x0004, "ACC_PROTECTED");
    add_flag(&AC_FLAGS_METHOD, 0x0008, "ACC_STATIC");
    add_flag(&AC_FLAGS_METHOD, 0x0010, "ACC_FINAL");
    add_flag(&AC_FLAGS_METHOD, 0x0040, "ACC_VOLATILE");
    add_flag(&AC_FLAGS_METHOD, 0x0080, "ACC_TRANSIENT");
    add_flag(&AC_FLAGS_METHOD, 0x1000, "ACC_SYNTHETIC");
    add_flag(&AC_FLAGS_METHOD, 0x4000, "ACC_ENUM");
}

void populate_ac_flags_inner_classes() {
    add_flag(&AC_FLAGS_INNER_CLASSES, 0x0000, "[]");
    add_flag(&AC_FLAGS_INNER_CLASSES, 0x0001, "ACC_PUBLIC");
    add_flag(&AC_FLAGS_INNER_CLASSES, 0x0002, "ACC_PRIVATE");
    add_flag(&AC_FLAGS_INNER_CLASSES, 0x0004, "ACC_PROTECTED");
    add_flag(&AC_FLAGS_INNER_CLASSES, 0x0008, "ACC_STATIC");
    add_flag(&AC_FLAGS_INNER_CLASSES, 0x0010, "ACC_FINAL");
    add_flag(&AC_FLAGS_INNER_CLASSES, 0x0200, "ACC_INTERFACE");
    add_flag(&AC_FLAGS_INNER_CLASSES, 0x0400, "ACC_ABSTRACT");
    add_flag(&AC_FLAGS_INNER_CLASSES, 0x1000, "ACC_SYNTHETIC");
    add_flag(&AC_FLAGS_INNER_CLASSES, 0x2000, "ACC_ANNOTATION");
    add_flag(&AC_FLAGS_INNER_CLASSES, 0x4000, "ACC_ENUM");
}

void deinit_ac_flags() {
    ac_node* ptr_list[4] = {AC_FLAGS_CLASS, AC_FLAGS_FIELD, AC_FLAGS_METHOD, AC_FLAGS_INNER_CLASSES};
    ac_node* ptr_crawler, *ptr_crawler_next;

    int i;

    for(i = 0; i < 4; i += 1){
        ptr_crawler = ptr_list[i];

        while (ptr_crawler) {
            ptr_crawler_next = ptr_crawler->next;
            free(ptr_crawler);
            ptr_crawler = ptr_crawler_next;
        }
    }

}
