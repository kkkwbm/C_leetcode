#include "defs.h"
#include <stdio.h>

int main() {
    struct tournament_t **tournaments;
    int result = read_tournaments("data.txt", &tournaments);

    if (result == 2)
    {
        printf("Couldn't open file\n");
        return 4;
    }
    else if (result == 3)
    {
        printf("File corrupted\n");
        return 6;
    }
    else if (result == 4)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    display_tournaments(tournaments);
    free_tournaments(tournaments);

    return 0;
}
