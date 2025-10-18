#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "assembler.h"
#include "str_func.h"
#include "fileopen.h"

typedef int type;

int main(void)
{
    //!открываем файл с командами
    FILE* stream = file_opener("SPU/commands_in.asm", "rb", __FUNCTION__, __FILE__, __LINE__);
    if (stream == NULL) return 1;
    
    //!читаем весь текст в один буфер
    char* buffer_commands = NULL;
    file_read(stream, &buffer_commands);
    puts(buffer_commands);
    fclose(stream);
    
    //!создаем массив указателей на буфер с текстом
    size_t len = 2 * n_check(buffer_commands) + 1;
    char** mas_str = make_mass(buffer_commands, len);
    changer(&buffer_commands, '\n', '\0');

    if (mas_str == NULL) return 1;
    
    //!создаю массив с байт кодом
    int* buffer_out = (int*) calloc (len, sizeof(int));
    struct labels data_labels = {};
    code_maker(buffer_out, mas_str, len, &data_labels);
    len = code_maker(buffer_out, mas_str, len, &data_labels);

    //!создаём сигнатуру
    signature_maker(buffer_out);

    //!открываем файл с байткодом
    FILE* stream_out = file_opener("SPU/translate_cmd.asm", "wb", __FUNCTION__, __FILE__, __LINE__);
    if (stream == NULL)
    {
        free(buffer_commands);
        free(buffer_out);
        free(mas_str);
        return 0;
    }

    //!записываем файл с байткодом
    fwrite(buffer_out, len, sizeof(buffer_out[0]), stream_out);

    printf("succsesly assembled\n");

    check_byte_code(buffer_out, len);

    fclose(stream_out);

    free(buffer_commands);
    free(buffer_out);
    free(mas_str);

    return 0;
}
