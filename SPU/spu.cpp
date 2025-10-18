#include <stdio.h>
#include <math.h>
#include "../stack/headers/stack1.h"
#include "../stack/headers/checker.h"
#include "enum.h"
#include "str_func.h"
#include "spu.h"
#include "fileopen.h"

//!номер версии процессора
#define VERSION '1'

//--------------------------------------------------------ПРОЦЕССОР-------------------------------------------------------------------------

//!процессор
int spu_launcher(struct stk* data, struct spu* data_spu, struct stk* data_func, FILE* stream_error)
{
    int val = 0;
    int swch = 0;
    
    swch = data_spu->code[data_spu->counter];
    printf("command = %d\n", swch);

    switch (swch)
    {
    case PUSH:
        data_spu->counter++;
        stack_push(data, data_spu->code[data_spu->counter]);
        printf("pushed %d\n", data_spu->code[data_spu->counter]);

        data_spu->counter++;
        //getchar();
        break;

    case ADD:
        if (check_size(data->size, stream_error)) break;

        val = (stack_pop(data) + stack_pop(data));
        stack_push(data, val);
        printf("added %d\n", val);
        
        data_spu->counter++;
        //getchar();
        break;

    case SUB:
        if (check_size(data->size, stream_error)) break;

        val = (stack_pop(data) - stack_pop(data));
        stack_push(data, val);
        printf("subbed %d\n", val);

        data_spu->counter++;
        //getchar();
        break;

    case DIV:
        if (check_size(data->size, stream_error)) break;

        if (data->stack[data->size] == 0)
        {
            fprintf(stream_error, "division by zero \n");
            break;
        }

        val = (stack_pop(data) / stack_pop(data));
        stack_push(data, val);
        printf("dived %d\n", val);

        data_spu->counter++;
        //getchar();
        break;

    case MULT:
        if (check_size(data->size, stream_error)) break;

        val = (stack_pop(data) * stack_pop(data));
        stack_push(data, val);
        printf("multiplayed %d\n", val);

        data_spu->counter++;
        //getchar();
        break;

    case SQvRT:
        if (data->size < 1)
        {
            fprintf(stream_error, "stack dosent have paramets\n");
            break;
        }

        val = (int)(sqrt(stack_pop(data)));
        stack_push(data, val);
        printf("the square root is extracted %d\n", val);

        data_spu->counter++;
        //getchar();
        break;

    case IN:
        printf("push parametr:\n");
        scanf("%d", &val);
        stack_push(data, val);
        printf("pushed %d\n", val);

        data_spu->counter++;
        //getchar();

        break;

    case OUT:
        if (data->size < 1)
        {
            fprintf(stream_error, "stack dosent have paramets\n");
            break;
        }
        
        printf("stack out = %d\n", stack_pop(data));

        data_spu->counter++;
        //getchar();
        break;
    
    case PUSHREG:
        
        data_spu->counter++;

        if (register_protection(data_spu->code[data_spu->counter], stream_error)) break;

        stack_push(data, data_spu->reg[data_spu->code[data_spu->counter]]);
        printf("pushed from reg %c (value: %d)\n", 
        data_spu->code[data_spu->counter] + 65, data_spu->reg[data_spu->code[data_spu->counter]]);
        
        data_spu->counter++;
        //getchar();
        break;

    case POPREG:
        if (data->size < 1)
        {
            fprintf(stream_error, "stack doesent have parametrs\n");
            break;
        }

        data_spu->counter++;

        if (register_protection(data_spu->code[data_spu->counter], stream_error)) break;

        data_spu->reg[data_spu->code[data_spu->counter]] = stack_pop(data);
        printf("reg %c poped %d\n", data_spu->code[data_spu->counter] + 65, data_spu->reg[data_spu->code[data_spu->counter]]);

        data_spu->counter++;
        //getchar();
        break;
    
    case JUMP:
        data_spu->counter++;

        data_spu->counter = (size_t)data_spu->code[data_spu->counter];
        printf("jumped on %zu command", data_spu->counter);

        //getchar();
        break;
    
    case JB:
        data_spu->counter++;

        if (stack_pop(data) > stack_pop(data))
        {
            data_spu->counter = (size_t)data_spu->code[data_spu->counter];
            printf("jumped on %zu command", data_spu->counter);
        }

        else data_spu->counter++;

        //getchar();
        break;

    case JBE:
        data_spu->counter++;

        if (stack_pop(data) >= stack_pop(data))
        {
            data_spu->counter = (size_t)data_spu->code[data_spu->counter];
            printf("jumped on %zu command", data_spu->counter);
        }

        else data_spu->counter++;

        //getchar();
        break;

    case JA:
        data_spu->counter++;

        if (stack_pop(data) <= stack_pop(data))
        {
            data_spu->counter = (size_t)data_spu->code[data_spu->counter];
            printf("jumped on %zu command", data_spu->counter);
        }

        else data_spu->counter++;

        //getchar();
        break;

    case JAE:
        data_spu->counter++;

        if (stack_pop(data) >= stack_pop(data))
        {
            data_spu->counter = (size_t)data_spu->code[data_spu->counter];
            printf("jumped on %zu command", data_spu->counter);
        }

        else data_spu->counter++;

        //getchar();
        break;

    case JE:
        data_spu->counter++;

        if (stack_pop(data) == stack_pop(data))
        {
            data_spu->counter = (size_t)data_spu->code[data_spu->counter];
            printf("jumped on %zu command", data_spu->counter);
        }

        else data_spu->counter++;

        //getchar();
        break;

    case JNE:
        data_spu->counter++;

        if (stack_pop(data) != stack_pop(data))
        {
            data_spu->counter = (size_t)data_spu->code[data_spu->counter];
            printf("jumped on %zu command", data_spu->counter);
        }

        else data_spu->counter++;

        //getchar();
        break;
    
    case CALL:
        data_spu->counter++;
        stack_push(data_func, (int) (data_spu->counter + 1));

        data_spu->counter = (size_t) data_spu->code[data_spu->counter];
        printf("call on %zu command", data_spu->counter);

        //getchar();
        break;

    case RET:

        data_spu->counter = (size_t) stack_pop(data_func);
        printf("ret on %zu command", data_spu->counter);

        //getchar();
        break;

    case HLT:
        swch = HLT;

        //getchar();
        break;

    default:
        fprintf(stream_error, "unrecognaized command, (command %zu)\n", data_spu->counter);
        swch = HLT;
        break;
    }
    
    printf("\n");

    return swch;
}

