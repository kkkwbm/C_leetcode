#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"

int stack_push(struct stack_t **stack, char *value) {
    if(!stack || !value) return 1;

    struct stack_t *new_top = malloc(sizeof(struct stack_t));
    if(!new_top) return 2;

    new_top->sentence = value;
    new_top->prev = *stack;
    *stack = new_top;

    return 0;
}

char *stack_pop(struct stack_t **stack, int *err_code) {
    if(!stack || !*stack)
    {
        if(err_code) *err_code = 1;
        return NULL;
    }

    char *sentence = (*stack)->sentence;
    struct stack_t *old_top = *stack;
    *stack = (*stack)->prev;
    free(old_top);

    if(err_code) *err_code = 0;
    return sentence;
}

void stack_destroy(struct stack_t **stack) {
    if(stack == NULL || *stack == NULL) return;
    while(*stack) free(stack_pop(stack, NULL));
    *stack = NULL;
}

int stack_save(const struct stack_t *stack, const char *filename) {
    if(!stack || !filename) return 1;

    FILE *file = fopen(filename, "w");
    if(!file) return 2;

    const struct stack_t *current = stack;
    while(current)
    {
        fprintf(file, "%s", current->sentence);
        current = current->prev;
    }

    fclose(file);
    return 0;
}


int stack_load(struct stack_t **stack, const char *filename) {
    if (!stack || !filename || *stack != NULL) return 1;

    FILE *file = fopen(filename, "r");
    if (!file) return 2;

    char c;
    int len = 0;
    int result = 0;

    while ((c = fgetc(file)) != EOF)
    {
        if (c == '.')
        {
            char *sentence = malloc(len + 2);
            if (!sentence)
            {
                result = 3;
                fclose(file);
                stack_destroy(stack);
                return result;
            }

            fseek(file, -(len + 1), SEEK_CUR);

            for (int i = 0; i < len; i++)
            {
                char ch = fgetc(file);
                if (feof(file))
                {
                    free(sentence);
                    stack_destroy(stack);
                    fclose(file);
                    return 3;
                }
                *(sentence + i) = ch;
            }
            *(sentence + len) = '.';
            *(sentence + len + 1) = '\0';

            fseek(file, 1, SEEK_CUR);

            int push_status = stack_push(stack, sentence);
            if (push_status)
            {
                free(sentence);
                stack_destroy(stack);;
                fclose(file);
                return 3;
            }

            len = 0;
        }
        else len++;
    }

    fclose(file);
    return result;
}





