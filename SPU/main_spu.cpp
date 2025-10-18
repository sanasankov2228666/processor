#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "../stack/headers/stack1.h"
#include "../stack/headers/checker.h"
#include "enum.h"
#include "spu.h"
#include "fileopen.h"
#include "str_func.h"

typedef int type;

int main(void)
{
    struct stk data1 = {};
    struct spu data_spu = {};
    
    stack_creator(&data1, 10);
    data_spu.stack = data1.stack;

    slicer();

    //!открытие файла с байткодом
    FILE* stream = file_opener("SPU/translate_cmd.asm", "rb", __FUNCTION__, __FILE__, __LINE__);
    if (stream == NULL) return 1;

    //!открытие файла записи ошибок
    FILE* stream_error = file_opener("SPU/spu_errors.txt", "wb", __FUNCTION__, __FILE__, __LINE__);
    if (stream_error == NULL) return 1;

    //!подсчёт количества комманд
    size_t len = size_file(stream) / sizeof(int);

    //!создание массива с байткодом
    data_spu.code = mass_cmd_maker(stream, len);

    //!проверка сигнатуры
    if( !(signature_version_check(data_spu.code)))
    {
        printf("signature or version is diffrient\n");
        spu_deleter(&data1, &data_spu, stream_error, stream);
        return 1;
    }

    //!запуск процессора
    printf("SPU launching\n");

    struct stk data_func = {}; 
    stack_creator(&data_func, 10);
    while (spu_launcher(&data1, &data_spu, &data_func, stream_error) != HLT);

    //!отладка стека
    printf("\nin program\n");
    for (size_t i = 0; i < data1.capacity + 2; i ++)
    {
        printf("%d\n", data1.stack[i]);
    }
    
    printf("\nuser see\n");
    while (data1.size > 0)
    {
        printf("%d\n", stack_pop(&data1));
    }

    spu_deleter(&data1, &data_spu, stream_error, stream);
    stack_deleter(&data_func);

    return 0;
}
