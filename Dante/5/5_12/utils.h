#ifndef INC_5_12_UTILS_H
#define INC_5_12_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include "format_type.h"

struct statistic_t
{
    int min;
    int max;
    float avg;
    float standard_deviation;
    int range;
};


void display(int **ptr);
void destroy(int ***ptr);
int load(const char *filename, int ***ptr, enum save_format_t format);
int statistics_row(int **ptr, struct statistic_t **stats);

#endif //INC_5_12_UTILS_H