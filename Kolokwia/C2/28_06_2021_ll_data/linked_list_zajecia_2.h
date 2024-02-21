#pragma once

typedef char* string;
#define CREATE_DISPLAY(TYPE, FORMAT)                      \
    void display_##TYPE(const void *data) {               \
        printf(#FORMAT,*((TYPE*)data));                   \
    }


enum data_type_t{
    data_type_uint32 = 1,
    data_type_float = 2,
    data_type_double = 3,
    data_type_string = 4
};

struct node_t{
    struct node_t *next;
    void *data;
    enum data_type_t type;
};
struct list_t{
    struct node_t *head;
};

int linked_list_create(struct list_t **);
int linked_list_destroy(struct list_t **);
int linked_list_node_create(struct node_t **node, enum data_type_t type, const void *data);
int linked_list_node_destroy(struct node_t **node);
int linked_list_push_front(struct list_t *list, enum data_type_t type, const void *data);
void linked_list_display(const struct list_t *list);