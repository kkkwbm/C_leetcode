#include "image_utils.h"
#include "tested_declarations.h"
#include "rdebug.h"

struct image_t* load_txt(struct image_t* image, int *err_code, FILE* fp)
{
    if(err_code != NULL) *err_code = 0;
    if(fscanf(fp,"%d %d", &image->width,&image->height) != 2)
    {
        if(err_code != NULL) *err_code = 3;
        return NULL;
    }
    if(image->width <= 0 || image->height <= 0)
    {
        if(err_code != NULL) *err_code = 3;
        return NULL;
    }
    int max;
    if(fscanf(fp,"%d", &max) != 1 || max < 0)
    {
        if(err_code != NULL) *err_code = 3;
        return NULL;
    }
    image->ptr = calloc(image->height, sizeof(int *));
    if(image->ptr == NULL)
    {
        if(err_code != NULL) *err_code = 4;
        return NULL;
    }
    for (int h = 0; h < image->height; h++)
    {
        *(image->ptr + h) = calloc(image->width, sizeof(int));
        if(*(image->ptr + h) == NULL)
        {
            if(err_code != NULL) *err_code = 4;
            return NULL;
        }
        for(int w = 0; w < image->width; w++)
        {
            int num;
            if(fscanf(fp,"%d", &num) != 1)
            {
                if(err_code != NULL) *err_code = 3;
                return NULL;
            }
            if(num < 0 || num > 255)
            {
                if(err_code != NULL) *err_code = 3;
                return NULL;
            }
            *(*(image->ptr + h) + w) = num;
        }
    }
    return image;
}
struct image_t* load_bin(struct image_t* image,int *err_code,FILE *fp)
{
    if(err_code != NULL) *err_code = 0;
    if(fread(&image->width, sizeof(int),1,fp) != 1
       || fread(&image->height, sizeof(int),1,fp) != 1)
    {
        if(err_code != NULL) *err_code = 3;
        return NULL;
    }
    if(image->width <= 0 || image->height <= 0)
    {
        if(err_code != NULL) *err_code = 3;
        return NULL;
    }
    int max;
    if(fread(&max, sizeof(int), 1, fp) != 1 || max < 0)
    {
        if(err_code != NULL) *err_code = 3;
        return NULL;
    }
    image->ptr = calloc(image->height, sizeof(int *));
    if(image->ptr == NULL)
    {
        if(err_code != NULL) *err_code = 4;
        return NULL;
    }
    for (int h = 0; h < image->height; h++)
    {
        *(image->ptr + h) = calloc(image->width, sizeof(int));
        if(*(image->ptr + h) == NULL)
        {
            if(err_code != NULL) *err_code = 4;
            return NULL;
        }
        for(int w = 0; w < image->width; w++)
        {
            int num;
            if(fread(&num, sizeof(int),1,fp) != 1)
            {
                if(err_code != NULL) *err_code = 3;
                return NULL;
            }
            if(num < 0 || num > 255)
            {
                if(err_code != NULL) *err_code = 3;
                return NULL;
            }
            *(*(image->ptr + h) + w) = num;
        }
    }
    return image;
}

struct image_t* load_image_t(const char *filename, int *err_code)
{
    if(err_code != NULL) *err_code = 0;
    if(filename == NULL)
    {
        if(err_code != NULL) *err_code = 1;
        return NULL;
    }

    FILE *fp = fopen(filename,"r");
    if(fp == NULL)
    {
        if(err_code != NULL) *err_code = 2;
        return NULL;
    }

    struct image_t* image = calloc(1, sizeof(struct image_t));
    if(image == NULL)
    {
        if(err_code != NULL) *err_code = 4;
        free(image);
        fclose(fp);
        return NULL;
    }
    if(fscanf(fp,"%s", image->type) != 1)
    {
        if(err_code != NULL) *err_code = 3;
        fclose(fp);
        free(image);
        return NULL;
    }

    int result_p1 = strcmp(image->type, "P1");
    int result_p2 = strcmp(image->type, "P2");
    int result_p3 = strcmp(image->type, "P3");
    int result_p4 = strcmp(image->type, "P4");
    int result_p5 = strcmp(image->type, "P5");
    int result_p6 = strcmp(image->type, "P6");

    if(result_p1 != 0 && result_p2 != 0 && result_p3 != 0
       && result_p4 != 0 && result_p5 != 0 && result_p6 != 0)
    {
        if(err_code != NULL) *err_code = 3;
        free(image);
        fclose(fp);
        return NULL;
    }
    if(result_p1 == 0 || result_p2 == 0 || result_p3 == 0)
    {
        if(load_txt(image,err_code,fp)==NULL)
        {
            fclose(fp);
            destroy_image(&image);
            return NULL;
        }
    }
    else if(result_p4 == 0 || result_p5 == 0 || result_p6 == 0)
    {
        if(load_bin(image,err_code,fp)==NULL)
        {
            fclose(fp);
            destroy_image(&image);
            return NULL;
        }
    }
    fclose(fp);
    return image;
}


