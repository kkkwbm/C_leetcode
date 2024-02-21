#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include <math.h>

#define RAD_TO_DEG (180.0 / M_PI)

int array_push_back_float(struct array_t *a, float value) {
    if (a == NULL || a->ptr == NULL || a->size < 0 || a->capacity <= 0 || a->size > a->capacity) return 1;
    if (a->size == a->capacity) return 2;

    *(a->ptr + a->size) = value;
    a->size++;

    return 0;
}

void array_display_float(const struct array_t *a) {
    if (a == NULL || a->ptr == NULL || a->size <= 0 || a->capacity <= 0 || a->size > a->capacity) return;

    for (int i = 0; i < a->size; i++) printf("%.2lf ", *(a->ptr + i));
    printf("\n");
}

void array_destroy_float(struct array_t *a) {
    if (a == NULL) return;

    free(a->ptr);
    a->ptr = NULL;
    a->size = 0;
    a->capacity = 0;
}

void array_destroy_struct_float(struct array_t **a) {
    if (a == NULL || *a == NULL) return;

    array_destroy_float(*a);
    free(*a);
    *a = NULL;
}

int array_create_float(struct array_t *a, int N) {
    if (N <= 0 || a == NULL) return 1;

    a->ptr = calloc(N,sizeof(float));
    if (a->ptr == NULL){
        return 2;
    }

    a->size = 0;
    a->capacity = N;

    return 0;
}

int array_create_struct_float(struct array_t **a, int N) {

    if (N <= 0 || a == NULL) return 1;

    *a = malloc(sizeof(struct array_t));
    if (*a == NULL) return 2;

    int result = array_create_float(*a, N);
    if (result != 0)
    {
        free(*a);
        *a = NULL;
    }

    return result;
}

int add_vectors(const struct array_t *a, const struct array_t *b, struct array_t **c) {
    if (a == NULL || b == NULL || c == NULL || a->capacity <= 0 || b->capacity <= 0
        || a->ptr == NULL || b->ptr == NULL || a->size > a->capacity || b->size > b->capacity) return 1;

    if (a->size != b->size) return 1;


    *c = malloc(sizeof(struct array_t));
    if (*c == NULL)
    {
        array_destroy_struct_float(c);
        return 2;
    }

    (*c)->ptr = malloc(a->size * sizeof(float));
    if ((*c)->ptr == NULL)
    {
        array_destroy_struct_float(c);
        return 2;
    }


    (*c)->size = a->size;
    (*c)->capacity = a->size;

    for (int i = 0; i < a->size; i++)
    {
        *((*c)->ptr + i) = *(a->ptr + i) + *(b->ptr + i);
    }

    return 0;
}

int subtract_vectors(const struct array_t *a, const struct array_t *b, struct array_t **c) {
    if (a == NULL || b == NULL || c == NULL || a->capacity <= 0
        || b->capacity <= 0|| a->ptr == NULL || b->ptr == NULL
        || a->size > a->capacity || b->size > b->capacity || a->size != b->size) return 1;


    *c = (struct array_t*)malloc(sizeof(struct array_t));
    if (*c == NULL){
        array_destroy_struct_float(c);
        return 2;
    }


    (*c)->ptr = malloc(a->size * sizeof(float));
    if ((*c)->ptr == NULL)
    {
        array_destroy_struct_float(c);
        return 2;
    }

    (*c)->size = a->size;
    (*c)->capacity = a->size;

    for (int i = 0; i < a->size; i++)
    {
        *((*c)->ptr + i) = *(a->ptr + i) - *(b->ptr + i);
    }

    return 0;
}

float dot_product(const struct array_t *a, const struct array_t *b) {
    if (a == NULL || b == NULL || a->capacity <= 0
        || b->capacity <= 0|| a->ptr == NULL || b->ptr == NULL
        || a->size > a->capacity || b->size > b->capacity || a->size != b->size) return -1;

    float result = 0.0;

    for (int i = 0; i < a->size; i++)
    {
        result += *(a->ptr + i) * *(b->ptr + i);
    }

    return result;
}

float length(const struct array_t *a) {
    if (a == NULL || a->ptr == NULL || a->size <= 0 || a->capacity <= 0 || a->size > a->capacity) return -1;

    float sum_squares = 0.0;

    for (int i = 0; i < a->size; i++)
    {
        sum_squares += *(a->ptr + i) * *(a->ptr + i);
    }


    return sqrtf(sum_squares);
}

float angle_between_vectors(const struct array_t *a, const struct array_t *b) {
    if (a == NULL || b == NULL || a->capacity <= 0
        || b->capacity <= 0|| a->ptr == NULL || b->ptr == NULL
        || a->size > a->capacity || b->size > b->capacity || a->size != b->size) return -1;

    if (a->size != b->size) return -1;

    int containsOnlyZeros = 1;
    const float *ptr_a = a->ptr;
    const float *ptr_b = b->ptr;

    for (int i = 0; i < a->size; i++) {
        if (*ptr_a != 0.0) {
            containsOnlyZeros = 0;
            break;
        }
        ptr_a++;
    }

    if (containsOnlyZeros) return -1;

    containsOnlyZeros = 1;

    for (int i = 0; i < b->size; i++) {
        if (*ptr_b != 0.0) {
            containsOnlyZeros = 0;
            break;
        }
        ptr_b++;
    }

    if (containsOnlyZeros) return -1;

    float dot = dot_product(a, b);
    float length_a = length(a);
    float length_b = length(b);

    if (length_a == 0.0 || length_b == 0.0) return 0.0;

    float cos_theta = dot / (length_a * length_b);
    float radian_angle = acosf(cos_theta);
    float degree_angle = radian_angle * RAD_TO_DEG;
    return degree_angle;
}

int normalize_vector(const struct array_t *a, struct array_t **b) {
    if (a == NULL || a->ptr == NULL || a->size <= 0 || a->capacity <= 0 || a->size > a->capacity || b == NULL) return 1;

    *b = (struct array_t*)malloc(sizeof(struct array_t));
    if (*b == NULL) return 2;


    (*b)->ptr = malloc(a->size * sizeof(float));
    if ((*b)->ptr == NULL)
    {
        free(*b);
        *b = NULL;
        return 2;
    }


    (*b)->size = a->size;

    (*b)->capacity = a->size;
    float length_a = length(a);

    if (length_a == 0.0){
        free((*b)->ptr);
        free(*b);
        return 3;
    }


    for (int i = 0; i < a->size; i++) {
        *((*b)->ptr + i) = *(a->ptr + i) / length_a;
    }

    return 0;
}

