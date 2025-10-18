#ifndef ASSEMBLER_H_
#define ASSEMBLER_H_
#include <stdio.h>

struct str_label
{
    int num = -1;
    char name[15] = {};
};

struct labels
{
    struct str_label str_labels[10] = {};
    int num_labels[10] = {};
    int current_ptr = -1;
};


int compare_func(char* command);

int* signature_maker(int* code);

size_t code_maker(int* buffer_out, char** mas_str, size_t len, struct labels* data_labels);

int check_byte_code(int* mass, size_t len);

int proccesing_nonarg(int* buffer_out, char** mas_str, int* pc_code, int* str_num, struct labels* data_labels);

int proccesing_witharg(int* buffer_out, char** mas_str, int* pc_code, int* str_num, struct labels* data_labels);

#endif