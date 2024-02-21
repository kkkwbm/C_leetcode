#include "defs.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


int count_pixels(uint8_t **image, uint8_t **visited, int value, int height, int width, int y, int x)
{
    if (x < 0 || y < 0 || x >= width || y >= height
        || *(*(visited + y) + x) == 1 || *(*(image + y) + x) != value) return 0;

    *(*(visited + y) + x) = 1;
    int counter = 1;

    counter += count_pixels(image, visited, value, height, width, y - 1, x);
    counter += count_pixels(image, visited, value, height, width, y, x - 1);
    counter += count_pixels(image, visited, value, height, width, y + 1, x);
    counter += count_pixels(image, visited, value, height, width, y, x + 1);
    counter += count_pixels(image, visited, value, height, width, y - 1, x - 1);
    counter += count_pixels(image, visited, value, height, width, y - 1, x + 1);
    counter += count_pixels(image, visited, value, height, width, y + 1, x - 1);
    counter += count_pixels(image, visited, value, height, width, y + 1, x + 1);

    return counter;
}
void destroy(uint8_t **image, int height){
    if(image == NULL) return;

    for (int i = 0; i < height; i++)
    {
        free(*(image + i));
    }
    free(image);
}
void display(uint8_t **image, int height, int width){
    if(image == NULL) return;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%d ", *(*(image + i) + j));
        }
        printf("\n");
    }

}

struct img_t* load_image(const char* fname, enum error_code_t* errorCode){
    if(errorCode == NULL) return NULL;
    if(fname == NULL){
        *errorCode = ERROR_CODE_INCORRECT_PARAMETERS;
        return NULL;

    }

    FILE *file = fopen(fname, "rb");
    if(file == NULL){

        *errorCode = ERROR_CODE_FILE_NOT_EXISTS;
        return NULL;

    }

    struct img_t *img = malloc(sizeof(struct img_t));
    if(img == NULL){

        *errorCode = ERROR_CODE_FAILED_TO_ALLOCATE_MEMORY;
        fclose(file);
        return NULL;

    }

    char P;

    if(fread(&P, sizeof(char), 1, file) != (unsigned long long) 1){

        *errorCode = ERROR_CODE_FILE_CORRUPTED;
        free(img);
        fclose(file);
        return NULL;

    }

    if(P != 'P'){

        *errorCode = ERROR_CODE_FILE_CORRUPTED;
        free(img);
        fclose(file);
        return NULL;

    }

    if(fread(&P, sizeof(char), 1, file) != (unsigned long long) 1){

        *errorCode = ERROR_CODE_FILE_CORRUPTED;
        free(img);
        fclose(file);
        return NULL;

    }

    if(P != '2'){

        *errorCode = ERROR_CODE_FILE_CORRUPTED;
        free(img);
        fclose(file);
        return NULL;

    }

    int width = 0;
    int height = 0;

    if(fread(&width, sizeof(int), 1, file) != (unsigned long long) 1){

        *errorCode = ERROR_CODE_FILE_CORRUPTED;
        free(img);
        fclose(file);
        return NULL;

    }

    if(width <= 0){

        *errorCode = ERROR_CODE_FILE_CORRUPTED;
        free(img);
        fclose(file);
        return NULL;

    }

    if(fread(&height, sizeof(int), 1, file) != (unsigned long long) 1){

        *errorCode = ERROR_CODE_FILE_CORRUPTED;
        free(img);
        fclose(file);
        return NULL;

    }

    if(height <= 0){

        *errorCode = ERROR_CODE_FILE_CORRUPTED;
        free(img);
        fclose(file);
        return NULL;

    }

    uint8_t max_pixel = 0;
    if(fread(&max_pixel, sizeof(uint8_t), 1, file) != (unsigned long long)1){

        *errorCode = ERROR_CODE_FILE_CORRUPTED;
        free(img);
        fclose(file);
        return NULL;

    }

    img->width = width;
    img->height = height;

    uint8_t **image = calloc(height, sizeof(uint8_t *));
    if(image == NULL){

        *errorCode = ERROR_CODE_FAILED_TO_ALLOCATE_MEMORY;
        free(img);
        fclose(file);
        return NULL;

    }

    for (int i = 0; i < height; i++) {

        *(image + i) = calloc(width, sizeof(uint8_t));
        if(*(image + i) == NULL){

            destroy(image, height);
            fclose(file);
            free(img);
            *errorCode = ERROR_CODE_FAILED_TO_ALLOCATE_MEMORY;
            return NULL;

        }

    }

