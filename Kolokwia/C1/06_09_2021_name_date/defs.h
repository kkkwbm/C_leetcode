#ifndef DEFS_H
#define DEFS_H

#include <stdint.h>

typedef union date_t {
    struct {
        unsigned int d : 5;
        unsigned int m : 4;
        unsigned int y : 11;
    };
    uint32_t value;
} date_t;

typedef struct record_t {
    char name[21];
    date_t bdate;
    char surname[31];
} record_t;

int read(const char* fname, struct record_t* buffer, int count);
void show(const struct record_t* arr, int count);

#endif // DEFS_H