//-------------------------------------------------------------------------------------------------------------------------------------------


//!функция читающая байт код из файла в массив
int* mass_cmd_maker(FILE* stream, size_t len)
{   
    int* commands = (int*) calloc (len, sizeof(int));
    if (commands == NULL)
    {
        printf("calloc error, %s %s:%d", __FILE__, __func__, __LINE__);
        return NULL;
    }

    fread(commands, sizeof(int), len, stream);

    return commands;
}

//!проверка размера стека
int check_size(size_t size, FILE* stream_error)
{
    if (size < 2)
    {
        fprintf(stream_error, "stack have %zu parametr\n", size);
        return 1;
    }

    return 0;
}

//!проверка сигнатуры
int signature_version_check(int* code)
{
    ((char*)code)[1] = 'K';
    ((char*)code)[2] = 'K'; 
    ((char*)code)[3] = VERSION;

    return ( ((char*)code)[1] == 'K' && ((char*)code)[2] == 'K' && ((char*)code)[3] == '1');;
}

//!проверка на вызов несуществующих регистров
int register_protection(int number_reg, FILE* stream_error)
{
    if (number_reg > 7)
    {
        fprintf(stream_error, "register %c doesent exist\n", number_reg + 65);
        return 1;
    }

    return 0;
}

//!функция чистки процессора
void spu_deleter(struct stk* data, struct spu* data_spu, FILE* stream_error, FILE* stream)
{
    fclose(stream_error);
    fclose(stream);
    free(data_spu->code);
    stack_deleter(data);

    printf("spu deleted\n");
}

// int spu_dump(struct stk data, struct spu data_spu, struct stk data_func, const char* func, const char* file, int LINE)
// {
//     printf("-------------------------STACK-INFO---------------------------\n");
//     stack_dump(data, func, file, LINE);
//     printf("--------------------------------------------------------------\n\n");
  
//     //--------------------------------------------------------------------------

//     printf("-------------------------SPU-INFO----------------------------\n\n");


//     printf("___________________________\n");
//     printf("|        code_buffer      |\n");
//     printf("___________________________\n");
//     for (size_t i = 1; i < 200; i++)
//     {   
//         printf("||%5zu: command | %5d||\n", i, data_spu.code[i]);
//     }
//     printf("___________________________\n");

//     //printf("")

//     return 0;
// }