#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "doubly_linked_list.h"
#include "tested_declarations.h"
#include "rdebug.h"

struct doubly_linked_list_t* dll_create(){
    struct doubly_linked_list_t * list = (struct doubly_linked_list_t *)malloc(sizeof(struct doubly_linked_list_t));
    if(!list) return NULL;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

int dll_push_back(struct doubly_linked_list_t* dll, int value){
    if(dll == NULL) return 1;

    struct node_t *node = malloc(sizeof(struct node_t));
    if (node == NULL) return 2;

    node->data = value;
    node->prev = dll->tail;
    node->next = NULL;

    if (dll->tail ) dll->tail->next = node;

    dll->tail = node;

    if (dll->head == NULL) dll->head = node;

    return 0;
}

int dll_size(const struct doubly_linked_list_t* dll){
    if(dll == NULL) return -1;

    int size = 0;
    for (struct node_t * i = dll->head; i  ; i = i->next) size++;

    return size;
}

int dll_is_empty(const struct doubly_linked_list_t* dll) {
    if (dll == NULL) return -1;

    if (dll->head == NULL) return 1;
    else return 0;
}

void dll_clear(struct doubly_linked_list_t* dll){
    if (dll == NULL) return;

    struct node_t *prev;
    struct node_t *node = dll->head;

    while (node )
    {
        prev = node;
        node = node->next;
        free(prev);
    }

    dll->head = NULL;
    dll->tail = NULL;
}

void dll_display(const struct doubly_linked_list_t* dll){
    if (dll == NULL) return;

    struct node_t *node = dll->head;
    if(node == NULL) return;

    while (node )
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void dll_display_reverse(const struct doubly_linked_list_t* dll){
    if (dll == NULL) return;

    struct node_t *node = dll->tail;
    if(node == NULL) return;

    while (node )
    {
        printf("%d ", node->data);
        node = node->prev;
    }
    printf("\n");
}

static void dll_insert_after(struct doubly_linked_list_t* dll, struct node_t* prev_node, struct node_t* new_node) {
    new_node->next = prev_node->next;
    new_node->prev = prev_node;

    if (prev_node->next != NULL) prev_node->next->prev = new_node;
    else dll->tail = new_node;
    prev_node->next = new_node;
}

int dll_sort_asc(struct doubly_linked_list_t* dll) {
    if (dll == NULL || dll->head == NULL) return 1;
    if (dll->head->next == NULL) return 0;

    struct node_t *current = dll->head->next;
    while (current != NULL)
    {
        struct node_t *prev = current->prev;
        struct node_t *next = current->next;

        if (current->data < prev->data)
        {
            prev->next = current->next;

            if (next != NULL) next->prev = prev;
            else dll->tail = prev;

            struct node_t *temp = prev;
            while (temp != NULL && temp->data > current->data) temp = temp->prev;

            if (temp == NULL)
            {
                current->next = dll->head;
                current->prev = NULL;
                dll->head->prev = current;
                dll->head = current;
            }
            else dll_insert_after(dll, temp, current);
        }
        current = next;
    }

    return 0;
}

int dll_sort_desc(struct doubly_linked_list_t* dll) {
    if (dll == NULL || dll->head == NULL) return 1;
    if (dll->head->next == NULL) return 0;

    struct node_t *current = dll->head->next;
    while (current != NULL)
    {
        struct node_t *prev = current->prev;
        struct node_t *next = current->next;

        if (current->data > prev->data)
        {
            prev->next = current->next;

            if (next != NULL) next->prev = prev;
            else dll->tail = prev;

            struct node_t *temp = prev;
            while (temp != NULL && temp->data < current->data) temp = temp->prev;
            if (temp == NULL)
            {
                current->next = dll->head;
                current->prev = NULL;
                dll->head->prev = current;
                dll->head = current;
            }
            else dll_insert_after(dll, temp, current);
        }
        current = next;
    }

    return 0;
}

