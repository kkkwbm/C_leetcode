#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

int main()
{
    struct rle_t *rle = NULL;
    uint8_t *img = NULL;
    int p_width = 0;
    int p_height = 0;
    int * ptr_p_width = &p_width;
    int * ptr_p_height = &p_height;

    enum error_code_t err = read_image(&img, ptr_p_width, ptr_p_height, "obrazek1.pgm");

    if (err != ERROR_CODE_OK)
    {
        printf("Error reading image file: %d\n", err);
        return 1;
    }

    printf("Image dimensions: %d x %d\n", p_width, p_height);

    int n = 0;
    err = encode_array(&rle, &n, img, p_width, p_height);
    if (err != ERROR_CODE_OK)
    {
        printf("Error encoding pixel data: %d\n", err);
        free(img);
        return 1;
    }

    printf("Compressed data:\n");
    for (int i = 0; i < n; i++) {
        printf("%d %d\n", (rle->val + i), (rle->len + i));
    }

    printf("\nOriginal pixel data:\n");
    show_array(img, p_width, p_height);

    free(img);
    free(rle);

    return 0;
}
