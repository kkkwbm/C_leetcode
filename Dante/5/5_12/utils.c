#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "format_type.h"
#include "utils.h"
#include <ctype.h>
#include "tested_declarations.h"
#include "rdebug.h"


// Ile jest linii w pliku bin, zlicza ile jest wartości "-1" w plku
int rows_in_file_bin(FILE *fp)
{
    int count = 0;
    while(1)
    {
        int value;
        if(fread(&value, sizeof(int),1,fp) != 1) break;
        if(value == -1) count++;
    }
    return count;
}

int rows_in_file_txt(FILE *fp)
{
    int count = 0;
    while(1)
    {
        int value;
        if(fscanf(fp,"%d",&value) != 1) break;
        if(value == -1) count++;
    }
    return count;
}

// Sprawdza ile jest liczb w jednej linii dla pliku txt uwzgledniajac koncowe -1
int txt_size_of_line(FILE *fp)
{
    int pos = ftell(fp);
    int value = 0;
    int count = 0;
    while(fscanf(fp, "%d", &value))
    {
        count++;
        if(value == -1) break;
    }
    fseek(fp,pos,SEEK_SET);
    return count;
}

// Ile jest liczb w jednej linii dla pliku bin, uwzgledniajac koncowe -11
int bin_size_of_line(FILE *fp)
{
    int pos = ftell(fp);
    int value = 0;
    int count = 0;
    while(fread(&value, sizeof(int),1,fp))
    {
        count++;
        if(value == -1) break;
    }
    fseek(fp,pos,SEEK_SET);
    return count;
}

int validate(FILE *fp) {
    while (!feof(fp)) {
        char c = fgetc(fp);
        if(feof(fp)) break;
        if (isdigit(c)) continue;
        if (c == ' ') continue;
        if (c == '-') continue;
        if (c == '\n') continue;
        return 0;
    }
    return 1;
}
int load(const char *filename, int ***ptr, enum save_format_t format)
{
    if(filename == NULL || ptr == NULL) return 1;
    if(format != fmt_binary && format != fmt_text) return 1;

    FILE *fp;
    if(format == fmt_text) fp = fopen(filename, "r");
    else fp = fopen(filename, "rb");
    if(fp == NULL) return 2;


    if(!validate(fp) && format == fmt_text){
        fclose(fp);
        return 3;
    }

    rewind(fp);

    int rows_count =0;

    if(format == fmt_text) rows_count = rows_in_file_txt(fp);
    else rows_count = rows_in_file_bin(fp);

    if(rows_count < 1)
    {
        fclose(fp);
        return 3;
    }
    rewind(fp);

    *ptr = malloc((rows_count + 1) * sizeof(int *));
    if(*ptr == NULL)
    {
        fclose(fp);
        return 4;
    }

    int **numbers = *ptr;
    *(numbers + rows_count) = NULL;

    for(int i = 0; i < rows_count; i++)
    {
        int cols;
        if(format == fmt_text) cols = txt_size_of_line(fp);
        else cols = bin_size_of_line(fp);

        *(numbers + i) = malloc((cols) * sizeof(int));
        if(*(numbers + i) == NULL)
        {
            for(int k = 0; k < i; k++)
            {
                free(*(numbers + k));
            }
            free(numbers);
            *ptr = NULL;
            fclose(fp);
            return 4;
        }
        int *row = *(numbers + i);

        for(int j = 0; j < cols; j++)
        {

            if(format == fmt_text)
            {
                if(fscanf(fp,"%d",row + j) != 1)
                {
                    fclose(fp);
                    for(int k = 0; k <= i; k++)
                    {
                        free(*(numbers + k));
                    }
                    free(numbers);
                    *ptr = NULL;
                    return 3;
                }
            }
            else
            {
                if(fread(row + j,sizeof(int),1, fp) != 1)
                {
                    fclose(fp);
                    for(int k = 0; k <= i; k++)
                    {
                        free(*(numbers + k));
                    }
                    free(numbers);
                    *ptr = NULL;
                    return 3;
                }
            }
        }

    }

    fclose(fp);
    return 0;
}



int statistics_row(int **ptr, struct statistic_t **stats) {
    if (!ptr || !stats) return -1;

    int rows = 0;
    while (*(ptr + rows)) rows++;

    struct statistic_t *statistics = malloc(rows * sizeof(struct statistic_t));
    if (!statistics) return -2;

    for (int i = 0; i < rows; ++i) {
        int size = 0;
        while (*(*(ptr + i) + size) != -1) size++;

        if (size == 0) {
            *(statistics + i) = (struct statistic_t) {-1, -1, -1.0f, -1.0f, -1};
            continue;
        }

        (statistics + i)->min = *(*(ptr + i));
        (statistics + i)->max = *(*(ptr + i));
        float sum = 0.0f;

        for (int j = 0; j < size; ++j)
        {
            if (*(*(ptr + i) + j) < (statistics + i)->min) (statistics + i)->min = *(*(ptr + i) + j);
            if (*(*(ptr + i) + j) > (statistics + i)->max) (statistics + i)->max = *(*(ptr + i) + j);
            sum += *(*(ptr + i) + j);
        }

        (statistics + i)->avg = sum / size;
        (statistics + i)->range = (statistics + i)->max - (statistics + i)->min;

        float variance = 0.0f;
        for (int j = 0; j < size; ++j)
        {
            variance += (*(*(ptr + i) + j) - (statistics + i)->avg) * (*(*(ptr + i) + j) - (statistics + i)->avg);
        }
        variance /= size;

        (statistics + i)->standard_deviation = sqrt(variance);
    }

    *stats = statistics;
    return rows;
}

void destroy(int ***ptr) {
    if (!ptr || !*ptr) return;

    int **data = *ptr;
    int i = 0;
    while (*(data + i))
    {
        free(*(data + i));
        i++;
    }

    free(data);
    *ptr = NULL;
}

void display(int **ptr)
{
    if(ptr == NULL || *ptr == NULL) return;

    int i = 0 ;
    while(1)
    {
        if(*(ptr + i) == NULL) break;
        int j = 0;
        while(1)
        {
            if((*(*(ptr + i) + j)) == -1) break;
            printf("%d ",(*(*(ptr + i) + j)));
            j++;
        }
        printf("\n");
        i++;
    }
}

void display_old(int **ptr)
{
    if (!ptr) return;

    int i = 0;
    while (*(ptr + i)) {
        int j = 0;
        while (*(*(ptr + i) + j) != -1) {
            if (j > 0) printf(" ");
            printf("%d", *(*(ptr + i) + j));
            j++;
        }
        printf("\n");
        i++;
    }
}

