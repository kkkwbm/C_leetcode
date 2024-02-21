#include <stdio.h>
#include <stdlib.h>
#include "comparators.h"
#include "tested_declarations.h"
#include "rdebug.h"

void print_int_array(void *base, int size) {
    int *p = (int *)base;
    for (int i = 0; i < size; i++, p++) {
        printf("%d ", *p);
    }
    printf("\n");
}

void print_double_array(void *base, int size) {
    double *p = (double *)base;
    for (int i = 0; i < size; i++, p++) {
        printf("%.6f ", *p);
    }
    printf("\n");
}

void print_point_array(void *base, int size) {
    struct point_t *p = (struct point_t *)base;
    for (int i = 0; i < size; i++, p++) {
        printf("%.6f %.6f\n", p->x, p->y);
    }
}

int main() {
    int data_type;
    int n;
    void *data = NULL;

    printf("Enter data type: ");
    if (scanf("%d", &data_type) != 1) {
        printf("Incorrect input\n");
        return 1;
    }

    printf("Enter array size: ");
    if (scanf("%d", &n) != 1) {
        printf("Incorrect input\n");
        return 1;
    }
    if (n <= 0)
    {
        printf("Incorrect input data\n");
        return 2;
    }

    switch (data_type) {
        case 0:
            data = malloc(n * sizeof(int));
            if (!data) {
                printf("Failed to allocate memory\n");
                return 8;
            }
            printf("Enter ints: ");
            for (int i = 0; i < n; i++) {
                if (scanf("%d", ((int *)data + i)) != 1) {
                    free(data);
                    printf("Incorrect input\n");
                    return 1;
                }
            }
            sort(data, n, sizeof(int), comp_int);
            print_int_array(data, n);
            break;
        case 1:
            data = malloc(n * sizeof(double));
            if (!data) {
                printf("Failed to allocate memory\n");
                return 8;
            }
            printf("Enter doubles: ");
            for (int i = 0; i < n; i++) {
                if (scanf("%lf", ((double *)data + i)) != 1) {
                    free(data);
                    printf("Incorrect input\n");
                    return 1;
                }
            }
            sort(data, n, sizeof(double), comp_double);
            print_double_array(data, n);
            break;
        case 2:
            data = malloc(n * sizeof(struct point_t));
            if (!data) {
                printf("Failed to allocate memory\n");
                return 8;
            }
            printf("Enter points: ");
            for (int i = 0; i < n; i++) {
                if (scanf("%lf %lf", &(((struct point_t *)data + i)->x), &(((struct point_t *)data + i)->y)) != 2) {
                    free(data);
                    printf("Incorrect input\n");
                    return 1;
                }
            }
            sort(data, n, sizeof(struct point_t), comp_point);
            print_point_array(data, n);
            break;
        default:
            printf("Incorrect input\n");
            return 1;
    }

    free(data);
    return 0;
}

