#include "dictionary.h"
#include "tested_declarations.h"
#include "rdebug.h"


struct dictionary_t* create_dictionary(int N, int *err_code) {
    if (N <= 0)
    {
        if (err_code) *err_code = 1;
        return NULL;
    }

    struct dictionary_t *dict = malloc(sizeof(struct dictionary_t));
    if (!dict)
    {
        if(err_code) *err_code = 2;
        return NULL;
    }

    dict->wc = malloc(N * sizeof(struct word_count_t));
    if (!dict->wc)
    {
        free(dict);
        if(err_code) *err_code = 2;
        return NULL;
    }

    for (int i = 0; i < N; i++)
    {
        (dict->wc + i)->word = NULL;
        (dict->wc + i)->counter = 0;
    }

    dict->size = 0;
    dict->capacity = N;

    if(err_code) *err_code = 0;
    return dict;
}

void destroy_dictionary(struct dictionary_t** d) {
    if (!d || !*d || !(*d)->wc) return;

    for (int i = 0; i < (*d)->size; i++)
    {
        free(((*d)->wc + i)->word);
    }

    free((*d)->wc);
    free(*d);
    *d = NULL;
}

int dictionary_add_word(struct dictionary_t *d, const char *word) {
    if (d == NULL || word == NULL || d->capacity <= 0 || d->size < 0 || d->wc == NULL) return 1;

    for (int i = 0; i < d->size; i++)
    {
        if (strcmp((d->wc + i)->word, word) == 0)
        {
            (d->wc + i)->counter++;
            return 0;
        }
    }

    if (d->size >= d->capacity) {
        struct word_count_t *new_wc = realloc(d->wc, 2 * d->capacity * sizeof(struct word_count_t));
        if (!new_wc) return 2;

        d->wc = new_wc;
        d->capacity *= 2;

        for (int i = d->size; i < d->capacity; i++) {
            (d->wc + i)->word = NULL;
            (d->wc + i)->counter = 0;
        }
    }

    (d->wc + d->size)->word = malloc((strlen(word) + 1) * sizeof(char));
    if (!(d->wc + d->size)->word) return 2;

    strcpy((d->wc + d->size)->word, word);
    (d->wc + d->size)->counter = 1;
    d->size++;

    return 0;
}

struct word_count_t* dictionary_find_word(const struct dictionary_t *d, const char *word) {
    if (!d || !word || !d->wc || d->size <= 0) return NULL;

    for (int i = 0; i < d->size; i++) {
        if (strcmp((d->wc + i)->word, word) == 0)
        {
            return d->wc + i;
        }
    }
    return NULL;
}

void dictionary_display(const struct dictionary_t *d) {
    if (!d || !d->wc || d->size <= 0 || d->wc == NULL || d->size > d->capacity) return;

    for (int i = 0; i < d->size; i++)
    {
        printf("%s %d\n", (d->wc + i)->word, (d->wc + i)->counter);
    }
}

int compare_strings_alphabetically(const void *a, const void *b) {
    struct word_count_t *word1 = (struct word_count_t *)a;
    struct word_count_t *word2 = (struct word_count_t *)b;
    return strcmp(word1->word, word2->word);
}

int dictionary_sort_alphabetically(struct dictionary_t *d) {
    if (d == NULL || d->wc == NULL || d->size <= 0) return 1;

    qsort(d->wc, d->size, sizeof(struct word_count_t), compare_strings_alphabetically);
    return 0;
}

int compare_word_counts(const void *a, const void *b) {
    struct word_count_t *word1 = (struct word_count_t *)a;
    struct word_count_t *word2 = (struct word_count_t *)b;

    if (word1->counter != word2->counter)
    {
        return word2->counter - word1->counter;
    }

    return strcmp(word1->word, word2->word);
}

int dictionary_sort_occurence(struct dictionary_t *d) {
    if (d == NULL || d->wc == NULL || d->size <= 0) return 1;

    qsort(d->wc, d->size, sizeof(struct word_count_t), compare_word_counts);
    return 0;
}

int save_dictionary_b(const struct dictionary_t *d, const char *filename) {
    if (d == NULL || d->wc == NULL || filename == NULL || d->size < 0 || d->capacity < 0 || d->size > d->capacity) return 1;

    FILE *f = fopen(filename, "wb");
    if (f == NULL) return 2;

    fwrite(&(d->size), sizeof(int), 1, f);

    struct word_count_t *current_wc = d->wc;

    for (int i = 0; i < d->size; ++i)
    {
        int word_len = strlen(current_wc->word);
        fwrite(&word_len, sizeof(int), 1, f);
        fwrite(current_wc->word, sizeof(char), word_len, f);
        fwrite(&(current_wc->counter), sizeof(int), 1, f);

        current_wc++;
    }

    fclose(f);
    return 0;
}

struct dictionary_t* load_dictionary_b(const char *filename, int *err_code) {
    if (filename == NULL)
    {
        if (err_code) *err_code = 1;
        return NULL;
    }

    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        if (err_code) *err_code = 2;
        return NULL;
    }

    int num_words;
    if (fread(&num_words, sizeof(int), 1, file) != 1)
    {
        if (err_code) *err_code = 3;
        fclose(file);
        return NULL;
    }

    int my_err_code = 0;

    struct dictionary_t *dict = create_dictionary(num_words, &my_err_code);
    if (dict == NULL)
    {
        if (err_code) *err_code = my_err_code == 2 ? 4 : 3;
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < num_words; i++)
    {
        int word_len;
        if (fread(&word_len, sizeof(int), 1, file) != 1)
        {
            if (err_code) *err_code = 3;
            destroy_dictionary(&dict);
            fclose(file);
            return NULL;
        }

        if(word_len <= 0 || word_len > 1024)
        {
            if (err_code) *err_code = 3;
            destroy_dictionary(&dict);
            fclose(file);
            return NULL;
        }

        char *word = malloc((word_len + 1) * sizeof(char));
        if (word == NULL)
        {
            if (err_code) *err_code = 4;
            destroy_dictionary(&dict);
            fclose(file);
            return NULL;
        }

        if ((int)fread(word, sizeof(char), word_len, file) != word_len)
        {
            if (err_code) *err_code = 3;
            destroy_dictionary(&dict);
            fclose(file);
            free(word);
            return NULL;
        }
        *(word + word_len) = '\0';

        int counter;
        if (fread(&counter, sizeof(int), 1, file) != 1)
        {
            if (err_code) *err_code = 3;
            destroy_dictionary(&dict);
            fclose(file);
            free(word);
            return NULL;
        }

        int valid = dictionary_add_word(dict, word);
        if(valid == 2){
            if (err_code) *err_code = 4;
            destroy_dictionary(&dict);
            fclose(file);
            free(word);
            return NULL;
        }
        struct word_count_t *wc = dictionary_find_word(dict, word);
        if (wc) wc->counter = counter;
        free(word);
    }

    fclose(file);
    if (err_code) *err_code = 0;
    return dict;
}






