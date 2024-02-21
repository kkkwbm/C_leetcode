#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node_t {
    struct node_t *next;
    void *data;
};

struct list_t {
    struct node_t *head;
    size_t data_size;
    //int(*compare)(const void*, const void*);
};
int linked_list_node_create(struct node_t **node, const void *data, size_t data_size){
    if(node == NULL || data == NULL || data_size <= 0) return 1;

    *node = malloc(sizeof (struct node_t));
    if(*node == NULL) return 2;

    (*node)->next = NULL;
    (*node)->data = malloc(data_size);
    if((*node)->data == NULL)
    {
        free(*node);
        return 2;
    }

    memcpy((*node)->data, data, data_size);

    return 0;
}
int linked_list_create(struct list_t ** list, size_t size){
    if(list == NULL || size <= 0) return 1;

    (*list) = malloc(sizeof (struct list_t));
    if(*list == NULL) return 2;

    (*list)->head = NULL;
    (*list)->data_size = size;

    return 0;
}
int linked_list_node_destroy(struct node_t **node){
    if(node == NULL || *node == NULL) return 1;

    free((*node)->data);
    free(*node);
    *node = NULL;

    return 0;
}
int linked_list_destroy(struct list_t **list){
    if(list == NULL || *list == NULL) return 1;

    struct node_t *temp = (*list)->head;
    while (temp != NULL)
    {
        struct node_t *temp2 = temp->next;
        linked_list_node_destroy(&temp);
        temp = temp2;
    }
    free(*list);
    *list = NULL;

    return 0;
}
int linked_list_push_back(struct list_t *list, const void *data){
    if (list == NULL || data == NULL) return 1;

    if(list->head == NULL)
    {
        if(linked_list_node_create(&list->head, data, list->data_size) == 2) return 2;
        return 0;
    }
    struct node_t *temp = list->head;

    while (temp->next != NULL) temp = temp->next;

    if(linked_list_node_create(&temp->next, data, list->data_size) == 2) return 2;

    return 0;
}

int linked_list_print(const struct list_t *list, int (*print_data)(FILE *, const void *)){
    if(list == NULL || print_data == NULL) return 1;

    struct node_t *temp = list->head;
    while (temp != NULL)
    {
        print_data(stdout, temp->data);
        temp = temp->next;
    }
    printf("\n");

    return 0;
}
void print_int(FILE *out, const void *data){
    if(data == NULL || out == NULL) return;

    fprintf(out, "%d ", *(int*)data);
}

int linked_list_pop_back(struct list_t *list) {
    if (list == NULL || list->head == NULL) return 1;

    struct node_t *temp = list->head;

    if (temp->next == NULL)
    {
        linked_list_node_destroy(&list->head);
        return 0;
    }

    while (temp->next->next != NULL) temp = temp->next;

    linked_list_node_destroy(&temp->next);
    temp->next = NULL;

    return 0;
}

int linked_list_pop_front(struct list_t *list) {
    if (list == NULL || list->head == NULL) return 1;

    struct node_t *temp = list->head;
    list->head = list->head->next;
    linked_list_node_destroy(&temp);

    return 0;
}

int linked_list_push_front(struct list_t *list, const void *data) {
    if (list == NULL || data == NULL) return 1;

    struct node_t *new_node;
    if (linked_list_node_create(&new_node, data, list->data_size) != 0) return 2;

    new_node->next = list->head;
    list->head = new_node;

    return 0;
}

int main()
{
    struct list_t *list;
    linked_list_create(&list, sizeof (int));
    for (int i = 0; i < 5; i++)
    {
        linked_list_push_back(list, &i);
        linked_list_print(list, print_int);
    }

    return 0;
}