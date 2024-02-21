#ifndef DEFS_H
#define DEFS_H

#include <stdlib.h>

typedef struct products_t {
    char *product_name;
    unsigned int price;
} products_t;

typedef struct categories_t {
    char *name;
    struct products_t *products;
    unsigned int count;
} categories_t;

int read_categories(const char *filename, struct categories_t ***categories);
void display_categories(struct categories_t **categories);
void free_categories(struct categories_t **categories);

#endif