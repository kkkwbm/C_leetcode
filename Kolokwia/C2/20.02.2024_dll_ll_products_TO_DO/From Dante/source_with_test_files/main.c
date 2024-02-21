#include <stdio.h>
#include <stdint.h>
#include "defs.h"
#include "tested_declarations.h"
#include "rdebug.h"

CREATE_FUNCTION_COUNT01(int)

int main(int argc, char **argv) {
    if (argc < 2)
    {
        printf("Not enough arguments");
        return 9;
    }
    struct double_linked_list_t *list = NULL;

    for (int i = 1; i < argc; i++)
    {
        int r = read_list(&list, *(argv + i), count01_int);
        if (r == -2)
        {
            printf("Couldn't open file");
            free_list(list);
            return 4;
        }
        if (r == -3)
        {
            printf("File corrupted");
            free_list(list);
            return 6;
        }

        if (r == -4)
        {
            printf("Failed to allocate memory");
            free_list(list);
            return 8;
        }
    }

    display_list(list);
    free_list(list);
    return 0;
}
