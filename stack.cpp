#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cstdint>

#define KANAREKA1 -100
#define KANAREKA2 -200
#define POISON -2

typedef int type;

enum
{
    correct = 0,
    bad_size = 1,
    bad_capacity = 2,
    bad_pointer = 3,

};

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

//!прототипы


//!функции работы со стеком

void stack_creator(struct stk* data, size_t capacity);

void stack_push(struct stk* data, type value);

int stack_pop(struct stk* data);

void stack_deleter(struct stk* data);


//!функции проверки

int stack_dump(struct stk data, const char* func, const char* FILE, int LINE);

int verify(struct stk* data);

int cheacker(struct stk* data, const char* func, const char* file, int line);

double hash_check(struct stk data);

void dump_helper(struct stk data, const char* func, const char* FILE, int LINE);


//!функции для калькулятора

int calculator(struct stk* data);

int my_strcmp(char* str1, const char* str2);

int calculate_input(char* command);


//!доп функции

void slicer(void);

//!структура стека
struct stk
{
    type* stack = NULL;
    size_t size = 0;
    size_t capacity = 0;
    size_t error[6] = {0, 0, 0, 0, 0, 0};
    double hash = 0;
};


int main(void)
{
    struct stk data1 = {};

    stack_creator(&data1, 3);

    slicer();
    printf("press enter to start\n");
    while (calculator(&data1) == 0);

    slicer();
    printf("program output\n");

    for (size_t i = 0; i < data1.capacity + 2; i ++)
    {
        printf("%d\n", data1.stack[i]);
    }

    while (data1.size > 0)
    {
        printf("%d\n", stack_pop(&data1));
    }

    stack_deleter(&data1);

    return 0;
}

//!функция создания стека
void stack_creator(struct stk* data, size_t capacity)
{
    if (capacity > 100000000)
    {
        data->error[1] = bad_capacity;
        capacity = 5;
    }

    data->stack = (type*) calloc (capacity + 2, sizeof(data->stack[0]));
    for (size_t i = 1; i < capacity + 1; i++)
    {
        data->stack[i] = POISON;
    }

    data->size = 0;
    data->capacity = capacity;

    data->stack[0] = KANAREKA1;
    data->stack[capacity + 1] = KANAREKA2;

    data->hash = hash_check(*data);

    cheacker(data, __FUNCTION__, __FILE__, __LINE__);
}

//!функция внесения в стек
void stack_push(struct stk* data, type value)
{
    cheacker(data, __FUNCTION__, __FILE__, __LINE__);

    if (data->capacity == data->size)
    {
        data->stack = (type*) realloc (data->stack, (data->capacity + 1) * 2 * sizeof(data->stack[0]));
        if (data->stack == NULL)
        {
            data->error[1] = bad_pointer;
        }

        data->stack[data->capacity + 1] = 0;
        data->capacity = (data->capacity) * 2;
        data->stack[data->capacity + 1] = KANAREKA2;

        for (size_t i = data->size + 1; i < data->capacity + 1; i++)
        {
            data->stack[i] = POISON;
        }
    }

    data->stack[data->size + 1] = value;
    data->size = data->size + 1;
    data->hash = hash_check(*data);

    cheacker(data, __FUNCTION__, __FILE__, __LINE__);
}

//!функция доставания из стека
int stack_pop(struct stk* data)
{
    cheacker(data, __FUNCTION__, __FILE__, __LINE__);

    if (data->size == 0)
    {
        data->error[0] = bad_size;
        return 0;
    }

    int parametr = data->stack[data->size];
    data->stack[data->size] = POISON;
    data->size = data->size - 1;
    data->hash = hash_check(*data);

    cheacker(data, __FUNCTION__, __FILE__, __LINE__);
    return parametr;
}

//!функция удаления стека
void stack_deleter(struct stk* data)
{
    if (data->stack == NULL)
    {
        printf("ERROR IN stack_deleter\n");
    }

    data->capacity = 0;
    data->size = 0;
    free (data->stack);
    data->stack = NULL;
}

//!функция вывода ошибок
int stack_dump(struct stk data, const char* func, const char* file, int LINE)
{
    int counter = 0;

    if (data.error[0])
    {
        slicer();
        printf("bad size!\n");
        dump_helper(data, func, file, LINE);
        counter++;
    }

    if (data.error[1])
    {
        slicer();
        printf("bad capasicity!\n");
        dump_helper(data, func, file, LINE);
        counter++;
    }

    if (data.error[2])
    {
        slicer();
        printf("bad pointer!\n");
        dump_helper(data, func, file, LINE);
        counter++;
    }

    if (data.error[3])
    {
        slicer();
        printf("kanareyka changed!\n");
        dump_helper(data, func, file, LINE);
        counter++;
    }

    if (data.error[4])
    {
        slicer();
        printf("Poison stack data changed!\n");
        dump_helper(data, func, file, LINE);
        counter++;
    }

    if (data.error[5])
    {
        slicer();
        printf("Hash is different\n");
        dump_helper(data, func, file, LINE);
        counter++;
    }

    return counter;
}

