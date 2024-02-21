#include <stdio.h>
#include "translator.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"

int main(int argc, char **argv) {

    if (argc <= 2) {
        printf("Wrong number of parameters");
        return 2;
    }

    enum error_t ERR;
    struct word_t **slownik = read_words(*(argv + 1), &ERR);
    if (ERR == ERROR_FILE_IO) {
        printf("Failed to open file");
        return 1;
    } else if (ERR == ERROR_MEMORY) {
        printf("Failed to allocate memory");
        return 8;
    }

    for (int i = 2; i < argc; i++) {
        char **znalezione = translate_words(slownik, 1, *(argv + i));
        if (znalezione == NULL) {
            delete_words(slownik);
            printf("Failed to allocate memory");
            return 8;
        }
        if (*znalezione == NULL) {
            printf("Word not found\n");
        } else {
            printf("%s\n", *znalezione);
        }
        free(znalezione);
    }

    delete_words(slownik);
    return 0;
}



