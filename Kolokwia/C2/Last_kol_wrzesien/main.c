#include <stdio.h>
#include "defs.h"

CREATE_FUNCTION_COUNT_MAX_ONES_DISTANCE(char)

int main(int argc, char *argv[]) {
    printf("Result for 11110011001: %hhu should be 4 \n", count_max_ones_distance_char(0b11110011001ULL));
    printf("Result for 10111110001: %hhu should be 5 \n", count_max_ones_distance_char(0b10111110001ULL));
    printf("Result for 10101010101: %hhu should be 3 \n", count_max_ones_distance_char(0b10101010101ULL));
    printf("Result for 00000000011: %hhu should be 2 \n", count_max_ones_distance_char(0b00000000011ULL));
    printf("Result for 00000000110: %hhu should be 2 \n", count_max_ones_distance_char(0b00000000110ULL));
    printf("Result for 11100000011: %hhu should be 8 \n", count_max_ones_distance_char(0b11100000011ULL));
    printf("Result for 00000000000: %hhu should be 0 \n", count_max_ones_distance_char(0b00000000000ULL));


    if (argc < 2)
    {
        printf("Not enough arguments\n");
        return 9;
    }

    struct list_t *list = NULL;


    char **arg = argv + 1;
    for (int i = 1; i < argc; i++, arg++)
    {
        if (list_load_file(&list, *arg) != 0)
        {
            printf("Couldn't open file \"%s\"\n", *arg);
        }
    }

    list_display(list);
    list_free(list);

    return 0;
}
