#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "tested_declarations.h"
#include "rdebug.h"


void clearBuffer() {
    while(getchar() != '\n');
}

int concatenate(char *buf, int bufsize, int num, ...) {
    if (buf == NULL || bufsize <= 0 || num <= 0) return 1;

    va_list args;
    va_start(args, num);

    int used = 0;
    for (int i = 0; i < num; i++) {
        char *str = va_arg(args, char*);
        int len = strlen(str);
        if (used + len + 1 > bufsize) return 2;
        strcpy(buf + used, str);
        used += len;
        if (i < num - 1) {
            *(buf + used) = ' ';
            used++;
        }
    }
    *(buf + used) = '\0';
    va_end(args);

    return 0;
}

void free_memory(char **texts, char *result) {
    for (int i = 0; i < 4; i++) {
        if (*(texts + i)) free(*(texts + i));
    }
    if (texts) free(texts);
    if (result) free(result);
}

int main() {
    char **texts = (char **)malloc(4 * sizeof(char *));
    if (!texts) {
        free(texts);
        printf("Failed to allocate memory\n");
        return 8;
    }
    char *result = (char *)malloc(4004 * sizeof(char));

    if (!result) {
        free_memory(texts, result);
        printf("Failed to allocate memory\n");
        return 8;
    }

    for (int i = 0; i < 4; i++) {
        *(texts + i) = (char *)malloc(1001 * sizeof(char));
        if (!*(texts + i)) {
            free_memory(texts, result);
            printf("Failed to allocate memory\n");
            return 8;
        }
    }

    int num;
    printf("Podaj liczbe tekstow do wprowadzenia: ");
    if (scanf("%d", &num) != 1) {
        free_memory(texts, result);
        printf("Incorrect input\n");
        return 1;
    }

    if (num < 2 || num > 4) {
        free_memory(texts, result);
        printf("Incorrect input data\n");
        return 2;
    }

    clearBuffer();

    printf("Podaj teksty: ");
    for (int i = 0; i < num; i++)
    {
        fgets(*(texts + i), 1001, stdin);
        int len = strlen(*(texts + i));
        if (*(*(texts + i) + len - 1) != '\n') // Check if the last character is not a newline
        {
            clearBuffer(); // Clear remaining characters from the buffer
        }
        else
        {
            *(*(texts + i) + len - 1) = '\0'; // Remove the newline character
        }
    }

    if (concatenate(result, 4004, num, *(texts + 0), *(texts + 1), *(texts + 2), *(texts + 3)) != 0) {
        free_memory(texts, result);
        printf("Failed to concatenate\n");
        return 1;
    }

    printf("%s", result);
    free_memory(texts, result);

    return 0;
}

