#ifndef INC_5_8_IMAGE_UTILS_H
#define INC_5_8_IMAGE_UTILS_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct point_t {
    int x;
    int y;
};

struct image_t {
    char type[3];
    int **ptr;
    int width;
    int height;
};

struct rectangle_t{
    struct point_t p;
    int width;
    int height;
};

struct image_t* load_image_t(const char *filename, int *err_code);
int save_image_t(const char * filename, const struct image_t *m1);
void destroy_image(struct image_t **m);
const int* image_get_pixel(const struct image_t *img, int x, int y);
int* image_set_pixel(struct image_t *img, int x, int y);
int image_draw_rectangle(struct image_t *img, const struct rectangle_t *rect, int value);

#endif
