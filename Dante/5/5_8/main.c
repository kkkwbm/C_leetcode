#include <stdio.h>
#include "image_utils.h"
#include "tested_declarations.h"
#include "rdebug.h"

void clearBuffer(){
  if(getchar()!='\n') clearBuffer();
}

int main() {
    char *filename = (char *)malloc(40 * sizeof(char));
    if (!filename)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Podaj nazwe: ");
    scanf("%39s", filename);
    void clearBuffer();

    int err_code;
    struct image_t *img = load_image_t(filename, &err_code);
    if(err_code == 2)
    {
        printf("Couldn't open file");
        free(filename);
        return 4;
    }
    if(err_code == 3)
    {
        printf("File corrupted");
        free(filename);
        return 6;
    }
    if(err_code == 4)
    {
        printf("Failed to allocate memory");
        free(filename);
        return 8;
    }

    int check_type_2 = strcmp(img->type, "P2");
    int check_type_5 = strcmp(img->type, "P5");
    if(check_type_2 != 0 && check_type_5 != 0)
    {
        printf("File corrupted\n");
        free(filename);
        destroy_image(&img);
        return 6;
    }


    struct rectangle_t rect;
    printf("Podaj wspolrzedne i wymiary prostokata: ");
    while(getchar() != '\n');
    if (scanf("%d %d %d %d", &rect.p.x, &rect.p.y, &rect.width, &rect.height) != 4)
    {
        printf("Incorrect input\n");
        destroy_image(&img);
        free(filename);
        return 1;
    }


    int color;
    printf("Podaj kolor: ");
    if (scanf("%d", &color) != 1)
    {
        printf("Incorrect input\n");
        destroy_image(&img);
        free(filename);
        return 1;
    }

    if(color < 0 || color > 255){
        printf("Incorrect input data\n");
        destroy_image(&img);
        free(filename);
        return 2;
    }

    if(rect.width <= 0 || rect.height <= 0)
    {
        printf("Incorrect input data\n");
        destroy_image(&img);
        free(filename);
        return 2;
    }

    if (image_draw_rectangle(img, &rect, color) != 0)
    {
        printf("Incorrect input data\n");
        destroy_image(&img);
        free(filename);
        return 2;
    }

    if (save_image_t(filename, img) != 0)
    {
        printf("Couldn't create file\n");
        destroy_image(&img);
        free(filename);
        return 5;
    }

    printf("File saved\n");

    destroy_image(&img);
    free(filename);
    return 0;
}

