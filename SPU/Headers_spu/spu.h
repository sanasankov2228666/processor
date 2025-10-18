#ifndef SPU_H_
#define SPU_H_

#include <stdio.h>

struct spu
{
    type* stack = NULL;
    int* code = NULL;
    size_t counter = 1;
    int reg [8] = {};
};

int check_size(size_t size, FILE* stream_error);

int spu_launcher(struct stk* data, struct spu* data_spu, struct stk* data_func, FILE* stream_error);

int* mass_cmd_maker(FILE* stream, size_t len);

int signature_version_check(int* code);

int register_protection(int number_reg, FILE* stream_error);

void spu_deleter(struct stk* data, struct spu* data_spu, FILE* stream_error, FILE* stream);

#endif