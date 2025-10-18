#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include "../../stack/headers/stack1.h"
#include "enum.h"
#include "str_func.h"
#include "fileopen.h"

static struct commands
{
    const char* name;
    const int number;

} 

//!массив комманд
commands[NUMBER_COMMANDS] = 
{
    {"PUSH", PUSH},       {"ADD", ADD},
    {"SUB", SUB},         {"DIV", DIV},
    {"MULT", MULT},       {"SQRT", SQvRT},
    {"IN", IN},           {"OUT", OUT},
    {"PUSHREG", PUSHREG}, {"POPREG", POPREG},
    {"JUMP", JUMP},       {"JB", JB},
    {"JBE", JBE},         {"JA", JA},
    {"JAE", JAE},         {"JE", JE},
    {"JNE", JNE},         {"HLT", HLT}
};

int* make_code(char** str_mas, int* code, size_t len)
{
    char* str = NULL;
    int val = 0;
    int swch = 0;

    for (size_t i1 = 0; i1 < 2 * len; i1++)
    {
        sscanf(str_mas[i1], "%s %d", str, val);
        for (int i = 0; i < NUMBER_COMMANDS && swch == 0; i++ )
        {
            if (my_strcmp(str, commands[i].name) == 0) swch = commands[i].number;
        }

        code[i1] = swch;

        if (val != 0)
        {
            i1++;
            code[i1] = val;
        }
    }

    return code;
}