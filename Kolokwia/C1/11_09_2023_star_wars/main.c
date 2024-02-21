#include "defs.h"
#include <stdio.h>

int main() {
    struct categories_t **categories;
    int result = read_categories("star_wars.txt", &categories);

    switch (result) {
        case 0:
            display_categories(categories);
            break;
        case 1:
            printf("Invalid parameters.\n");
            return 1;
        case 2:
            printf("Couldn't open file\n");
            return 4;
        case 3:
            printf("File corrupted\n");
            return 6;
        case 4:
            printf("Failed to allocate memory\n");
            return 8;
        default:
            printf("Unknown error\n");
            return 9;
    }

    free_categories(categories);
    return 0;
}