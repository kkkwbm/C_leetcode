#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int array_create(struct array_t *a, int N){
    if(a == NULL || N <= 0) return 1;

    (a->ptr) = calloc(N, sizeof(int));

    if((a->ptr) == NULL) return 2;

    (a->capacity) = N;
    (a->size) = 0;
    return 0;
}
void array_display(const struct array_t *a){
    if (a == NULL || a->ptr == NULL || a->size < 0 || a->capacity <= 0 || a->size > a->capacity) return;

    for(int i = 0;i < (a->size) ;i++) printf("%d ",*((a->ptr)+i));
}
void array_destroy(struct array_t *a){
    if(a == NULL || (a->ptr) == NULL) return;
    free(a->ptr);
}

int array_push_back(struct array_t *a, int value) {
    if (a == NULL || a->ptr == NULL || a->size < 0 || a->capacity <= 0 || a->size > a->capacity) return 1;
    if (a->size == a->capacity) return 2;

    *(a->ptr + a->size) = value;
    a->size++;

    return 0;
}