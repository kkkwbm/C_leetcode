#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_utils.h"
#include "tested_declarations.h"
#include "rdebug.h"

int main() {

    char *filename1 = (char*)malloc(20 * sizeof(char));
    if (!filename1)
    {
        printf("Failed to allocate memory\n");
        free(filename1);
        return 8;
    }

    printf("Podaj nazwę pierwszego pliku: ");
    scanf("%19s", filename1);
    while(getchar() != '\n');

    char *extension = strrchr(filename1, '.');

    if (extension == NULL || (strcmp(extension, ".txt") != 0 && strcmp(extension, ".bin") != 0))
    {
        printf("Unsupported file format\n");
        free(filename1);
        return 7;
    }


    int err_code;

    struct matrix_t *matrix1 = strstr(filename1, ".txt") ?
                               matrix_load_t(filename1, &err_code) :
                               matrix_load_b(filename1, &err_code);



    switch (err_code) {
        case 2:
            printf("Couldn't open file\n");
            free(filename1);
            matrix_destroy_struct(&matrix1);
            return 4;
        case 3:
            printf("File corrupted\n");
            free(filename1);
            matrix_destroy_struct(&matrix1);
            return 6;
        case 4:
            printf("Failed to allocate memory\n");
            free(filename1);
            matrix_destroy_struct(&matrix1);
            return 8;
    }

    free(filename1);

    char *filename2 = (char*)malloc(20 * sizeof(char));
    printf("Podaj nazwę drugiego pliku: ");
    scanf("%19s", filename2);
    while(getchar() != '\n');

    char *extension2 = strrchr(filename2, '.');

    if (extension2 == NULL || (strcmp(extension2, ".txt") != 0 && strcmp(extension2, ".bin") != 0))
    {
        printf("Unsupported file format\n");
        matrix_destroy_struct(&matrix1);
        free(filename2);
        return 7;
    }

    struct matrix_t *matrix2 = strstr(filename2, ".txt") ?
                               matrix_load_t(filename2, &err_code) :
                               matrix_load_b(filename2, &err_code);



    switch (err_code) {
        case 2:
            printf("Couldn't open file\n");
            matrix_destroy_struct(&matrix1);
            matrix_destroy_struct(&matrix2);
            free(filename2);
            return 4;
        case 3:
            printf("File corrupted\n");
            matrix_destroy_struct(&matrix1);
            matrix_destroy_struct(&matrix2);
            free(filename2);
            return 6;
        case 4:
            printf("Failed to allocate memory\n");
            matrix_destroy_struct(&matrix1);
            matrix_destroy_struct(&matrix2);
            free(filename2);
            return 8;
    }


    free(filename2);


    struct matrix_t *add_result = matrix_add(matrix1, matrix2);
    struct matrix_t *sub_result = matrix_subtract(matrix1, matrix2);
    struct matrix_t *mul_result = matrix_multiply(matrix1, matrix2);

    if (add_result)
    {
        matrix_display(add_result);
        matrix_destroy_struct(&add_result);
    }
    else printf("Error\n");

    if (sub_result)
    {
        matrix_display(sub_result);
        matrix_destroy_struct(&sub_result);
    }
    else printf("Error\n");

    if (mul_result)
    {
        matrix_display(mul_result);
        matrix_destroy_struct(&mul_result);
    }
    else printf("Error\n");

    matrix_destroy_struct(&matrix1);
    matrix_destroy_struct(&matrix2);

    return 0;
}


