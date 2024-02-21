#ifndef LAST_KOL_WRZESIEN_DEFS_H
#define LAST_KOL_WRZESIEN_DEFS_H

#include <stdint.h>

#define CREATE_FUNCTION_COUNT_MAX_ONES_DISTANCE(typ) \
uint8_t count_max_ones_distance_##typ (typ a) {\
    uint8_t max_distance = 0;\
    uint8_t current_distance = 0;\
    uint8_t flag = 0;\
    for (unsigned int i = 0; i < sizeof(typ) * 8; i++)\
    {\
        if ((a >> i) & 1)\
        {\
            if (!flag)\
            {\
                flag = 1;\
                current_distance = 1;\
            }\
            else\
            {\
                current_distance++;\
            }\
        }\
        else if (flag)\
        {\
            if (current_distance > max_distance)\
            {\
                max_distance = current_distance;\
            }\
        }\
    }\
    return max_distance;\
}


#define CREATE_FUNCTION_COUNT_MAX_ONES_DISTANCE_2(typ) \
uint8_t count_max_ones_distance_2_##typ (typ a) {\
    uint8_t max_distance = 0;\
    uint8_t current_distance = 0;\
    uint8_t flag = 0;\
    for (unsigned int i = 0; i < sizeof(typ) * 8; i++)\
    {\
        if(((a >> i) & 1) == 1 && flag == 1)\
        { \
            current_distance++;\
            if(current_distance > max_distance) max_distance = current_distance;\
            current_distance = 1;\
            continue; \
        }\
        else if(((a >> i) & 1) == 1 && flag == 0)\
        {\
             current_distance = 1;\
             flag = 1;\
             continue;\
        }\
        else if(((a >> i) & 1) == 0 && flag == 1)\
        {\
            current_distance++;\
        }\
    }\
    return max_distance;\
}

struct word_t {
    char *word;
    uint8_t counter;
    uint8_t bit_counts;
};

struct node_t {
    struct word_t *word;
    struct node_t *next;
};

struct list_t {
    struct node_t *head;
};

int list_load_file(struct list_t **list, const char *filename);
void list_free(struct list_t *list);
void list_display(const struct list_t *list);

#endif //LAST_KOL_WRZESIEN_DEFS_H