int save_image_text(const struct image_t *m1, FILE *fp)
{
    if(fprintf(fp,"%s\n", m1->type) == 0)
    {
        fclose(fp);
        return 3;
    }
    if(fprintf(fp,"%d %d\n", m1->width,m1->height) == 0)
    {
        fclose(fp);
        return 3;
    }
    int num_2 = 255;
    if(fprintf(fp,"%d\n", num_2) == 0)
    {
        fclose(fp);
        return 3;
    }
    for(int i = 0; i < m1->height; i++)
    {
        for(int j = 0; j < m1->width; j++)
        {
            int num = (*((*(m1->ptr + i) + j)));
            if(fprintf(fp,"%d ", num) == 0)
            {
                fclose(fp);
                return 3;
            }
        }
        if(fprintf(fp,"\n") == 0) return 3;
    }
    fclose(fp);
    return 0;
}

int save_image_bin(const struct image_t *m1, FILE *fp)
{
    if(fwrite(m1->type, sizeof(m1->type),1,fp) == 0)
    {
        fclose(fp);
        return 3;
    }
    if(fwrite(&m1->width, sizeof(m1->width),1,fp) == 0
       || fwrite(&m1->height, sizeof(m1->height),1,fp) == 0)
    {
        fclose(fp);
        return 3;
    }
    int num_2 = 255;
    if(fwrite(&num_2, sizeof(num_2),1,fp) == 0)
    {
        fclose(fp);
        return 3;
    }
    for(int i = 0; i < m1->height; i++)
    {
        for(int j = 0; j < m1->width; j++)
        {
            int num = (*((*(m1->ptr + i) + j)));
            if(fwrite(&num, sizeof(num),1,fp) == 0)
            {
                fclose(fp);
                return 3;
            }
        }
    }
    fclose(fp);
    return 0;
}


int save_image_t(const char * filename, const struct image_t * m1)
{
    if(filename == NULL || m1 == NULL || m1->width <= 0 || m1->height <= 0 || m1->ptr == NULL) return 1;

    int result_p1 = strcmp(m1->type, "P1");
    int result_p2 = strcmp(m1->type, "P2");
    int result_p3 = strcmp(m1->type, "P3");
    int result_p4 = strcmp(m1->type, "P4");
    int result_p5 = strcmp(m1->type, "P5");
    int result_p6 = strcmp(m1->type, "P6");

    if(result_p1 != 0 && result_p2 != 0 && result_p3 != 0
       && result_p4 != 0 && result_p5 != 0 && result_p6 != 0) return 1;

    FILE *fp = fopen(filename,"w");
    if(fp == NULL) return 2;

    if(result_p1 == 0 || result_p2 == 0 || result_p3 == 0) return save_image_text(m1,fp);
    else return save_image_bin(m1,fp);
}

void destroy_image(struct image_t **m)
{
    if(m == NULL || *m == NULL) return;
    else if ((*(m))->ptr != NULL)
    {
        for (int h = 0; h < (*(m))->height; h++)
        {
            if((*((*(m))->ptr + h)) == NULL) break;
            free((*((*(m))->ptr + h)));
        }
        free((*(m))->ptr);
    }
    free(*m);
    *m = NULL;
}

const int* image_get_pixel(const struct image_t *img, int x, int y)
{
    if(img == NULL || x < 0 || y < 0 || img->height <= 0 || img->width <= 0
       || img->ptr == NULL || y >= img->height || x >= img->width) return NULL;

    const int* num = &(*(*(img->ptr + y) + x));
    return num;
}
int* image_set_pixel(struct image_t *img, int x, int y)
{
    if(img == NULL || x < 0 || y < 0 || img->height <= 0 || img->width <= 0
       || img->ptr == NULL || y >= img->height || x >= img->width) return NULL;

    int* num = &(*(*(img->ptr + y) + x));
    return num;
}

int image_draw_rectangle(struct image_t *img, const struct rectangle_t *rect, int value) {
    if (img == NULL || img->ptr == NULL || img->height <= 0 || img->width <= 0 || rect == NULL || rect->height <= 0 || rect->width <= 0 || value < 0 || value > 255)
        return 1;

    if (rect->p.x < 0 || rect->p.y < 0 || rect->p.x + rect->width > img->width || rect->p.y + rect->height > img->height)
        return 1;

    for (int i = 0; i < rect->width; i++) {
        *(*(img->ptr + rect->p.y) + rect->p.x + i) = value;
        *(*(img->ptr + rect->p.y + rect->height - 1) + rect->p.x + i) = value;
    }

    for (int i = 0; i < rect->height; i++) {
        *(*(img->ptr + rect->p.y + i) + rect->p.x) = value;
        *(*(img->ptr + rect->p.y + i) + rect->p.x + rect->width - 1) = value;
    }

    return 0;
}




