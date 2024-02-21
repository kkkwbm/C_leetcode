#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"



#define CREATE_FUNCTION_COUNT01(TYPE) \
TYPE count01_##TYPE(TYPE arg){        \
    TYPE count=0;                     \
    for(int i=1;i<sizeof(TYPE)*8;i++){\
        if(((arg>>i)&1)==0){          \
            if(((arg>>(i-1))&1)==1){  \
                count++;              \
            }                         \
        }                             \
    }                                 \
    return count;                     \
}

CREATE_FUNCTION_COUNT01(uint8_t)

#define CREATE_FUNCTION_COUNT10(TYPE)          \
TYPE count10_##TYPE(TYPE arg){                 \
    TYPE count=0;                     \
    for(int i=0;i<(sizeof(TYPE)*8) -1 ;i++){\
        if(((arg>>i)&1)==1){          \
            if(((arg>>(i+1))&1)==0){  \
                count++;              \
            }                         \
        }                             \
    }                                 \
    return count;                     \
}



CREATE_FUNCTION_COUNT10(uint8_t)


static int is_valid_complex_number(const char* str);
static void parse_complex_number(const char* str, unsigned char* re, unsigned char* im);

void list_init(struct list_t *list) {
    if(list == NULL) return;
    list->head = NULL;
}

struct node_t* list_create_element(unsigned char re, unsigned char im, uint8_t (*crc_function)(uint8_t)) {
    if(re == NULL || im == NULL) return NULL;
    struct node_t* node = (struct node_t*)malloc(sizeof(struct node_t));
    if (node == NULL) return NULL;

    node->data.re = re;
    node->data.im = im;
    node->data.crc = crc_function(re ^ im);
    node->next = NULL;

    return node;
}

int list_push_front(struct list_t *list, struct node_t *item) {
    if (list == NULL || item == NULL) return -2;

    if (list->head == NULL)
    {
        item->next = NULL;
        list->head = item;
    }
    else
    {
        item->next = list->head;
        list->head = item;
    }

    return 0;
}

int list_push_back(struct list_t *list, struct node_t *item) {
    if (list == NULL || item == NULL) return -2;

    if (list->head == NULL)
    {
        item->next = NULL;
        list->head = item;
    }
    else
    {
        struct node_t* current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        item->next = NULL;
        current->next = item;
    }

    return 0;
}

int list_clear(struct list_t* list) {
    if (list == NULL) return -1;

    struct node_t* current = list->head;
    while (current != NULL)
    {
        struct node_t* next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;

    return 0;
}

struct list_t* list_load_from_file(FILE* f, enum order_t order) {
    if (f == NULL) return NULL;

    printf("STAGE 1 - list_load_from_file\n");

    struct list_t* list = (struct list_t*)malloc(sizeof(struct list_t));
    if (list == NULL) return NULL;

    list_init(list);

    unsigned char re, im;
    // printf("STAGE 2 - list_load_from_file\n");
    // Tutaj się wywala
    while (fscanf(f, "%hhu + j%hhu", &re, &im) == 2)
    {
        //printf("STAGE 3 - list_load_from_file\n");
        //printf("%d %d\n", re, im);

        struct node_t* item = list_create_element(re, im, count10_uint8_t);
        if (item == NULL)
        {
            list_clear(list);
            free(list);
            return NULL;
        }

        if (order == FRONT) list_push_front(list, item);
        else if (order == BACK) list_push_back(list, item);
        else
        {
           // list_clear(list);
           //free(list);
            //return NULL;
            list_push_back(list, item);
        }
    }

    return list;
}

struct list_t* list_load_from_file2(FILE* f, enum order_t order) {
    if (f == NULL) return NULL;

    struct list_t* list = (struct list_t*)malloc(sizeof(struct list_t));
    if (list == NULL) return NULL;

    list_init(list);

    char buffer[20];
    while (fgets(buffer, sizeof(buffer), f) != NULL)
    {
        char* newline_pos = strchr(buffer, '\n');
        if (newline_pos != NULL) *newline_pos = '\0';

        if (!is_valid_complex_number(buffer)) continue;

        unsigned char re, im;
        parse_complex_number(buffer, &re, &im);
        printf("%d %d\n", re, im);

        struct node_t* item = list_create_element(re, im, count10_uint8_t);
        if (item == NULL)
        {
            list_clear(list);
            free(list);
            return NULL;
        }

        if (order == FRONT) list_push_front(list, item);
        else if (order == BACK) list_push_back(list, item);
        else
        {
            list_clear(list);
            free(list);
            return NULL;
        }
    }

    return list;
}

void list_print(const struct list_t* list) {
    if (list == NULL) return;

    if (list->head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    struct node_t* current = list->head;
    while (current != NULL)
    {
        printf("%hhu + j%hhu: %hhu\n", current->data.re, current->data.im, current->data.crc);
        current = current->next;
    }
}




static int is_valid_complex_number(const char* str) {
    if (str == NULL) return 0;

    const char* ptr = str;
    size_t len = 0;
    while (*ptr != '\0')
    {
        len++;
        ptr++;
    }

    if (len < 5) return 0;

    if (*(ptr - 1) != '>' && *(ptr - 1) != '<') return 0;

    ptr = str;
    while (*ptr != '\0')
    {
        if (!((*ptr >= '0' && *ptr <= '9') || *ptr == '+' || *ptr == '-' || *ptr == 'j' || *ptr == ' ')) return 0;
        ptr++;
    }

    return 1;
}

static void parse_complex_number(const char* str, unsigned char* re, unsigned char* im) {
    sscanf(str, "%hhu + j%hhu", re, im);
}
