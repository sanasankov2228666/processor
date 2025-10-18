#ifndef CALCULATOR_H_
#define CALCULATOR_H_

enum
{
    PUSH = 1,
    POP = 2,
    ADD = 3,
    SUB = 4,
    DIV = 5,
    MULT = 6,
    END = 7,
    OUT = 8,
};

int calculator(struct stk* data);

int my_strcmp(char* str1, const char* str2);

int calculate_input(char* command);

void buffer_free();

#endif
