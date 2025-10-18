#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../../stack/headers/stack1.h"
#include "enum.h"
#include "str_func.h"
#include "fileopen.h"
#include "assembler.h"

//!версия ассемблера
#define VERSION 1

static struct commands
{
    const char* name;
    const int number;
    const int arg = 0;
} 


//!массив комманд
commands[NUMBER_COMMANDS] = 
{
    {"PUSH", PUSH, 1},       {"ADD", ADD, 0},
    {"SUB", SUB, 0},         {"DIV", DIV, 0},
    {"MULT", MULT, 0},       {"SQRT", SQvRT, 0},
    {"IN", IN, 0},           {"HLT", HLT, 0},
    {"OUT", OUT, 0},         {"PUSHREG", PUSHREG, 1},
    {"POPREG", POPREG, 1},   {"JUMP", JUMP, 1},
    {"JB", JB, 1},           {"JBE", JBE, 1},
    {"JA", JA, 1},           {"JAE", JAE, 1},
    {"JE", JE, 1},           {"JNE", JNE, 1},
    {"CALL", CALL, 1},       {"RET", RET, 0}
};


//!функция переводящая команды
int compare_func(char* command)
{
    int swch = 0;

    for (int i = 0; i < NUMBER_COMMANDS && swch == 0; i++ )
    {
        if (my_strcmp(command, commands[i].name) == 0) swch = commands[i].number;
    }
    
    return swch;
}

//---------------------------------------------СОЗДАНИЕ-БАЙТ-КОДА-----------------------------------------------------------------------------

//!функция для создания байткода
size_t code_maker(int* buffer_out, char** mas_str, size_t len, struct labels* data_labels)
{
    int pc_code = 1;

    for (int str_num = 0; (pc_code < (int) len && str_num < (int) len) ; pc_code++, str_num++)
    {
        
        buffer_out[pc_code] = compare_func(mas_str[str_num]);
        
        if (buffer_out[pc_code] == 0)
        {
            proccesing_nonarg(buffer_out, mas_str, &pc_code, &str_num, data_labels);
        }
        
        else if (commands[buffer_out[pc_code] - 1].arg == 1)
        {   
            pc_code++;
            str_num++;

            proccesing_witharg(buffer_out, mas_str, &pc_code, &str_num, data_labels);
        }
    }

    return (size_t) pc_code;
}

//!функция обработки комманды без аргумента
int proccesing_nonarg(int* buffer_out, char** mas_str, int* pc_code, int* str_num, struct labels* data_labels)
{
    char* ptr = NULL;
    int arg_val = 0;

    ptr = strchr(mas_str[*str_num], ':');
    
    if (ptr != NULL)
    {
        if ( (sscanf(ptr + 1, "%d", &arg_val)) == 0)
        {
            data_labels->current_ptr++;

            sscanf(ptr + 1, "%s", &data_labels->str_labels[data_labels->current_ptr].name);
            data_labels->str_labels[data_labels->current_ptr].num = *pc_code;
        }

        else data_labels->num_labels[arg_val] = *pc_code;

        (*pc_code)--;
    }

    return *pc_code;
}

//!функция обработки комманды с аргументом
int proccesing_witharg(int* buffer_out, char** mas_str, int* pc_code, int* str_num, struct labels* data_labels)
{
    char* ptr = NULL;
    int arg_val = 0;

    ptr = strchr(mas_str[*str_num], ':');
    
    if (ptr != NULL)
    {
        if ( (sscanf(ptr + 1, "%d", &arg_val)) == 0)
        {
            char label_name[15] = {}; 
            int cheaker = 1;
            int index = 0;

            sscanf(ptr + 1, "%s", label_name);
            for ( index = 0; index < 10 && cheaker != 0 ; index++ )
            {
                cheaker = my_strcmp(label_name, data_labels->str_labels[index].name);
            }
            
            index--;
            buffer_out[*pc_code] = data_labels->str_labels[index].num;
        }
        
        else buffer_out[*pc_code] = data_labels->num_labels[arg_val];
    }
    
    else
    {
        if ( (sscanf(mas_str[*str_num], "%d", &buffer_out[*pc_code])) == 0 )
        {
            buffer_out[*pc_code] = toupper(mas_str[*str_num][0]) - 'A';
        }
    }

    return *pc_code;
}

//------------------------------------------------------------------------------------------------------------------------------------------

//!функция распечатки байт кода
int check_byte_code(int* mass, size_t len)
{
    printf("___________________________\n");
    printf("|      commands_buffer    |\n");
    printf("___________________________\n");
    for (size_t i = 1; i < len; i++)
    {   
        printf("||%5zu: command | %5d||\n", i, mass[i]);
    }
    printf("___________________________\n");

    return 1;
}

//!функция создающая сигнатуру
int* signature_maker(int* code)
{
    ((char*)code)[1] = 'K';
    ((char*)code)[2] = 'K'; 
    ((char*)code)[3] = '1';

    return code;
}
