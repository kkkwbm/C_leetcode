#include "translator.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "tested_declarations.h"
#include "rdebug.h"

struct word_t** read_words(const char* filename, enum error_t* errcode) {
    if (errcode == NULL) return NULL;
    if (filename == NULL) {
        *errcode = ERROR_INCORRECT_PARAMETERS;
        return NULL;
    }

    char buffer[100];

    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        *errcode = ERROR_FILE_IO;
        return NULL;
    }

    int licznik = 0;

    while (!feof(f)) {
        if (feof(f)) break;
        fscanf(f, "%s", buffer);
        licznik++;
    }

    licznik /= 2;

    struct word_t **slownik = calloc(licznik + 1, sizeof(struct word_t *));
    if (slownik == NULL) {
        *errcode = ERROR_MEMORY;
        fclose(f);
        return NULL;
    }

    fseek(f, 0, SEEK_SET);
    int slowoNumer = 0;

    while (!feof(f)) {
        if (feof(f)) break;
        if (slowoNumer >= licznik) break;
        struct word_t *slowo = calloc(1, sizeof(struct word_t));
        if (slowo == NULL) {
            delete_words(slownik);
            fclose(f);
            *errcode = ERROR_MEMORY;
            return NULL;
        }
        if (slowo == NULL) break;
        fscanf(f, "%s", buffer);
        slowo->text_pl = strdup(buffer);
        fscanf(f, "%s", buffer);
        slowo->text_en = strdup(buffer);
        *(slownik + slowoNumer) = slowo;
        slowoNumer++;
    }

    *errcode = ERROR_OK;
    fclose(f);
    return slownik;
}
void delete_words(struct word_t** tab) {
    if (tab == NULL) return;

    struct word_t **temp = tab;
    while (*temp != NULL) {
        struct word_t *word = *temp;
        if (word != NULL) {
            if (word->text_pl != NULL) free(word->text_pl);
            if (word->text_en != NULL) free(word->text_en);
            free(word);
        }
        temp++;
    }
    free(tab);
}
char** translate_words(struct word_t** tab, int n, ...) {
    if (tab == NULL || n <= 0) return NULL;

    va_list list;
    va_start(list, n);

    char **translated = calloc(n + 1, sizeof(char *));
    if (translated == NULL) {
        return NULL;
    }
    int check = 0;

    for (int i = 0; i < n; i++) {
        int licznik = 0;
        char *szukane = va_arg(list, char *);
        while (*(tab + licznik) != NULL) {
            struct word_t *word = *(tab + licznik);
            if (strcmp(word->text_pl, szukane) == 0) {
                check = 1;
                *(translated + i) = word->text_en;
            }
            licznik++;
        }
        if (check == 0) *(translated + i) = NULL;
        check = 0;
    }

    return translated;
}


