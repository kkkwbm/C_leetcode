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

int dll_push_front(struct doubly_linked_list_t* dll, int value) {
    if (dll == NULL) return 1;

    struct node_t* node = malloc(sizeof(struct node_t));
    if (node == NULL) return 2;

    node->data = value;
    node->prev = NULL;
    node->next = dll->head;

    if (dll->head ) dll->head->prev = node;

    dll->head = node;

    if (dll->tail == NULL) dll->tail = node;

    return 0;
}

int dll_pop_front(struct doubly_linked_list_t* dll, int *err_code)
{
    if (dll == NULL)
    {
        if(err_code ) *err_code = 1;
        return 0;
    }

    if (dll->head == NULL)
    {
        if(err_code ) *err_code = 1;
        return 0;
    }

    struct node_t* old_head = dll->head;
    int value = old_head->data;

    dll->head = old_head->next;

    if (dll->head ) dll->head->prev = NULL;
    else dll->tail = NULL;

    free(old_head);
    if (err_code) *err_code = 0;
    return value;
}

int dll_pop_back(struct doubly_linked_list_t* dll, int *err_code)
{
    if (dll == NULL)
    {
        if(err_code ) *err_code = 1;
        return 0;
    }

    if (dll->tail == NULL)
    {
        if(err_code ) *err_code = 1;
        return 0;
    }

    struct node_t* old_tail = dll->tail;
    int value = old_tail->data;

    dll->tail = old_tail->prev;

    if (dll->tail) dll->tail->next = NULL;
    else dll->head = NULL;

    free(old_tail);
    if (err_code) *err_code = 0;
    return value;
}

int dll_front(const struct doubly_linked_list_t* dll, int *err_code) {
    if (dll == NULL)
    {
        if (err_code ) *err_code = 1;
        return 0;
    }

    if (dll->head == NULL)
    {
        if (err_code ) *err_code = 1;
        return 0;
    }

    if (err_code ) *err_code = 0;
    return dll->head->data;
}

int dll_back(const struct doubly_linked_list_t* dll, int *err_code) {
    if (dll == NULL)
    {
        if (err_code ) *err_code = 1;
        return 0;
    }

    if (dll->tail == NULL)
    {
        if (err_code ) *err_code = 1;
        return 0;
    }

    if (err_code ) *err_code = 0;
    return dll->tail->data;
}

struct node_t* dll_begin(struct doubly_linked_list_t* dll) {
    if (dll == NULL || dll->head == NULL) return NULL;

    return dll->head;
}

struct node_t* dll_end(struct doubly_linked_list_t* dll){
    if (dll == NULL || dll->tail == NULL) return NULL;

    return dll->tail;
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

int dll_at(const struct doubly_linked_list_t* dll, unsigned int index, int *err_code) {
    if (dll == NULL)
    {
        if (err_code ) *err_code = 1;
        return 0;
    }

    struct node_t* current = dll->head;
    if(current == NULL) return 2;

    for (unsigned int i = 0; i < index; i++)
    {
        if (current == NULL)
        {
            if (err_code ) *err_code = 1;
            return 0;
        }
        current = current->next;
    }

    if (current == NULL)
    {
        if (err_code ) *err_code = 1;
        return 0;
    }

    if (err_code ) *err_code = 0;
    return current->data;
}

int dll_insert(struct doubly_linked_list_t* dll, unsigned int index, int value) {
    if (dll == NULL) return 1;

    unsigned int size = dll_size(dll);
    if(index > size) return 1;

    struct node_t* new_node = (struct node_t*)malloc(sizeof(struct node_t));
    if (new_node == NULL) return 2;

    new_node->data = value;
    new_node->prev = NULL;
    new_node->next = NULL;


    if (index == 0)
    {
        if (size == 0)
        {
            dll->head = new_node;
            dll->tail = new_node;
        }
        else
        {
            new_node->next = dll->head;
            dll->head->prev = new_node;
            dll->head = new_node;
        }
    }
    else if (index == size)
    {
        new_node->prev = dll->tail;
        dll->tail->next = new_node;
        dll->tail = new_node;
    }
    else
    {
        struct node_t* current = dll->head;
        unsigned int i = 0;

        while (i < index - 1)
        {
            current = current->next;
            i++;
        }

        new_node->prev = current;
        new_node->next = current->next;
        current->next->prev = new_node;
        current->next = new_node;
    }

    return 0;
}

int dll_remove(struct doubly_linked_list_t* dll, unsigned int index, int *err_code){
    if(dll == NULL)
    {
        if (err_code ) *err_code = 1;
        return 0;
    }

    struct node_t *current = dll->head;
    if(current == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }

    for(unsigned int i = 0; i < index && current; i++)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }

    int tmp = current->data;
    int is_memory_freed = 0;

    if(dll->head == dll->tail && index == 0)
    {
        free(dll->head);
        dll->head = NULL;
        dll->tail = NULL;
        is_memory_freed = 1;
    }
    else
    {
        if (current->prev) current->prev->next = current->next;
        if (current->next) current->next->prev = current->prev;
        if (dll->head == current) dll->head = current->next;
        if (dll->tail == current) dll->tail = current->prev;
    }

    if (!is_memory_freed) free(current);
    if (err_code) *err_code = 0;

    return tmp;
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
