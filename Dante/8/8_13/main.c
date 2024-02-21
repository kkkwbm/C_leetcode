#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include "tested_declarations.h"
#include "rdebug.h"

int* count_words(const char *filename, int *err_code, int N, ...) {
    if(filename == NULL || N <= 0)
    {
        if(err_code) *err_code = 1;
        return NULL;
    }
    if(err_code) *err_code = 0;

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        if(err_code) *err_code = 2;
        return NULL;
    }

    int* counts = (int*) calloc(N, sizeof(int));
    if (!counts)
    {
        if(err_code) *err_code = 3;
        fclose(file);
        return NULL;
    }

    va_list args;
    va_start(args, N);


    for (int i = 0; i < N; i++)
    {
        char *current_word = va_arg(args, char*);
        int word_len = strlen(current_word);
        rewind(file);

        char ch;
        int match_len = 0;
        char prev_ch = 0;

        while ((ch = fgetc(file)) != EOF)
        {
            if (ch == *current_word && (!isalpha(prev_ch) || prev_ch == 0))
            {
                match_len++;
            }
            else if (ch == *(current_word + match_len) && match_len > 0)
            {
                match_len++;
            }
            else match_len = 0;

            if (match_len == word_len)
            {
                char next_ch = fgetc(file);
                if (!isalpha(next_ch)) *(counts + i) += 1;
                ungetc(next_ch, file);
                match_len = 0;
            }

            prev_ch = ch;
        }
    }


    va_end(args);
    fclose(file);

    return counts;
}


int main(int argc, char **argv) {
    if (argc < 3)
    {
        printf("Not enough arguments\n");
        return 9;
    }

    int err;
    int N = argc - 2;
    int * counts = malloc(N * sizeof(int));
    if(counts == NULL)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    for(int i = 0; i < N; i++)
    {
        int *single_count = count_words(*(argv + 1), &err, 1, *(argv + 2 + i));
        if (single_count)
        {
            *(counts + i) = *single_count;
            free(single_count);
        }
        if(err == 2)
        {
            printf("Couldn't open file\n");
            free(counts);
            free(single_count);
            return 4;
        }
        else if(err == 3)
        {
            printf("Failed to allocate memory\n");
            free(counts);
            free(single_count);
            return 8;
        }
    }

    for (int i = 0; i < N; i++)
    {
        printf("%d\n", *(counts + i));
    }
    free(counts);
    return 0;
}

