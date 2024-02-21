#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tested_declarations.h"
#include "rdebug.h"

char **split_words(const char *text) {
    if (text == NULL || *text == '\0') return NULL;

    int word_count = 0;
    int in_word = 0;
    for (int i = 0; *(text + i) != '\0'; i++)
    {
        if (isalpha(*(text + i)))
        {
            if (!in_word)
            {
                in_word = 1;
                word_count++;
            }
        }
        else in_word = 0;
    }

    char **words = (char **)malloc((word_count + 1) * sizeof(char *));
    if (words == NULL) return NULL;

    int word_index = 0;
    int start = 0;
    in_word = 0;
    for (int i = 0; *(text + i) != '\0'; i++)
    {
        if (isalpha(*(text + i)))
        {
            if (!in_word)
            {
                in_word = 1;
                start = i;
            }
        }
        else
        {
            if (in_word)
            {
                *(words + word_index) = (char *)malloc((i - start + 1) * sizeof(char));
                if (!*(words + word_index))
                {
                    for (int j = 0; j < word_index; j++)
                    {
                        free(*(words + j));
                    }
                    free(words);
                    return NULL;
                }
                strncpy(*(words + word_index), text + start, i - start);
                *(*(words + word_index) + i - start) = '\0';
                word_index++;
            }
            in_word = 0;
        }
    }

    if (in_word)
    {
        *(words + word_index) = (char *)malloc((strlen(text) - start + 1) * sizeof(char));
        if (!*(words + word_index))
        {
            for (int j = 0; j < word_index; j++)
            {
                free(*(words + j));
            }
            free(words);
            return NULL;
        }
        strcpy(*(words + word_index), text + start);
        word_index++;
    }

    if (word_count == 0) {
        free(words);
        return NULL;
    }


    *(words + word_index) = NULL;
    return words;
}

int compare(const void *a, const void *b) {
    char *str_a = *(char **)a;
    char *str_b = *(char **)b;

    return strcmp(str_a, str_b);
}

int sort_words(char **words) {
    if (words == NULL) return 1;

    int count = 0;
    while (*(words + count) != NULL) count++;

    qsort(words, count, sizeof(char *), compare);
    return 0;
}

void destroy(char **words) {
    if (words == NULL) return;

    int i = 0;
    while (*(words + i) != NULL)
    {
        free(*(words + i));
        i++;
    }
    free(words);
}

int contains_alpha(const char *str) {
    while (*str)
    {
        if (isalpha(*str)) return 1;
        str++;
    }
    return 0;
}


int main() {
    char *input = (char *)malloc(1000 * sizeof(char));
    if (input == NULL) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Enter text: ");
    fgets(input, 1000, stdin);
    char *newline = strchr(input, '\n');
    if (newline) *newline = '\0';

    if (!contains_alpha(input))
    {
        printf("Nothing to show\n");
        free(input);
        return 0;
    }

    char **words = split_words(input);
    if (words == NULL)
    {
        printf("Failed to allocate memory\n");
        free(input);
        return 8;
    }

    if (sort_words(words))
    {
        destroy(words);
        free(input);
        printf("Failed to sort words\n");
        return 1;
    }

    if (*words == NULL) printf("Nothing to show\n");
    else
    {
        int i = 0;
        while (*(words + i) != NULL)
        {
            printf("%s\n", *(words + i));
            i++;
        }
    }

    destroy(words);
    free(input);
    return 0;
}


