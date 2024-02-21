#ifndef KOL_01_07_DEFS_H
#define KOL_01_07_DEFS_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


#define CREATE_FUNCTION_COUNT01(TYPE) \
TYPE count01_##TYPE(TYPE arg){        \
    TYPE count=0;                     \
    for(long unsigned int i=1;i<sizeof(TYPE)*8;i++){\
        if(((arg>>i)&1)==0){          \
            if(((arg>>(i-1))&1)==1){  \
                count++;              \
            }                         \
        }                             \
    }                                 \
    return count;                     \
}


struct info_t {
    char *name;
    uint8_t games;
    uint8_t points;    //1 - home team wins, 0 - draw, 2 - away team wins
    uint8_t hash_value;
};
struct node_t {
    struct info_t *info;
    struct node_t *next;
    struct node_t *prev;
};
struct double_linked_list_t {
    struct node_t *head;
    struct node_t *tail;
};

int read_table(struct double_linked_list_t** lists, const char* filename, uint8_t (*wsk)(uint8_t));
void display_table_forward(const struct double_linked_list_t* lists);
void free_list(struct double_linked_list_t* lists);

#endif //KOL_01_07_DEFS_H
