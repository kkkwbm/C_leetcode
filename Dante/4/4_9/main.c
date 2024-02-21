#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "array.h"

int main() {
    int size_a, size_b;
    printf("Podaj rozmiar tablicy: ");
    if (scanf("%d", &size_a) != 1)
    {
        printf("Incorrect input\n");
        return 1;
    }
    if (size_a <= 0 || size_a > 100)
    {
        printf("Incorrect input data\n");
        return 2;
    }

    struct array_t* vector_a = malloc(sizeof(struct array_t));

    if (vector_a == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }

    if (array_create_float(vector_a, size_a) != 0)
    {
        printf("Failed to allocate memory");
        array_destroy_struct_float(&vector_a);
        return 8;
    }

    printf("Podaj liczby: ");
    for (int i = 0; i < size_a; i++)
    {
        if (scanf("%f", vector_a->ptr + i) != 1)
        {
            printf("Incorrect input\n");
            array_destroy_struct_float(&vector_a);
            return 1;
        }
        vector_a->size++;
    }

    // printf("\n Rozmiar tablicy 1 %d \n", sizeof(vector_a));

    printf("Podaj rozmiar drugiej tablicy: ");
    if (scanf("%d", &size_b) != 1)
    {
        printf("Incorrect input\n");
        array_destroy_struct_float(&vector_a);
        return 1;
    }
    if (size_b <= 0 || size_b > 100)
    {
        printf("Incorrect input data\n");
        array_destroy_struct_float(&vector_a);
        return 2;
    }

    struct array_t* vector_b = malloc(sizeof(struct array_t));
    if (vector_b == NULL)
    {
        printf("Failed to allocate memory");
        array_destroy_struct_float(&vector_a);
        array_destroy_struct_float(&vector_b);
        return 8;
    }

    if (array_create_float(vector_b, size_b) != 0)
    {
        printf("Failed to allocate memory");
        array_destroy_struct_float(&vector_a);
        array_destroy_struct_float(&vector_b);
        return 8;
    }

    printf("Podaj liczby: ");
    for (int i = 0; i < size_b; i++)
    {
        if (scanf("%f", vector_b->ptr + i) != 1)
        {
            printf("Incorrect input\n");
            array_destroy_struct_float(&vector_a);
            array_destroy_struct_float(&vector_b);
            return 1;
        }
        vector_b->size++;
    }

    int containsOnlyZeros_a = 1;
    int containsOnlyZeros_b = 1;
    float *ptr_a_sum = vector_a->ptr;
    float *ptr_b_sum = vector_b->ptr;

    for (int i = 0; i < vector_a->size; i++)
    {
        if (*ptr_a_sum != 0.0) {
            containsOnlyZeros_a = 0;
            break;
        }
        ptr_a_sum++;
    }

    for (int i = 0; i < vector_b->size; i++)
    {
        if (*ptr_b_sum != 0.0) {
            containsOnlyZeros_b = 0;
            break;
        }
        ptr_b_sum++;
    }

    struct array_t* sum = NULL;

    //printf("Size of A vector %d, and capacity %d \n", vector_a->size, vector_a->capacity);
    //printf("Size of B vector %d, and capacity %d \n", vector_b->size, vector_b->capacity);
    int result = add_vectors(vector_a, vector_b, &sum);
    if(result == 2)
    {
        printf("Failed to allocate memory\n");
        array_destroy_struct_float(&vector_a);
        array_destroy_struct_float(&vector_b);
        array_destroy_float(sum);
        free(sum);
        return 8;
    }
    else if (result == 1)
    {
        printf("Operation not permitted\n");
        array_destroy_float(sum);
        free(sum);
    }
    else if(result == 0)
    {
        array_display_float(sum);
        array_destroy_float(sum);
        free(sum);
    }


    struct array_t* difference = NULL;

    result = subtract_vectors(vector_a, vector_b, &difference);
    if (result == 1)
    {
        printf("Operation not permitted\n");
        array_destroy_float(difference);
        free(difference);
    }
    else if(result == 2)
    {
        printf("Failed to allocate memory\n");
        array_destroy_struct_float(&vector_a);
        array_destroy_struct_float(&vector_b);
        array_destroy_float(difference);
        free(difference);
        return 8;
    }
    else if(result == 0)
    {
        // printf("RĂłĹźnica wprowadzonych wektorĂłw:\n");
        // printf("diff: ");
        array_display_float(difference);
        array_destroy_float(difference);
        free(difference);
    }


    float dot = dot_product(vector_a, vector_b);
    if (dot == INFINITY || dot == -INFINITY || isnan(dot) || dot == -1)
    {
        printf("Operation not permitted\n");
    }
    else
    {
        //printf("dot: ");
        printf(" %.2f\n", dot);
    }

    float angle = angle_between_vectors(vector_a, vector_b);
    if (angle == INFINITY || angle == -INFINITY || isnan(angle) || angle == -1)
    {
        printf("Operation not permitted\n");
    }
    else if(containsOnlyZeros_a || containsOnlyZeros_b)
    {
        printf("Operation not permitted\n");
    }
    else
    {
        //printf("angle: ");
        printf("%.2f\n", angle);
    }

    float len_a = length(vector_a);
    if (len_a == INFINITY || len_a == -INFINITY || isnan(len_a))
    {
        printf("Operation not permitted\n");
    }
    else
    {
        //printf("a len: ");
        printf("%.2f\n", len_a);
    }

    float len_b = length(vector_b);
    if (len_b == INFINITY || len_b == -INFINITY || isnan(len_b))
    {
        printf("Operation not permitted\n");
    }
    else
    {
        //printf("b len: ");
        printf("%.2f\n", len_b);
    }

    struct array_t* normalized_a = NULL;
    result = normalize_vector(vector_a, &normalized_a);
    if (result == 2)
    {
        printf("Failed to allocate memory\n");
        array_destroy_struct_float(&vector_a);
        array_destroy_struct_float(&vector_b);
        array_destroy_float(normalized_a);
        free(normalized_a);
        return 8;
    }
    else if(result == 3)
    {
        printf("Operation not permitted\n");
    }
    else if(result == 1)
    {
        printf("Operation not permitted\n");
        array_destroy_float(normalized_a);
        free(normalized_a);
    }
    else if(result == 0)
    {
        // printf("Znormalizowany wektor a:\n");
        //printf("a norm: ");
        array_display_float(normalized_a);
        array_destroy_float(normalized_a);
        free(normalized_a);
    }

    struct array_t* normalized_b = NULL;
    result = normalize_vector(vector_b, &normalized_b);
    if (result == 2)
    {
        printf("Failed to allocate memory");
        array_destroy_struct_float(&vector_a);
        array_destroy_struct_float(&vector_b);
        array_destroy_float(normalized_b);
        free(normalized_b);
        return 8;
    }
    else if(result == 3)
    {
        printf("Operation not permitted");
    }
    else if(result == 1)
    {
        printf("Operation not permitted");
        array_destroy_float(normalized_b);
        free(normalized_b);
    }
    else if(result == 0)
    {
        // printf("Znormalizowany wektor b:\n");
       //printf("b norm: ");
        array_display_float(normalized_b);
        array_destroy_float(normalized_b);
        free(normalized_b);
    }

    array_destroy_struct_float(&vector_a);
    array_destroy_struct_float(&vector_b);

    return 0;
}
