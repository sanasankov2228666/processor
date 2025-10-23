#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "../../stack/headers/stack1.h"
#include "enum.h"
#include "str_func.h"
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
    {"PUSH",   PUSH,   1},        {"ADD",     ADD,     0},
    {"SUB",    SUB,    0},        {"DIV",     DIV,     0},
    {"MULT",   MULT,   0},        {"SQRT",    SQvRT,   0},
    {"IN",     IN,     0},        {"HLT",     HLT,     0},
    {"OUT",    OUT,    0},        {"PUSHREG", PUSHREG, 1},
    {"POPREG", POPREG, 1},        {"PUSHM",   PUSHM,   1},
    {"POPM",   POPM,   1},        {"JUMP",    JUMP,    1},
    {"JB",     JB,     1},        {"JBE",     JBE,     1},
    {"JA",     JA,     1},        {"JAE",     JAE,     1},
    {"JE",     JE,     1},        {"JNE",     JNE,     1},
    {"CALL",   CALL,   1},        {"RET",     RET,     0},
    {"DRAW",   DRAW,   0}
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
size_t byte_code_maker(struct main_str* assembler, int asm_number)
{
    size_t pc_code = 1;
    size_t str_c = 0;

    for (; (pc_code < assembler->len && str_c < assembler->len) ; pc_code++, str_c++)
    {

        if ((assembler->mas_str[str_c])[0] == '\0') return pc_code;
        while ((assembler->mas_str[str_c])[0] == '\n') str_c++;

        assembler->buffer_out[pc_code] = compare_func(assembler->mas_str[str_c]);

        printf("%d\n", assembler->buffer_out[pc_code]);
        if (assembler->buffer_out[pc_code] == 0)
        {
            if ((assembler->mas_str[str_c])[0] == ':')
            {
                if (proccesing_label(assembler, &pc_code, &str_c, asm_number)) return ERROR;
                pc_code--;
            }

            else
            {
                printf("unrecognize command [%s] str: %zu\n", assembler->mas_str[str_c], str_c);
                return ERROR;
            }
        }

        else if (commands[assembler->buffer_out[pc_code] - 1].arg == 1)
        {
            pc_code++;
            str_c++;

            if (proccesing_witharg(assembler, &pc_code, &str_c, asm_number)) return ERROR;
        }
    }

    return pc_code;
}

//!функция обработки комманды без аргумента
int proccesing_label(struct main_str* assembler, size_t* pc_code, size_t* str_c, int asm_number)
{
    if (asm_number == 2) return SUCCSES;

    char* ptr = assembler->mas_str[*str_c] + 1;
    int arg_val = 0;
    char name_label[MAX_NAME_LBL] = {};

    if ( (sscanf(ptr, "%d", &arg_val)) == 0)
    {
        //загнать в функцию---
        assembler->lables.current_ptr++;
        if (assembler->lables.current_ptr >= MAX_NAME_LBL)
        {
            printf("max number of labels is reached str: %zu", *str_c);
        }

        sscanf(ptr, "%s", name_label);
        if (equal_label_check(assembler, name_label, str_c)) return ERROR;
        sscanf(ptr, "%s", assembler->lables.str_labels[assembler->lables.current_ptr].name);

        assembler->lables.str_labels[assembler->lables.current_ptr].num = (int) *pc_code;
        //---
    }

    else
    {
        if (arg_val < 0)
        {
            LABLE_MISSTAKE_OUT;
        }

        assembler->lables.num_labels[arg_val] = (int) *pc_code;
    }

    return SUCCSES;
}

//!функция обработки комманды с аргументом
int proccesing_witharg(struct main_str* assembler, size_t* pc_code, size_t* str_c, int asm_number)
{
    char* curr_str = assembler->mas_str[*str_c];
    int arg_val = 0;

    if (curr_str[0] == ':')
    {
        curr_str++;
        if (sscanf(curr_str, "%d", &arg_val) == 0)
        {
            if (proccesing_arg_label(assembler, curr_str, pc_code, str_c, asm_number)) return ERROR;
        }
    }

    else if (curr_str[0] == '[')
    {
        curr_str++;
        check_mem_arg(assembler, curr_str, pc_code, str_c);

        assembler->buffer_out[*pc_code] = toupper(curr_str[0]) - 'A';
    }

    else
    {
        if (sscanf(curr_str, "%d", &arg_val) == 0)
        {
            if (assembler->buffer_out[*pc_code - 1] != POPREG && assembler->buffer_out[*pc_code - 1] != PUSHREG)
            {
                printf("bad syntax reg func str: %zu", *str_c);
                return ERROR;
            }

            assembler->buffer_out[*pc_code] = toupper(curr_str[0]) - 'A';
        }

        else assembler->buffer_out[*pc_code] = arg_val;
    }

    return SUCCSES;
}

//-------------------------------------------------ВСПОМОГАТЕЛЬНЫЕ-ФУНКЦИИ---------------------------------------------------------

int equal_label_check(struct main_str* assembler, char* name_label, size_t* str_c)
{
    for (int i = 0; i < STR_LBL_NUMBER; i++)
    {
        if ( my_strcmp(name_label, assembler->lables.str_labels[i].name) == 0)
        {
            LABLE_MISSTAKE_OUT;
        }
    }

    return SUCCSES;
}

int proccesing_arg_label(struct main_str* assembler, char* curr_str, size_t* pc_code, size_t* str_c, int asm_number )
{
    char name_label[MAX_NAME_LBL] = {};
    int cheaker = 1;
    int index = 0;

    sscanf(curr_str, "%s", name_label);
    for ( index = 0; index < STR_LBL_NUMBER && cheaker != 0 ; index++ )
    {
        cheaker = my_strcmp(name_label, assembler->lables.str_labels[index].name);
    }

    if( index == STR_LBL_NUMBER && asm_number == 2)
    {
        printf("label %s doesent exist str: %zu\n",name_label, *str_c);
        return ERROR;
    }

    index--;

    assembler->buffer_out[*pc_code] = assembler->lables.str_labels[index].num;
    return SUCCSES;
}

//!функция проверки синтаксиса для функция RAM
int check_mem_arg(struct main_str* assembler, char* curr_str, size_t* pc_code, size_t* str_c)
{
    int index = 0;

    if (check_reg_syntax(curr_str, str_c)) return ERROR;

    if (assembler->buffer_out[*pc_code - 1] == PUSHREG ||
        assembler->buffer_out[*pc_code - 1] == POPREG)
    {
        printf("bad syntax str: %zu\n", *str_c);
        return ERROR;
    }

    while ( curr_str[index] != ']' && curr_str[index + 1] != '\0' ) index++;
    if (curr_str[index] != ']')
    {
        printf("bad syntax str: %zu\n", *str_c);
        return ERROR;
    }

    return SUCCSES;
}

//!фунция проверки синтаксиса регистров
int check_reg_syntax(char* curr_str, size_t* str_c)
{
    if ( toupper(curr_str[1]) != 'X')
    {
        printf("bad syntax reg arg str: %zu\n", *str_c);
        return ERROR;
    }

    return ERROR;
}

//------------------------------------------------------------------------------------------------------------------------------------------

int asm_deleter(struct main_str* assembler, char* buffer)
{
    free(buffer);
    free(assembler->buffer_out);
    free(assembler->mas_str);

    printf("asm deleted\n");
    return SUCCSES;
}

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
