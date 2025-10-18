#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cstdint>
#include "../stack/headers/stack1.h"
#include "calc_headers/calculator.h"

//!калькулятор
int calculator(struct stk* data)
{
    int val = 0;
    int help = 0;
    int swch = 0;
    char command[8] = {};

    buffer_free();
    swch = calculate_input(command);

    while (swch == 0)
    {
        buffer_free();
        printf("ERROR, command is Unrecognized!\n\n");
        for (int i = 0; i < 6; i++)
        {
            command[i] = '\0';
        }

        swch = calculate_input(command);
    }

    switch (swch)
    {
    case PUSH:
        printf("write push parametr\n");
        scanf("%d", &val);
        while (val < 0)
        {
            printf("parametr cant be < 0\n");
            printf("write push parametr\n");
            scanf("%d", &val);
        }

        stack_push(data, val);
        printf("pushed\n");
        break;

    case POP:
        if (data->size < 1)
        {
            printf("stack dosent have paramets\n");
            break;
        }

        stack_pop(data);
        printf("poped\n");
        break;

    case ADD:
        if (data->size < 2)
        {
            printf("stack have %zu parametr\n", data->size);
            break;
        }

        val = (stack_pop(data) + stack_pop(data));
        stack_push(data, val);
        printf("added\n");
        break;

    case SUB:
        if (data->size < 2)
        {
            printf("stack have %zu parametr\n", data->size);
            break;
        }

        if ((data->stack[data->size - 1] - data->stack[data->size - 2]) < 0)
        {
            printf("cant be subbed\n");
            break;
        }

        val = (stack_pop(data) - stack_pop(data));
        stack_push(data, val);
        printf("subbed\n");
        break;

    case DIV:
        if (data->size < 2)
        {
            printf("stack have %zu parametr\n", data->size);
            break;
        }

        if (data->stack[data->size - 2] == 0)
        {
            printf("cant be dived\n");
            break;
        }

        val = (stack_pop(data) / stack_pop(data));
        stack_push(data, val);
        printf("dived\n");
        break;

    case MULT:
        if (data->size < 2)
        {
            printf("stack have %zu parametr\n", data->size);
            break;
        }

        val = (stack_pop(data) * stack_pop(data));
        stack_push(data, val);
        printf("multiplayed\n");
        break;

    case OUT:
        if (data->size < 1)
        {
            printf("stack dosent have paramets\n");
            break;
        }

        printf("stack out = %d\n", stack_pop(data));
        break;

    case END:
        help = 1;
        break;

    default:
        break;
    }

    return help;
}

//!функция сравнения строк
int my_strcmp(char* str1, const char* str2)
{
    int div = 0;
    size_t i = 0;
    if (strlen(str1) != strlen(str2))
    {
        return 1;
    }

    while (str1[i] != '\0' && str2[i] != '\0')
    {
        div = tolower (str1[i]) - tolower (str2[i]);
        i++;
        if (div != 0)
        {
            break;
        }
    }
    return div;
}

//!функция ввода для калькулятора
int calculate_input(char* command)
{
    int swch = 0;

    printf("write your command:\n");
    scanf("%5[^\n]", command);

    //strcasecmp()

    if (my_strcmp(command, "PUSH") == 0) swch = PUSH;
    else if (my_strcmp(command, "POP") == 0) swch = POP;
    else if (my_strcmp(command, "ADD") == 0) swch = ADD;
    else if (my_strcmp(command, "SUB") == 0) swch = SUB;
    else if (my_strcmp(command, "DIV") == 0) swch = DIV;
    else if (my_strcmp(command, "MULT") == 0) swch = MULT;
    else if (my_strcmp(command, "END") == 0) swch = END;
    else if (my_strcmp(command, "OUT") == 0) swch = OUT;

    return swch;
}

void buffer_free()
{
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF);
}
