#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "format_type.h"
#include "utils.h"
#include "tested_declarations.h"
#include "rdebug.h"



int main() {
    char *filename = malloc(40 * sizeof(char));
    if (!filename)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Podaj nazwe pliku: ");
    scanf("%39s", filename);

    enum save_format_t format;
    if (strstr(filename, ".txt")) format = fmt_text;
    else if (strstr(filename, ".bin")) format = fmt_binary;
    else
    {
        printf("Unsupported file format\n");
        free(filename);
        return 7;
    }
    int len = strlen(filename);
    if (len < 4 ||
        (strcmp(filename + len - 4, ".txt") != 0 &&
         strcmp(filename + len - 4, ".bin") != 0))
    {
        printf("Unsupported file format\n");
        free(filename);
        return 7;
    }

    /*
    for(long unsigned int i = 0; i < strlen(filename); i++)
    {
        if(*(filename + i) == '.' && (*(filename + i + 1) == 't' || *(filename + i + 1 ) == 'b')
           && (*(filename + i + 2) == 'x' || *(filename + i + 2) == 'i')) break;

        *(filename_modified + i) = *(filename + i);
    }
     */

    int **data = NULL;
    int load_result = load(filename, &data, format);
    free(filename);

    switch (load_result)
    {
        case 1: return 1;
        case 2:
            printf("Couldn't open file\n");
            return 4;
        case 3:
            printf("File corrupted\n");
            return 6;
        case 4:
            printf("Failed to allocate memory\n");
            return 8;
    }

    struct statistic_t *statistics = NULL;
    int stats_result = statistics_row(data, &statistics);
    if (stats_result < 0)
    {
        printf("Failed to allocate memory\n");
        destroy(&data);
        return 8;
    }

    for (int i = 0; i < stats_result; ++i)
    {
        printf("%d %d %d %.2f %.2f\n", (statistics + i)->min, (statistics + i)->max, (statistics + i)->range, (statistics + i)->avg, (statistics + i)->standard_deviation);
    }

    free(statistics);
    destroy(&data);
    return 0;
}
