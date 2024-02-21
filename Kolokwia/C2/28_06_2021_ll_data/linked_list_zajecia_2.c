//
// Created by G on 28.06.2021.
//

#include "linked_list_zajecia_2.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

CREATE_DISPLAY(uint32_t, %u)

CREATE_DISPLAY(float,%f)

CREATE_DISPLAY(double,%lf)

CREATE_DISPLAY(string,%s)

int linked_list_create(struct list_t **ll){
    if(!ll) return 1;
    *ll = calloc(1, sizeof(struct list_t));
    if(!*ll) return 2;
    return 0;
}
int linked_list_destroy(struct list_t** list){
    if(!list || !*list) return 1;
    struct node_t *curr = (*list)->head;
    struct node_t *temp = 0;
    while(curr)
    {
        temp = curr;
        curr = curr->next;
        linked_list_node_destroy(&temp);
    }
    free(*list);
    return 0;
}
int linked_list_node_create(struct node_t **node, enum data_type_t type, const void *data){
    if(!node || type < 1 || type > 4 || !data) return 1;
    *node = calloc(1, sizeof(struct node_t));
    if(!*node) return 2;
    void *copy;
    int size = 0;
    switch(type){
        case data_type_uint32:{
            size = sizeof(int);
            break;
        }
        case data_type_float:{
            size = sizeof(float);
            break;
        }
        case data_type_double:{
            size = sizeof(double);
            break;
        }
        case data_type_string:{
            size = strlen((char*)data)+1;
            break;
        }
    }
    copy = malloc(size);
    if(!copy) return free(*node),2;
    memcpy(copy, data,size);
    (*node)->data = copy;
    (*node)->type = type;
    return 0;
}
int linked_list_node_destroy(struct node_t **node){
    if(!node || !*node) return 1;
    free((*node)->data);
    free(*node);
    return 0;
}
int linked_list_push_front(struct list_t *list, enum data_type_t type, const void *data){
    if(!list ||type<1||type>4||!data) return 1;
    struct node_t *node = NULL;
    if(linked_list_node_create(&node,type,data)==2) return 2;
    node->next = list->head;
    list->head = node;
    return 0;
}
void linked_list_display(const struct list_t *list){
    if(!list) return;
    struct node_t *curr = list->head;
    while(curr){
        switch(curr->type){
            case data_type_uint32:
                display_uint32_t(curr->data);
                break;
            case data_type_float:
                display_float(curr->data);
                break;
            case data_type_double:
                display_double(curr->data);
                break;
            case data_type_string:
                display_string(&curr->data);
                break;
        }
        printf(" ");
        curr=curr->next;
    }
}