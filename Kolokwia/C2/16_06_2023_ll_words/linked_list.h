//
// Created by Bartosz on 02.07.2023.
//

#ifndef KOLOKWIUM_C2___16_06_2023_LINKED_LIST_H
#define KOLOKWIUM_C2___16_06_2023_LINKED_LIST_H


#include <stdint.h>

struct node_t {
    char* word_en;
    char* word_pl;
    uint8_t bits;
    struct node_t *next;
};

int insert(struct node_t **head, const char *word_en, const char *word_pl);
int reverse(struct node_t **head);
void clear(struct node_t **head);


#endif //KOLOKWIUM_C2___16_06_2023_LINKED_LIST_H
