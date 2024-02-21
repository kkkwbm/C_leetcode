#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "defs.h"

void destroy(uint8_t **image, int height);
void display(uint8_t **image, int height, int width);
int count_pixels_v14(uint8_t **image, uint8_t **visited, int value, int height, int width, int y, int x);
int count_pixels_v4(uint8_t **image, uint8_t **visited, int value, int height, int width, int y, int x);
int count_pixels(uint8_t **image, uint8_t **visited, int value, int height, int width, int y, int x);
int count_pixels_v2(uint8_t **image, uint8_t **visited, int value, int height, int width, int y, int x, int id);
int size_of_area(uint8_t **image, int height, int width, int id);

int main() {

    uint8_t **image, **visited;

    FILE *f = fopen("test.txt", "rt");

    if (f == NULL) return 1;

    int height;
    int width;
    int res = fscanf(f, "%d %d", &height, &width);

    image = (uint8_t **)calloc(height, sizeof(uint8_t *));
    visited = (uint8_t **)calloc(height, sizeof(uint8_t *));

    if (image == NULL || visited == NULL)
    {
        free(image);
        free(visited);
        fclose(f);
        return 2;
    }

    for (int i = 0; i < height; ++i)
    {
        *(image + i) = (uint8_t *) calloc(width, sizeof (uint8_t));
        *(visited + i) = (uint8_t *) calloc(width, sizeof (uint8_t));
        if (*(image + i) == NULL || *(visited + i) == NULL)
        {
            destroy(image, height);
            destroy(visited, height);
            fclose(f);
            return 2;
        }
        for (int j = 0; j < width; ++j)
        {
            res = fscanf(f, "%hhu", (*(image + i) + j));
            if (res != 1)
            {
                destroy(image, height);
                fclose(f);
                return 3;
            }
        }

    }

    display(image, height, width);

    fclose(f);

    //int size;// = count_pixels(image, visited, 0, height, width, 0, 0);

    struct area_t *areas = NULL;
    int counter = 1;

//    for (int i = 0; i < height; ++i)
//        for (int j = 0; j < width; ++j)
//            if (*(*(visited + i) + j) == 0)
//            {
//                size = count_pixels(image, visited, *(*(image + i) + j), height, width, i, j);
//                struct area_t *temp = (struct  area_t *) realloc(areas, (counter + 1) * sizeof(struct area_t));
//                if (temp == NULL)
//                {
//                    destroy(image, height);
//                    destroy(visited, height);
//                    free(areas);
//                }
//                areas = temp;
//
//                (areas + counter)->size = size;
//                (areas + counter)->y = i;
//                (areas + counter)->x = j;
//                counter++;
//                printf("%d %d %d %d\n", size, i, j, *(*(image + i) + j));
//            }

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (*(*(visited + i) + j) == 0)
            {
                count_pixels_v2(image, visited, *(*(image + i) + j), height, width, i, j, counter++);
            }
        }
    }




    areas = (struct  area_t *) calloc(counter - 1, sizeof(struct area_t));
    if(areas == NULL)
    {
        destroy(image, height);
        fclose(f);
        return 3;
    }

    int flag = 1;
    for (int c = 1; c < counter; ++c, flag = 1)
    {
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                if (*(*(visited + i) + j) == c && flag)
                {
                    (areas + c - 1)->size = size_of_area(visited, height, width, c);
                    (areas + c - 1)->top_y = i;
                    (areas + c - 1)->left_x = j;
                    flag = 0;
                }
            }
        }
    }


    display(visited, height, width);

    for (int i = 0; i < counter - 1; ++i)
    {
        printf("%d %d %d\n", (areas + i)->size, (areas + i)->top_y, (areas + i)->left_x);
    }

    return 0;
}

void destroy(uint8_t **image, int height)
{
    if (image == NULL) return;

    for (int i = 0; i < height; ++i) free(*(image + i));

    free(image);
}

void display(uint8_t **image, int height, int width) {
    for (int i = 0; i < height; ++i, printf("\n"))
    {
        for (int j = 0; j < width; ++j)
        {
            printf("%d ", *(*(image + i) + j));
        }
    }
}

int count_pixels_v14(uint8_t **image, uint8_t **visited, int value, int height, int width, int y, int x)
{
    if (x < 0 || y < 0 || x >= width || y >= height) return 0;
    if (*(*(visited + y) + x) == 1) return 0;
    if (*(*(image + y) + x) != value) return 0;

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
