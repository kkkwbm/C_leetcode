#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct node_t* find_or_create_node(struct list_t *list, const char *word);
static uint8_t calculate_bit_counts(const char *word);

int list_load_file(struct list_t **list, const char *filename) {
    if (list == NULL) return 1;

    FILE *file = fopen(filename, "r");
    if (!file) return 2;

    if (*list == NULL)
    {
        *list = malloc(sizeof(struct list_t));
        if (*list == NULL)
        {
            fclose(file);
            return 3;
        }
        (*list)->head = NULL;
    }

    char text[21];
    while (fscanf(file, "%20s", text) == 1)
    {
        struct node_t *node = find_or_create_node(*list, text);
        if (!node)
        {
            fclose(file);
            return 3;
        }
        node->word->counter++;
        node->word->bit_counts = calculate_bit_counts(node->word->word);
    }

    fclose(file);
    return 0;
}

void list_free(struct list_t *list) {
    if (list == NULL) return;

    struct node_t *current = list->head;
    while (current != NULL)
    {
        struct node_t *temp = current;
        current = current->next;
        free(temp->word->word);
        free(temp->word);
        free(temp);
    }

    free(list);
}

void list_display(const struct list_t *list) {
    if (list == NULL) return;

    struct node_t *current = list->head;
    while (current != NULL)
    {
        printf("%s %d %d\n", current->word->word, current->word->counter, current->word->bit_counts);
        current = current->next;
    }
}

static struct node_t* find_or_create_node(struct list_t *list, const char *word) {
    struct node_t *current = list->head;
    struct node_t *prev = NULL;

    while (current != NULL)
    {
        if (strcmp(current->word->word, word) == 0)
        {
            return current;
        }
        prev = current;
        current = current->next;
    }


    struct node_t *newNode = malloc(sizeof(struct node_t));
    if (newNode == NULL) return NULL;

    newNode->word = malloc(sizeof(struct word_t));
    if (newNode->word == NULL)
    {
        free(newNode);
        return NULL;
    }


    newNode->word->word = strdup(word);
    if (newNode->word->word == NULL)
    {
        free(newNode->word);
        free(newNode);
        return NULL;
    }


    newNode->word->counter = 0;
    newNode->word->bit_counts = 0;
    newNode->next = NULL;


    if (prev == NULL)
    {
        list->head = newNode;
    }
    else
    {
        prev->next = newNode;
    }

    return newNode;
}

static uint8_t calculate_bit_counts(const char *word) {
    uint8_t bit_counts = 0;
    while (*word)
    {
        bit_counts += count_max_ones_distance_char(*word++);
    }
    return bit_counts;
}