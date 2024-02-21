#include "defs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

CREATE_CALCULATE_BITS(char)


int insert(struct node_t **head, const char *word) {
    if (head == NULL || word == NULL) return 1;

    struct node_t *new_node = (struct node_t *)malloc(sizeof(struct node_t));
    if (new_node == NULL) return 2;

    new_node->word = strdup(word);
    if (new_node->word == NULL)
    {
        free(new_node);
        return 2;
    }

    new_node->bits = 0;
    for (char *p = new_node->word; *p; p++)
    {
        new_node->bits += calculate_bits_char(*p);
    }

    if (*head == NULL || strcmp((*head)->word, word) > 0)
    {
        new_node->next = *head;
        *head = new_node;
    }
    else
    {
        struct node_t *current = *head;
        while (current->next != NULL && strcmp(current->next->word, word) < 0)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }

    return 0;
}

void clear(struct node_t **head) {
    if (head == NULL || *head == NULL) return;

    struct node_t *current = *head;
    while (current != NULL)
    {
        struct node_t *next = current->next;
        free(current->word);
        free(current);
        current = next;
    }

    *head = NULL;
}

int reverse(struct node_t **head) {
    if (head == NULL || *head == NULL) return 1;

    struct node_t *prev = NULL;
    struct node_t *current = *head;
    while (current != NULL)
    {
        struct node_t *next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;

    return 0;
}