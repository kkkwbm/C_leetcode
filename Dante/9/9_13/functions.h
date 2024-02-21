#ifndef INC_9_13_FUNCTIONS_H
#define INC_9_13_FUNCTIONS_H

#include <stdio.h>

#define COUNT_BITS(value, set_counter_ptr, cleared_counter_ptr)\
do{\
    unsigned long mask = 1ULL << ((sizeof(value) * 8ULL) - 1ULL);\
    int set_counter = 0;\
    int cleared_counter = 0;\
    while(mask) \
    {\
        if(value & mask) ++set_counter;\
        else ++cleared_counter;\
        mask >>= 1ULL;\
    }\
    *(set_counter_ptr) = set_counter;\
    *(cleared_counter_ptr) = cleared_counter;\
} while(0)

#define DISPLAY_BITS(value)\
do{\
    unsigned long mask = 1ULL << ((sizeof(value) * 8ULL) - 1ULL);\
    while(mask)\
    {\
        printf((value & mask) ? "1" : "0");\
        mask >>= 1ULL;\
    }\
    printf("\n");\
} while(0)


#define REVERSE_BITS(pointer_to_variable){\
    int size = sizeof(*pointer_to_variable) * 8ULL;\
    long long unsigned int value = *pointer_to_variable;\
    *pointer_to_variable = 0ULL;\
    for(int i = 0ULL; i < size; i++)\
    {\
        if(value & 1ULL << i)\
        {\
            *pointer_to_variable += 1ULL << (size - i - 1ULL);\
        }\
    }\
}\

#endif //INC_9_13_FUNCTIONS_H
