#include "defs.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>



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

    uint8_t **image = malloc(height * sizeof(uint8_t *));
    if(image == NULL){

        *errorCode = ERROR_CODE_FAILED_TO_ALLOCATE_MEMORY;
        free(img);
        fclose(file);
        return NULL;

    }

    for (int i = 0; i < height; i++) {

        *(image + i) = malloc(width * sizeof(uint8_t));
        if(*(image + i) == NULL){

            for (int j = 0; j < i; j++) free(*(image + j));
            free(image);
            *errorCode = ERROR_CODE_FAILED_TO_ALLOCATE_MEMORY;
            free(img);
            fclose(file);
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

    if (input->img != NULL) {
        for (int i = 0; i < input->height; i++)
        {
            free(*(input->img + i));
        }
        free(input->img);
    }
    free(input);
}

struct img_t* image_threshold(const struct img_t* input, enum error_code_t* errorCode) {
    if (input == NULL || errorCode == NULL)
    {
        *errorCode = ERROR_CODE_INCORRECT_PARAMETERS;
        return NULL;
    }

    struct img_t* thresholded = (struct img_t*)malloc(sizeof(struct img_t));
    if (thresholded == NULL)
    {
        *errorCode = ERROR_CODE_FAILED_TO_ALLOCATE_MEMORY;
        return NULL;
    }

    thresholded->width = input->width;
    thresholded->height = input->height;
    thresholded->img = (uint8_t**)malloc(sizeof(uint8_t*) * input->height);
    if (thresholded->img == NULL)
    {
        free(thresholded);
        *errorCode = ERROR_CODE_FAILED_TO_ALLOCATE_MEMORY;
        return NULL;
    }

    for (int i = 0; i < input->height; i++)
    {
        *(thresholded->img + i) = (uint8_t*)malloc(sizeof(uint8_t) * input->width);
        if (*(thresholded->img + i) == NULL) {
            destroy_img(thresholded);
            *errorCode = ERROR_CODE_FAILED_TO_ALLOCATE_MEMORY;
            return NULL;
        }

        for (int j = 0; j < input->width; j++)
        {
            *(*(thresholded->img + i) + j) = (*(*(input->img + i) + j) > 127) ? 255 : 0;
        }
    }

    *errorCode = ERROR_CODE_OK;
    return thresholded;
}

int size_of_area(uint8_t **image, int height, int width, int id)
{
    int size = 0;

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if(*(*(image + i) + j) == id) size++;
        }
    }
    return size;
}


int count_pixels(uint8_t **image, uint8_t **visited, int value, int height, int width, int y, int x)
{
    if (x < 0 || y < 0 || x >= width || y >= height || *(*(visited + y) + x) == 1 || *(*(image + y) + x) != value) return 0;
    else
    {
        *(*(visited + y) + x) = 1;
        return 1 + count_pixels(image, visited, value, height, width, y - 1, x) +
               count_pixels(image, visited, value, height, width, y, x - 1) +
               count_pixels(image, visited, value, height, width, y + 1, x) +
               count_pixels(image, visited, value, height, width, y, x + 1) +
               count_pixels(image, visited, value, height, width, y - 1, x - 1) +
               count_pixels(image, visited, value, height, width, y - 1, x + 1) +
               count_pixels(image, visited, value, height, width, y + 1, x - 1) +
               count_pixels(image, visited, value, height, width, y + 1, x + 1);
    }

}

int count_pixels_v2(uint8_t **image, uint8_t **visited, int value, int height, int width, int y, int x, int id)
{
    if (x < 0 || y < 0 || x >= width || y >= height) return 0;
    if (*(*(visited + y) + x)) return 0;
    if (*(*(image + y) + x) != value) return 0;

    *(*(visited + y) + x) = id;
    int counter = 1;

    counter += count_pixels_v2(image, visited, value, height, width, y - 1, x, id);
    counter += count_pixels_v2(image, visited, value, height, width, y, x - 1, id);
    counter += count_pixels_v2(image, visited, value, height, width, y + 1, x, id);
    counter += count_pixels_v2(image, visited, value, height, width, y, x + 1, id);

    counter += count_pixels_v2(image, visited, value, height, width, y - 1, x - 1, id);
    counter += count_pixels_v2(image, visited, value, height, width, y - 1, x + 1, id);
    counter += count_pixels_v2(image, visited, value, height, width, y + 1, x - 1, id);
    counter += count_pixels_v2(image, visited, value, height, width, y + 1, x + 1, id);

    return counter;
}

