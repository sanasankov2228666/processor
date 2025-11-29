#include <stdio.h>
#include <string.h>
#include "str_func.h"
#include <stdlib.h>

void global_opener(char* name, char* format);
void code_generator(char* folder);
int fill_code(char* filename);
void full_gen(char* folder);

static FILE* code = NULL;

int main(void)
{
    if (code == NULL)
    {
        global_opener("asm_codes/video.asm", "w");
    }

    char folder[20] = "frames";
    full_gen(folder);

    fclose(code);
    code = NULL;

    return 0;
}

void full_gen(char* folder)
{
    for (int i = 134; i <= 1192; i++)
    {
        fprintf(code, "PUSH 0\n");
        fprintf(code, "POPREG AX\n");
        
        code_generator(folder);      
        fprintf(code, "DRAW\n");
    }

    fprintf(code, "HLT\n");
}

void code_generator(char* folder)
{
    static int dump_count = 134;
    char filename[40] = {};
    snprintf(filename, sizeof(filename), "%s/out%04d.jpg.txt", folder, dump_count++);
    
    if (fill_code(filename)) printf("generate failed\n");
}

int fill_code(char* filename)
{
    FILE* stream = fopen(filename, "r");
    if (stream == NULL) 
    {
        printf("Error: cannot open file %s\n", filename);
        return 1;
    }

    size_t size = size_file(stream);
    char* buffer = NULL;
    file_read(stream, &buffer);

    for (size_t i = 0; i < size; i++)
    {
        fprintf(code, "PUSH %d\n", buffer[i]);
        fprintf(code, "POPM [AX]\n");

        fprintf(code, "PUSHREG AX\n");
        fprintf(code, "PUSH 1\n");
        fprintf(code, "ADD\n");
        fprintf(code, "POPREG AX\n");
    }

    fclose(stream);
    if (buffer != NULL)
        free(buffer);

    return 0;
}

void global_opener(char* name, char* format)
{
    if (code == NULL)
    {
        code = fopen(name, format);
    }
}