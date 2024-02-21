//
// Created by student on 20/02/2024.
//

#ifndef KOL_20_02_DEFS_H
#define KOL_20_02_DEFS_H


#define CREATE_FUNCTION_COUNT01(TYPE)        \
TYPE count01_##TYPE(TYPE arg){               \
    TYPE count = 0;                          \
    for(unsigned int i = 1; i < sizeof(TYPE) * 8; i++)\
    {                                        \
        if(((arg >> i) & 1) == 0)            \
        {                                    \
            if(((arg >> (i - 1)) & 1) == 1)  \
            {                                \
                count++;                     \
            }                                \
        }                                    \
    }                                        \
    return count;                            \
}

struct products_t
{
    char* product_name;
    unsigned int price;
    unsigned int hash_value;
};

struct categories_t
{
    char* name;
    struct products_t** products;
};

struct node_t
{
    struct categories_t* categories;
    struct node_t* next;
    struct node_t* prev;
};

struct double_linked_list_t
{
    struct node_t* head;
    struct node_t* tail;
};

int read_list(struct double_linked_list_t** lists, const char* filename, int (*wsk)(int));
void display_list(const struct double_linked_list_t* lists);
void free_list(struct double_linked_list_t* lists);

#endif //KOL_20_02_DEFS_H
