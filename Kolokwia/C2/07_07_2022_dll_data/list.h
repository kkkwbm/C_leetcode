#ifndef KOLOKWIUM2_07_07_LIST_H
#define KOLOKWIUM2_07_07_LIST_H
#include <stdio.h>
enum type_t{
    INT,
    DBL,
    STR
};
struct list_t{
    struct node_t *head;
    struct node_t *tail;
    struct header_t *header;
};

struct header_t {
    unsigned  int size;
    enum type_t *types;
    char **names;
};

struct node_t {
    union val_t *vals;
    struct node_t *prev;
    struct node_t *next;
};

union val_t{
    int as_int;
    double as_double;
    char *as_str;
};



int read_header(struct header_t *head, FILE *fp);
int read_file(struct list_t **list, const char *fname);

void free_header(struct header_t *hd);
void free_list(struct list_t **list);

void display_list(const struct list_t *list);

void* aggregate_list(const struct list_t* list, const char* column_name, void(accumulate)(const void*, void*));
void accumulate_int(const void* cell_value, void* result);
void accumulate_double(const void* cell_value, void* result);
void accumulate_string(const void* cell_value, void* result);
#endif //KOLOKWIUM2_07_07_LIST_H