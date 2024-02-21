//
// Created by Bartosz on 21.06.2023.
//
#include "comparators.h"
#include <string.h>
#include <stdlib.h>
#include "tested_declarations.h"
#include "rdebug.h"

int comp_int(const void *ptr1, const void *ptr2) {
    if (!ptr1 || !ptr2) return -1;
    int a = *(int *)ptr1;
    int b = *(int *)ptr2;
    return a - b;
}

int comp_double(const void *ptr1, const void *ptr2) {
    if (!ptr1 || !ptr2) return -1;
    double a = *(double *)ptr1;
    double b = *(double *)ptr2;
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

int comp_point(const void *ptr1, const void *ptr2) {
    if (!ptr1 || !ptr2) return -1;
    struct point_t *a = (struct point_t *)ptr1;
    struct point_t *b = (struct point_t *)ptr2;

    if (a->x > b->x) return 1;
    if (a->x < b->x) return -1;
    if (a->y > b->y) return 1;
    if (a->y < b->y) return -1;

    return 0;
}

void swap(void *a, void *b, size_t size) {
    char *temp = malloc(size);
    if (!temp) return;

    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);

    free(temp);
}
int sort(void *array, size_t n_items, size_t size, int (*comparator)(const void *, const void *)) {
    if(array == NULL || n_items <= 0 || size <= 0 || comparator == NULL) return 1;
    char *base_ptr = (char *)array;

    for (size_t i = 0; i < n_items - 1; i++) {
        for (size_t j = 0; j < n_items - i - 1; j++) {
            if (comparator(base_ptr + j * size, base_ptr + (j + 1) * size) > 0) {
                swap(base_ptr + j * size, base_ptr + (j + 1) * size, size);
            }
        }
    }

    return 0; // Success
}


