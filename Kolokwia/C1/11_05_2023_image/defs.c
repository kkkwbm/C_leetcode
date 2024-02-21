#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

enum error_code_t read_image(uint8_t **pimg, int *pwidth, int *pheight, const char *fname) {
    if (pimg == NULL || pwidth == NULL || pheight == NULL || fname == NULL) return ERROR_CODE_INCORRECT_PARAMETERS;

    FILE *file = fopen(fname, "r");
    if (file == NULL) return ERROR_CODE_FILE_NOT_EXISTS;

    char one, two;
    if (fscanf(file, "%c%c\n", &one, &two) != 2 || one != 'P' || two != '2') {
        fclose(file);
        return 5;
    }

    if (fscanf(file, "%d %d", pwidth, pheight) != 2)
    {
        fclose(file);
        return 6;
    }

    int max_val;
    if (fscanf(file, "%d", &max_val) != 1 || max_val > 255)
    {
        fclose(file);
        return 7;
    }

    *pimg = malloc((*pwidth) * (*pheight) * sizeof(uint8_t));
    if (*pimg == NULL)
    {
        fclose(file);
        return ERROR_CODE_FAILED_TO_ALLOCATE_MEMORY;
    }

    for (int i = 0; i < (*pwidth) * (*pheight); ++i)
    {
        if (fscanf(file, "%hhu", (*pimg) + i) != 1)
        {
            free(*pimg);
            fclose(file);
            return ERROR_CODE_FILE_CORRUPTED;
        }
    }

    fclose(file);
    return ERROR_CODE_OK;
}

void show_array(const uint8_t *img, int width, int height) {
    if (img == NULL) return;

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            printf("%03d ", *(img + i * width + j));
        }
        printf("\n");
    }
}

enum error_code_t encode_array(struct rle_t **out, int *n, const uint8_t *img, int width, int height) {
    if (img == NULL || out == NULL || n == NULL || width <= 0 || height <= 0) return ERROR_CODE_INCORRECT_PARAMETERS;

    *n = 0;
    *out = NULL;

    for (int i = 0; i < width * height; ++i)
    {
        int run_len = 1;
        while (i + 1 < width * height && *(img + i) == *(img + i + 1))
        {
            ++run_len;
            ++i;
        }

        struct rle_t *temp = realloc(*out, (*n + 1) * sizeof(struct rle_t));
        if (temp == NULL)
        {
            free(*out);
            *out = NULL;
            return ERROR_CODE_FAILED_TO_ALLOCATE_MEMORY;
        }

        *out = temp;
        (*((*out) + (*n))).val = *(img + i);
        (*((*out) + (*n))).len = run_len;
        (*n)++;
    }
    return ERROR_CODE_OK;
}