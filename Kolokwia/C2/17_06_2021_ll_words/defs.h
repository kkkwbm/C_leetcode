#ifndef DEFS_H
#define DEFS_H

#include <stdlib.h>
#include <stdint.h>

#define CREATE_CALCULATE_BITS(TYPE)                \
uint8_t calculate_bits_##TYPE(TYPE value) {        \
    uint8_t count = 0;                             \
    for (size_t i = 0; i < sizeof(TYPE) * 8; i++)  \
    {                                              \
        if ((value >> i) & 1) count++;             \
    }                                              \
    return count;                                  \
}                                                  \

struct node_t {
    char* word;
    uint8_t bits;
    struct node_t *next;
};

int insert(struct node_t **head, const char *word);
int reverse(struct node_t **head);
void clear(struct node_t **head);

#endif