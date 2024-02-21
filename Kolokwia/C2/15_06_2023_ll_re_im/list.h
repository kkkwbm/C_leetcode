#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdint.h>

enum order_t {
    FRONT,
    BACK
};

struct complex_t {
    unsigned char re;
    unsigned char im;
    uint8_t crc;
};

struct node_t {
    struct node_t *next;
    struct complex_t data;
};

struct list_t {
    struct node_t *head;
};

void list_init(struct list_t *list);
struct node_t* list_create_element(unsigned char re, unsigned char im, uint8_t (*crc_function)(uint8_t));
int list_push_front(struct list_t *list, struct node_t *item);
int list_push_back(struct list_t *list, struct node_t *item);
int list_clear(struct list_t* list);
struct list_t* list_load_from_file(FILE* f, enum order_t order);
void list_print(const struct list_t* list);

#endif  // LIST_H
