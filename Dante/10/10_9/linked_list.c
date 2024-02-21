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

int ll_remove_sequence(struct linked_list_t* ll, const struct linked_list_t* ll_2) {
    if (!ll || !ll_2) return -1;
    if (!ll_2->head) return 0;

    struct node_t *curr = ll->head;
    struct node_t *prev = NULL;
    int sequencesRemoved = 0;

    while (curr)
    {
        struct node_t *patternNode = ll_2->head;
        struct node_t *tempCurr = curr;
        struct node_t *startOfMatch = curr;

        while (tempCurr && patternNode && tempCurr->data == patternNode->data)
        {
            tempCurr = tempCurr->next;
            patternNode = patternNode->next;
        }

        if (!patternNode)
        {
            sequencesRemoved++;
            while (curr != tempCurr)
            {
                struct node_t *next = curr->next;
                free(curr);
                curr = next;
            }

            if (prev) prev->next = curr;
            else ll->head = curr;

            if (!curr) ll->tail = prev;
        }
        else
        {
            prev = startOfMatch;
            curr = startOfMatch->next;
        }
    }

    return sequencesRemoved;
}






