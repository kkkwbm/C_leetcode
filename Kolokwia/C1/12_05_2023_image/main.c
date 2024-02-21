#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "defs.h"



int main2() {
    enum error_code_t errorCode;

    // Step 1: Load the image from the "obrazek2.bin" file
    struct img_t* img = load_image("obrazek2.bin", &errorCode);
    if (errorCode != ERROR_CODE_OK) {
        printf("Failed to load the image. Error code: %d\n", errorCode);
        return -1;
    }

    // Step 2: Display the loaded image
    printf("Original Image:\n");
    display(img->img, img->height, img->width);

    // Step 3: Threshold the loaded image
    struct img_t* thresholded_img = image_threshold(img, &errorCode);
    if (errorCode != ERROR_CODE_OK) {
        printf("Failed to threshold the image. Error code: %d\n", errorCode);
        destroy_img(img);
        return -1;
    }

    // Step 4: Display the thresholded image
    printf("\nThresholded Image:\n");
    display(thresholded_img->img, thresholded_img->height, thresholded_img->width);

    // Step 5: Get the area statistics of the thresholded image
    struct area_t* areas = NULL;
    int counter = 0;
    int res = area_statistics(thresholded_img, &areas, &counter);
    if (res != 0) {
        printf("Failed to get area statistics. Error code: %d\n", res);
    } else {
        printf("\nArea Statistics:\n");
        for (int i = 0; i < counter; ++i) {
            printf("Area %d: Size = %d, Top Y = %d, Left X = %d\n", i, areas[i].size, areas[i].top_y, areas[i].left_x);
        }
        free(areas);
    }

    // Step 6: Free all allocated memory and close any opened files
    destroy_img(img);
    destroy_img(thresholded_img);

    return 0;
}