    for (int i = 0; i < height; ++i) {

        for (int j = 0; j < width; ++j) {

            uint8_t pixel = 0;
            if(fread(&pixel, sizeof(uint8_t), 1, file) != (unsigned long long)1){

                for (int k = 0; k < height; k++) free(*(image + k));
                *errorCode = ERROR_CODE_FILE_CORRUPTED;
                free(image);
                free(img);
                fclose(file);
                return NULL;

            }

            if(pixel > max_pixel){

                for (int k = 0; k < height; k++) free(*(image + k));
                *errorCode = ERROR_CODE_FILE_CORRUPTED;
                free(image);
                free(img);
                fclose(file);
                return NULL;

            }

            *(*(image + i) + j) = pixel;

        }

    }

    img->img = image;
    fclose(file);
    *errorCode = ERROR_CODE_OK;

    return img;
}

void destroy_img(struct img_t* input) {
    if (input == NULL) return;

    if (input->img != NULL)
    {
        for (int i = 0; i < input->height; i++)
        {
            free(*(input->img + i));
        }
        free(input->img);
    }
    free(input);
}

struct img_t* image_threshold(const struct img_t* input, enum error_code_t* errorCode) {
    if (input == NULL || input->img == NULL || input->height <= 0 || input->width <= 0 || errorCode == NULL)
    {
        if(errorCode) *errorCode = ERROR_CODE_INCORRECT_PARAMETERS;
        return NULL;
    }

    struct img_t* thresholded = (struct img_t*)calloc(1, sizeof(struct img_t));
    if (thresholded == NULL)
    {
        *errorCode = ERROR_CODE_FAILED_TO_ALLOCATE_MEMORY;
        return NULL;
    }

    thresholded->width = input->width;
    thresholded->height = input->height;
    thresholded->img = (uint8_t**)calloc(input->height, sizeof(uint8_t*));
    if (thresholded->img == NULL)
    {
        destroy_img(thresholded);
        *errorCode = ERROR_CODE_FAILED_TO_ALLOCATE_MEMORY;
        return NULL;
    }

    for (int i = 0; i < input->height; i++)
    {
        *(thresholded->img + i) = NULL;
    }

    long sum = 0;
    long total_pixels = input->width * input->height;
    for (int i = 0; i < input->height; i++)
    {
        for (int j = 0; j < input->width; j++)
        {
            sum += *(*(input->img + i) + j);
        }
    }
    uint8_t average_value = sum / total_pixels;

    for (int i = 0; i < input->height; i++)
    {
        *(thresholded->img + i) = (uint8_t*)calloc(input->width, sizeof(uint8_t));
        if (*(thresholded->img + i) == NULL)
        {
            destroy_img(thresholded);
            *errorCode = ERROR_CODE_FAILED_TO_ALLOCATE_MEMORY;
            return NULL;
        }

        for (int j = 0; j < input->width; j++)
        {
            *(*(thresholded->img + i) + j) = (*(*(input->img + i) + j) > average_value) ? 255 : 0;
        }
    }

    *errorCode = ERROR_CODE_OK;
    printf("OK");
    return thresholded;
}

int area_statistics(const struct img_t* input, struct area_t** areas, int* counter){
    if(input == NULL || counter == NULL) return 1;

    uint8_t **visited = calloc(input->height, sizeof(uint8_t *));
    if(visited == NULL) return 2;

    for (int i = 0; i < input->height; i++)
    {
        *(visited + i) = calloc(input->width, sizeof(uint8_t));
        if(*(visited + i) == NULL)
        {
            destroy(visited, input->height);
            free(visited);
            return 2;
        }

    }

    struct area_t *my_areas = NULL;
    int my_counter = 0;


    int size = 0;

    for(int i = 0; i < input->height; i++)
    {
        for(int j = 0; j < input->width; j++)
        {
            if(*(*(visited + i) + j) == 0)
            {
                size = count_pixels(input->img, visited, *(*(input->img + i) + j), input->height, input->width, i, j);
                struct area_t *temp = (struct area_t *)realloc(my_areas, (my_counter + 1) * sizeof(struct area_t));
                if(temp == NULL)
                {
                    destroy(visited, input->height);
                    free(areas);
                    return 2;
                }
                my_areas = temp;

                (my_areas + my_counter)->size = size;
                (my_areas + my_counter)->top_y = i;
                (my_areas + my_counter)->left_x = j;
                my_counter++;
                printf("%d %d %d %d\n", size, i, j, *(*(input->img + i) + j));
            }
        }
    }

    printf("MY AREAS\n");

    for(int i = 0; i < my_counter; i++)
    {
        printf("%d %d %d\n", (my_areas + i)->size, (my_areas + i)->top_y, (my_areas + i)->left_x);
    }

    *areas = my_areas;
    *counter = my_counter;

    return 0;
}
