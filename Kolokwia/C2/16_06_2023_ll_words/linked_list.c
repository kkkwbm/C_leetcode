#include "linked_list.h"
#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "string.h"
#include <stdio.h>

CREATE_FUNCTION_COUNT01(char)


struct node_t *create_node(const char *word_en, const char *word_pl, uint8_t (*bits_function)(char)) {
    struct node_t *node = (struct node_t *) malloc(sizeof(struct node_t));
    if (node == NULL) return NULL;

    node->word_en = strdup(word_en);
    node->word_pl = strdup(word_pl);
    if (node->word_en == NULL || node->word_pl == NULL)
    {
        free(node->word_en);
        free(node->word_pl);
        free(node);
        return NULL;
    }

    node->bits = 0;
    char *letter = node->word_en;
    while (*letter != '\0')
    {
        node->bits += bits_function(*letter);
        letter++;
    }

    letter = node->word_pl;
    while (*letter != '\0')
    {
        node->bits += bits_function(*letter);
        letter++;
    }

    //node->bits = bits_function(*word_en) + bits_function(*word_pl);
    node->next = NULL;

    return node;
}

int insert(struct node_t **head, const char *word_en, const char *word_pl) {
    if (head == NULL || word_en == NULL || word_pl == NULL)return 1;

    struct node_t *node = create_node(word_en, word_pl, count01_char);
    if (node == NULL) return 2;

    struct node_t **tracer = head;
    while(*tracer != NULL && strcmp((*tracer)->word_en, node->word_en) < 0)
    {
        tracer = &((*tracer)->next);
    }
    node->next = *tracer;
    *tracer = node;

    return 0;
}

void clear(struct node_t **head) {
    if (head == NULL || *head == NULL) return;

    struct node_t *current_node = *head;
    struct node_t *next_node;

    while (current_node != NULL)
    {
        next_node = current_node->next;

        free(current_node->word_en);
        free(current_node->word_pl);
        free(current_node);

        current_node = next_node;
    }

    *head = NULL;
}

int reverse(struct node_t **head) {
    if (head == NULL || *head == NULL) return 1;

    struct node_t *prev_node = NULL;
    struct node_t *current_node = *head;
    struct node_t *next_node = NULL;

    while (current_node != NULL)
    {
        next_node = current_node->next;
        current_node->next = prev_node;
        prev_node = current_node;
        current_node = next_node;
    }

    *head = prev_node;

    return 0;
}



