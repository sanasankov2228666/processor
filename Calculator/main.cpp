#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <cstdint>
#include "../stack/headers/stack1.h"
#include "../stack/headers/checker.h"
#include "calc_headers/calculator.h"

typedef int type;

int main(void)
{
    struct stk data1 = {};

    stack_creator(&data1, 3);

    slicer();
    printf("press enter to start\n");
    while (calculator(&data1) == 0);

    slicer();
    printf("program output\n");

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

    stack_deleter(&data1);

    return 0;
}
