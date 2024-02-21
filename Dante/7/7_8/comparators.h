//
// Created by Bartosz on 21.06.2023.
//

#ifndef INC_7_8_COMPARATORS_H
#define INC_7_8_COMPARATORS_H

#include <stddef.h>

struct point_t
{
    double x;
    double y;
};

int comp_int(const void *ptr1, const void *ptr2);
int comp_double(const void *ptr1, const void *ptr2);
int comp_point(const void *ptr1, const void *ptr2);
int sort(void *array, size_t n_items, size_t size, int (*comparator)(const void *, const void *));


#endif //INC_7_8_COMPARATORS_H