void destroy(uint8_t **image, int height)
{
    if (image == NULL) return;

    for (int i = 0; i < height; ++i) free(*(image + i));

    free(image);
}
int valid_point(struct img_t *temp, int x, int y, int unused) {
    if (x < 0 || y < 0)return 0;
    if (x >= temp->width || y >= temp->height)return 0;
    if (*(*(temp->img + y) + x) == unused)return 0;
    return 1;
}



void solve(struct img_t *img, struct area_t *area, int unused, int startX, int startY, int lookForThis) {
    if (*(*(img->img + startY) + startX) == lookForThis) {
        if (area->top_y > startY && area->left_x > startX)area->top_y = startY, area->left_x = startX;
        area->size++;
        *(*(img->img + startY) + startX) = unused;


        //top
        if (valid_point(img, startX, startY - 1, unused))
            solve(img, area, unused, startX, startY - 1, lookForThis);
        //right top
        if (valid_point(img, startX + 1, startY - 1, unused))
            solve(img, area, unused, startX + 1, startY - 1, lookForThis);
        //right
        if (valid_point(img, startX + 1, startY, unused))
            solve(img, area, unused, startX + 1, startY, lookForThis);
        //right bot
        if (valid_point(img, startX + 1, startY + 1, unused))
            solve(img, area, unused, startX + 1, startY + 1, lookForThis);
        //bot
        if (valid_point(img, startX, startY + 1, unused))
            solve(img, area, unused, startX, startY + 1, lookForThis);
        //left bot
        if (valid_point(img, startX - 1, startY + 1, unused))
            solve(img, area, unused, startX - 1, startY + 1, lookForThis);
        //left
        if (valid_point(img, startX - 1, startY, unused))
            solve(img, area, unused, startX - 1, startY, lookForThis);
        //left top
        if (valid_point(img, startX - 1, startY - 1, unused))
            solve(img, area, unused, startX - 1, startY - 1, lookForThis);
    }
}

int find_unused_value(struct img_t *temp) {

    int found = 0;

    for (int i = 0; i < 256; i++) {
        for (int y = 0; y < temp->height; y++) {
            for (int x = 0; x < temp->width; x++) {
                if (*(*(temp->img + y) + x) == i) {
                    found = 1;
                    break;
                }
            }
            if (found)break;
        }
        if (!found)return i;
        found = 0;
    }


    return -1;
}

long long find_undone(struct img_t *temp, int unused, int *xs, int *ys) {
    for (int i = 0; i < 256; i++) {
        for (int y = 0; y < temp->height; y++) {
            for (int x = 0; x < temp->width; x++) {
                if (*(*(temp->img + y) + x) != unused) {
                    *xs = x;
                    *ys = y;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int area_statistics(const struct img_t *input, struct area_t **areas, int *counter) {
    if (input==NULL || areas==NULL || counter==NULL) {
        return -1;
    }

    struct img_t *temp = calloc(1,sizeof(struct img_t));
    if (temp==NULL) {
        *areas = NULL;
        return -2;
    }

    int height = input->height;
    int width = input->width;

    temp->img = calloc(height,sizeof(uint8_t *));
    if (temp->img==NULL) {
        free(temp);
        *areas = NULL;
        return -2;
    }

    for (int i = 0; i < height; i++) {
        *(temp->img + i) = calloc(1,width* sizeof(uint8_t));
        if (*(temp->img + i)==NULL) {
            for (int j = 0; j < i; j++) {
                free(*(temp->img + j));
            }
            free(temp->img);
            free(temp);
            *areas = NULL;
            return -2;
        }

    }


    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            *(*(temp->img + y) + x) = *(*(input->img + y) + x);
        }
    }

    temp->height = height;
    temp->width = width;


    int unusedValue = find_unused_value(temp);

    int xs, ys;

    *areas = NULL;
    void *tempPtr;
    *counter = 0;
    for (int i = 0; find_undone(temp, unusedValue, &xs, &ys); i++) {
        tempPtr = realloc(*areas, sizeof(struct area_t) * (i + 1));
        if (!tempPtr) {
            destroy_img(temp);
            free(*areas);
            *areas = NULL;
            return -2;
        } else *areas = tempPtr;

        ((*areas) + i)->left_x = width;
        ((*areas) + i)->top_y = height;
        ((*areas) + i)->size = 0;

        solve(temp, *areas + i, unusedValue, xs, ys, *(*(temp->img + ys) + xs));
        (*counter)++;
    }


    destroy_img(temp);
    return 0;
}

