#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"

INIT_ARRAY(int)
INIT_ARRAY(double)

int main(void)
{
    int data_type;
    char* filename = (char*)malloc(sizeof(char) * 31);
    if (!filename)
    {
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Enter filename: ");
    if (!scanf(" %30[^\n]", filename))
    {
        free(filename);
        printf("Incorrect input");
        return 1;
    }

    printf("Choose your type: ");
    if (!scanf("%d", &data_type))
    {
        free(filename);
        printf("Incorrect input");
        return 1;
    }
    if (data_type != 0 && data_type != 1)
    {
        free(filename);
        printf("Incorrect input data");
        return 2;
    }

    if (data_type == 0)
    {
        struct array_int_t* p;
        switch (load_array_int(&p, filename))
        {
            case 1:
                free(filename);
                printf("Incorrect input");
                return 1;
            case 2:
                free(filename);
                printf("Couldn't open file");
                return 4;
            case 3:
                free(filename);
                printf("File corrupted");
                return 6;
            case 4:
                free(filename);
                printf("Failed to allocate memory");
                return 8;
        }

        if (sort_array_int(p))
        {
            free_array_int(p);
            free(filename);
            printf("Incorrect input");
            return 1;
        }
        switch (save_array_int(p, filename))
        {
            case 1:
                free_array_int(p);
                free(filename);
                printf("Incorrect input");
                return 1;
            case 2:
                free_array_int(p);
                free(filename);
                printf("Couldn't create file");
                return 5;
        }
        printf("File saved");
        free_array_int(p);
        free(filename);
    }
    else
    {

        struct array_double_t* p;
        switch (load_array_double(&p, filename))
        {
            case 1:
                free(filename);
                printf("Incorrect input");
                return 1;
            case 2:
                free(filename);
                printf("Couldn't open file");
                return 4;
            case 3:
                free(filename);
                printf("File corrupted");
                return 6;
            case 4:
                free(filename);
                printf("Failed to allocate memory");
                return 8;
        }

        if (sort_array_double(p))
        {
            free_array_double(p);
            free(filename);
            printf("Incorrect input");
            return 1;
        }
        switch (save_array_double(p, filename))
        {
            case 1:
                free_array_double(p);
                free(filename);
                printf("Incorrect input");
                return 1;
            case 2:
                free_array_double(p);
                free(filename);
                printf("Couldn't create file");
                return 5;
        }
        printf("File saved");
        free_array_double(p);
        free(filename);
    }
    return 0;
}
