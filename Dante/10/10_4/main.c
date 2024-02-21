#include "stack.h"
#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"

int main(int argc, char **argv) {
    if(argc < 2)
    {
        printf("Not enough arguments\n");
        return 9;
    }

    char **currentArg = argv + 1;
    for(int i = 1; i < argc; ++i, ++currentArg)
    {
        struct stack_t *stack = NULL;
        int load_result = stack_load(&stack, *currentArg);
        if(load_result == 2)
        {
            printf("Couldn't open file %s\n", *currentArg);
            stack_destroy(&stack);
            continue;
        }
        else if(load_result != 0)
        {
            printf("Failed to allocate memory\n");
            return 8;
        }

        int save_result = stack_save(stack, *currentArg);
        if(save_result == 2)
        {
            printf("Couldn't create file\n");
            stack_destroy(&stack);
            return 5;
        }
        else printf("File %s saved\n", *currentArg);
        stack_destroy(&stack);
    }

    return 0;
}

