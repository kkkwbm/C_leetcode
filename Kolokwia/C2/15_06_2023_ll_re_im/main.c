#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main(int argc, char* argv[]) {
    if (argc != 3)
    {
        printf("Wrong number of parameters\n");
        return -1;
    }

    enum order_t order;
    if (strcmp(argv[2], "front") == 0) order = FRONT;
    else if (strcmp(argv[2], "back") == 0) order = BACK;
    else
    {
        printf("Unknown value (second parameter)\n");
        return -2;
    }

    printf("STAGE 1\n");

    FILE* file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("File open error\n");
        return -3;
    }

    printf("STAGE 2\n");

    struct list_t* list = list_load_from_file(file, order);
    fclose(file);

    printf("STAGE 3\n");

    if (list == NULL)
    {
        printf("Failed to allocate memory\n");
        return -4;
    }

    printf("STAGE 4\n");


    list_print(list);
    printf("\n");

    list_clear(list);
    free(list);

    return 0;
}
