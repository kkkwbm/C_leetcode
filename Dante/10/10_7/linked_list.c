#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"

struct linked_list_t* ll_create()
{
    struct linked_list_t *list = malloc(sizeof(struct linked_list_t));
    if (list == NULL) return NULL;

    list->head = NULL;
    list->tail = NULL;
    return list;
}

int ll_push_back(struct linked_list_t* ll, int value)
{
    if (ll == NULL) return 1;

    struct node_t *node = malloc(sizeof(struct node_t));
    if (node == NULL) return 2;

    node->data = value;
    node->next = NULL;

    if (ll->head == NULL)
    {
        ll->head = node;
        ll->tail = node;
    }
    else
    {
        ll->tail->next = node;
        ll->tail = node;
    }

    return 0;
}

int ll_push_front(struct linked_list_t* ll, int value)
{
    if (ll == NULL) return 1;

    struct node_t *node = malloc(sizeof(struct node_t));
    if (node == NULL) return 2;

    node->data = value;
    node->next = ll->head;

    if (ll->head == NULL) ll->tail = node;

    ll->head = node;
    return 0;
}

int ll_pop_front(struct linked_list_t* ll, int *err_code)
{
    if (ll == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }

    if (ll->head == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }

    int value = ll->head->data;
    struct node_t *temp = ll->head;
    ll->head = ll->head->next;

    if (ll->head == NULL) ll->tail = NULL;

    free(temp);
    if (err_code) *err_code = 0;
    return value;
}

int ll_pop_back(struct linked_list_t* ll, int *err_code)
{
    if (ll == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }

    if (ll->head == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }

    int value;
    if (ll->head == ll->tail)
    {
        value = ll->head->data;
        free(ll->head);
        ll->head = NULL;
        ll->tail = NULL;
    }
    else
    {
        struct node_t *prev = ll->head;
        while (prev->next != ll->tail)
        {
            prev = prev->next;
        }

        value = ll->tail->data;
        free(ll->tail);
        ll->tail = prev;
        ll->tail->next = NULL;
    }

    if (err_code) *err_code = 0;
    return value;
}

int ll_back(const struct linked_list_t* ll, int *err_code)
{
    if (ll == NULL || ll->head == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }

    if (err_code)  *err_code = 0;
    return ll->tail->data;
}

int ll_front(const struct linked_list_t* ll, int *err_code)
{
    if (ll == NULL || ll->head == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }

    if (err_code)  *err_code = 0;
    return ll->head->data;
}

struct node_t* ll_begin(struct linked_list_t* ll)
{
    if (ll == NULL) return NULL;

    return ll->head;
}

struct node_t* ll_end(struct linked_list_t* ll)
{
    if (ll == NULL) return NULL;

    return ll->tail;
}

int ll_size(const struct linked_list_t* ll)
{
    if (ll == NULL) return -1;

    int size = 0;
    struct node_t* current = ll->head;
    while (current)
    {
        size++;
        current = current->next;
    }

    return size;
}

int ll_is_empty(const struct linked_list_t* ll)
{
    if (ll == NULL) return -1;
    return ll->head == NULL ? 1 : 0;
}

int ll_at(const struct linked_list_t* ll, unsigned int index, int *err_code) {
    if (ll == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }

    struct node_t* temp = ll->head;
    unsigned int i = 0;

    while (temp && i < index)
    {
        temp = temp->next;
        i++;
    }

    if (temp == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }

    if (err_code) *err_code = 0;
    return temp->data;
}

int ll_insert(struct linked_list_t* ll, unsigned int index, int value) {
    if (ll == NULL) return 1;

    if (index == 0) return ll_push_front(ll, value);

    struct node_t* newNode = (struct node_t*)malloc(sizeof(struct node_t));
    if (newNode == NULL) return 2;

    newNode->data = value;
    newNode->next = NULL;

    struct node_t* temp = ll->head;
    unsigned int i = 1;

    while (temp && i < index)
    {
        temp = temp->next;
        i++;
    }

    if (temp == NULL)
    {
        free(newNode);
        return 1;
    }

    newNode->next = temp->next;
    temp->next = newNode;

    if (newNode->next == NULL) ll->tail = newNode;

    return 0;
}

int ll_remove(struct linked_list_t* ll, unsigned int index, int *err_code) {
    if (ll == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }

    if (index == 0) return ll_pop_front(ll, err_code);

    struct node_t* temp = ll->head;
    unsigned int i = 1;

    while (temp && i < index)
    {
        temp = temp->next;
        i++;
    }

    if (temp == NULL || temp->next == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }

    struct node_t* toDelete = temp->next;
    int value = toDelete->data;

    temp->next = toDelete->next;

    if (temp->next == NULL) ll->tail = temp;

    free(toDelete);
    if (err_code) *err_code = 0;

    return value;
}

void ll_clear(struct linked_list_t* ll) {
    if (ll == NULL) return;

    struct node_t* temp;

    while (ll->head)
    {
        temp = ll->head;
        ll->head = ll->head->next;
        free(temp);
    }

    ll->tail = NULL;
}

void ll_display(const struct linked_list_t* ll) {
    if (ll == NULL) return;
    if (ll->head == NULL && ll->tail == NULL) return;

    struct node_t* temp = ll->head;

    while (temp)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}




