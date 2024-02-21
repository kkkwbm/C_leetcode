#include <stdio.h>
#include <stdlib.h>
#include "tested_declarations.h"
#include "rdebug.h"

int create_array_2d_2(int ***ptr, int width, int height) {
    if (width <= 0 || height <= 0 || ptr == NULL) return 1;

    *ptr = (int **)malloc(height * sizeof(int*));
    if (*ptr == NULL) return 2;

    for (int i = 0; i < height; i++) {
        *(*ptr + i) = (int *)malloc(width * sizeof(int));
        if (*(*ptr + i) == NULL)
        {
            for (int j = 0; j < i; j++)
            {
                free(*(*ptr + j));
            }
            free(*ptr);
            return 2;
        }
    }
    return 0;
}

void destroy_array_2d(int ***ptr, int height) {
    if(height <= 0 || ptr == NULL || *ptr == NULL || **ptr == NULL) return;
    for (int i = 0; i < height; i++)
    {
        free(*(*ptr + i));
    }
    free(*ptr);
    *ptr = NULL;
}

void display_array_2d(int **ptr, int width, int height) {
    if(width <= 0 || height <= 0 || ptr == NULL || *ptr == NULL) return;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%d ", *((*(ptr + i)) + j));
        }
        printf("\n");
    }
}

int sum_row(int *ptr, int width) {
    if (ptr == NULL || width <= 0) return -1;

    int sum = 0;
    for (int i = 0; i < width; i++) sum += *(ptr + i);
    return sum;
}

int sum_array_2d(int **ptr, int width, int height) {
    if (width <= 0 || height <= 0 || ptr == NULL || *ptr == NULL) return -1;

    int total_sum = 0;
    for (int i = 0; i < height; i++)
    {
        total_sum += sum_row(*(ptr + i), width);
    }
    return total_sum;
}

int main() {
    int width;
    int height;

    printf("Podaj szerokość i wysokość: ");
    if (scanf("%d %d", &width, &height) != 2)
    {
        printf("Incorrect input\n");
        return 1;
    }
    if(width <= 0 || height <= 0)
    {
        printf("Incorrect input data \n");
        return 2;
    }


    int **tab;
    int result = create_array_2d_2(&tab, width, height);
    if (result == 1)
    {
        printf("Incorrect input data\n");
        return 2;
    }
    else if (result == 2)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Podaj liczby: ");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (scanf("%d", (*(tab + i) + j)) != 1)
            {
                destroy_array_2d(&tab, height);
                printf("Incorrect input\n");
                return 1;
            }
        }
    }

    display_array_2d(tab, width, height);

    for (int i = 0; i < height; i++)
    {
        printf("%d\n", sum_row(*(tab + i), width));
    }

    printf("%d\n", sum_array_2d(tab, width, height));

    destroy_array_2d(&tab, height);
    return 0;
}