//!фунция фиксирующая ошибки
int verify(struct stk* data)
{
    int counter = 0;
    if (data->size > 100000000 || data->size > data->capacity)
    {
        data->error[0] = 1;
        counter++;
    }

    if (data->capacity > 100000000 || data->capacity == 0)
    {
        data->error[1] = 1;
        counter++;
    }

    if (data->stack == NULL)
    {
        data->error[2] = 1;
        counter++;
    }

    if (data->stack[0] != KANAREKA1 || data->stack[data->capacity + 1] != KANAREKA2)
    {
        data->error[3] = 1;
        counter++;
    }

    for (size_t i = data->size + 1; i < data->capacity; i++)
    {
        if (data->stack[i] != POISON)
        {
            data->error[4] = 1;
        }
    }

    if ((data->hash - hash_check(*data)) > 0.000000001)
    {
        data->error[5] = 1;
        counter++;
    }

    return counter;
}

//!функция проверки
int cheacker(struct stk* data, const char* func, const char* file, int line)
{
    int a = verify(data);
    int b = stack_dump(*data, func, file, line);

    for (size_t i = 0; i < (sizeof(data->error)/sizeof(data->error[0])); i++)
    {
        data->error[i] = 0;
    }

    return (a && b);
}

//TODO заменить на более надежную DJB2
//!хэш функция
double hash_check(struct stk data)
{
    intptr_t stack_ptr = (intptr_t)data.stack;
    intptr_t error_ptr = (intptr_t)&data.error;

    double elem1 = 0;
    double elem2 = 0;

    for (size_t i = 0; i < data.capacity + 2; i++)
    {
        elem1 = elem1 + 1.23 * data.stack[i];
    }

    for (size_t i = 0; i < (sizeof(data.error) / sizeof(data.error[0])); i++)
    {
        elem2 = elem2 + 2.31 * (double)data.error[i];
    }

    double zero_check = elem2 + 1;
    if (zero_check < 0.0000000001) {
        zero_check = 1;
    }

    double ptr_component = (double)(error_ptr / (stack_ptr + 1));
    double size_component = (double)(data.size + data.capacity);

    return (elem1 / zero_check) * size_component * ptr_component;
}

void slicer(void)
{
    printf("______________________________________________________________________________________________________________\n");
}

//!помощь вывода для функции проверки
void dump_helper(struct stk data, const char* func, const char* file, int LINE)
{
    printf(">ERROR<\n");
    printf("In function %s, %s:%d\n", func, file, LINE);
    printf("Stack = %p, \n", data.stack);
    printf("size = %lu\n", data.size);
    printf("capacity = %lu\n", data.capacity);
    printf("data:\n");
    for (size_t i = 0; i < data.capacity + 2; i++)
    {
        printf("[%lu] = %d\n", i, data.stack[i]);
    }

}

//!калькулятор
int calculator(struct stk* data)
{
    int a = 0;
    int help = 0;
    int swch = 0;
    char command[8] = {};

    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF);
    swch = calculate_input(command);

    while (swch == 0)
    {
        while(getchar() != '\n');
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
        scanf("%d", &a);
        while (a < 0)
        {
            printf("parametr cant be < 0\n");
            printf("write push parametr\n");
            scanf("%d", &a);
        }

        stack_push(data, a);
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
            printf("stack have %lu parametr\n", data->size);
            break;
        }

        a = (stack_pop(data) + stack_pop(data));
        stack_push(data, a);
        printf("added\n");
        break;

    case SUB:
        if (data->size < 2)
        {
            printf("stack have %lu parametr\n", data->size);
            break;
        }

        if ((data->stack[data->size - 1] - data->stack[data->size - 2]) < 0)
        {
            printf("cant be subbed\n");
            break;
        }

        a = (stack_pop(data) - stack_pop(data));
        stack_push(data, a);
        printf("subbed\n");
        break;

    case DIV:
        if (data->size < 2)
        {
            printf("stack have %lu parametr\n", data->size);
            break;
        }

        if (data->stack[data->size - 2] == 0)
        {
            printf("cant be dived\n");
            break;
        }

        a = (stack_pop(data) / stack_pop(data));
        stack_push(data, a);
        printf("dived\n");
        break;

    case MULT:
        if (data->size < 2)
        {
            printf("stack have %lu parametr\n", data->size);
            break;
        }

        a = (stack_pop(data) * stack_pop(data));
        stack_push(data, a);
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
    int a = 0;
    size_t i = 0;
    if (strlen(str1) != strlen(str2))
    {
        return 1;
    }

    while (str1[i] != '\0' && str2[i] != '\0')
    {
        a = tolower (str1[i]) - tolower (str2[i]);
        i++;
        if (a != 0)
        {
            break;
        }
    }
    return a;
}

//!функция ввода для калькулятора
int calculate_input(char* command)
{
    int swch = 0;

    printf("write your command:\n");
    scanf("%5[^\n]", command);

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
