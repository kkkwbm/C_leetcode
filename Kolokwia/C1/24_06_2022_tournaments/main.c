#include <stdio.h>
#include "defs.h"

int main() {
    struct tournament_t *tournaments = NULL;
    int size = read_tournaments("fetch.txt", &tournaments);

    if (size < 0)
    {
        switch (size)
        {
            case -1:
                printf("Invalid data provided\n");
                return 1;
            case -2:
                printf("Couldn't open file\n");
                return 4;
            case -3:
                printf("File corrupted\n");
                return 6;
            case -4:
                printf("Failed to allocate memory\n");
                return 8;
            default:
                printf("Error!\n");
        }
    }

    display_tournaments(tournaments, size);
    free_tournaments(tournaments, size);

    return 0;
}
