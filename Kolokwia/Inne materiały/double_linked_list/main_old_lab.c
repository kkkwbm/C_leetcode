#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum direction_t {
    ASCENDING = 0,
    DESCENDING
};
struct item_t {
    void* value;
    struct item_t* next;
    struct item_t* prev;
};
struct dll_t {
    struct item_t* head;
    struct item_t* tail;
    int item_size;
};

struct dll_t* create_list(int item_size);
struct item_t* create_item(void* value, int item_size);
int list_push_back(struct dll_t * list, void * value);
void destroy(struct dll_t* plist);
void display(const struct dll_t* plist, void(*fun)(void*));
int sort(struct dll_t* plist, enum direction_t dir, int(*compare)(void*,void*));
int size_of_list(const struct dll_t  * list);
void display_int(void *);
int main() {

    struct dll_t * list = create_list(sizeof(int ));
    int vals[] = {1,2,3,4,5};
    for (int i = 0; i < 5; ++i) {
        list_push_back(list, vals + i);
    }
    display(list, display_int);
    return 0;
}
void display_int(void * element)
{
    printf("%d ",  *( (int *) (element)) );
}
int size_of_list(const struct dll_t * list)
{
    if(list == NULL) return -1;

    int size = 0;
    for (struct item_t * i = list->head; i != NULL ; i = i->next) size++;

    return size;
}
void display(const struct dll_t* plist, void(*fun)(void*)){
    if(plist == NULL || fun == NULL) return;

    int size = size_of_list(plist);
    if(size == 0) return;

    printf("Rozmiar listy: %d ", size);
    printf("Elementy listy: ");

    for (struct item_t * i = plist->head; i != NULL ; i = i->next)
    {
        fun(i->value);
    }
}
int list_push_back(struct dll_t * list, void * value){
    if(list == NULL || value == NULL) return 1;

    struct item_t * item = create_item(value, list->item_size);
    if(item == NULL) return 2;

    if(list->tail == NULL && list->head == NULL)
    {
        list->head = item;
        list->tail = item;
        return 0;
    }

    item->prev = list->tail;
    list->tail->next = item;
    list->tail = item;

    return 0;
}
struct dll_t* create_list(int item_size){
    if(item_size < 1) return NULL;

    struct dll_t * list = (struct dll_t *)malloc(sizeof(struct dll_t) * 1);
    if(list == NULL) return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->item_size = item_size;

    return list;
}
struct item_t* create_item(void* value, int item_size){
    if(value == NULL || item_size < 1) return NULL;

    struct item_t * item = (struct item_t *) malloc(sizeof(struct item_t));
    if(item == NULL) return NULL;

    item->value = malloc(item_size);
    if(item->value == NULL)
    {
        free(item);
        return NULL;
    }
    item->next = NULL;
    item->prev = NULL;

    memcpy(item->value, value, item_size);

    return item;
}
int sort(struct dll_t* plist, enum direction_t dir, int(*compare)(void*,void*)){
    if(plist == NULL || compare == NULL) return 1;
    if(dir == ASCENDING)
    {
        for(int j = 1;j;)
        {
            j = 0;
            for(struct item_t * i = plist->head; i->next != NULL; i = i->next)
            {
                if((compare(i->value,i->next->value) > 0 && dir == ASCENDING) || (compare(i->value,i->next->value) < 0 && dir == DESCENDING))
                {
                    struct item_t *temp = i->next;
                    if(i->prev) i->prev->next = temp;
                    if(temp->next) temp->next->prev = i;
                    i->next = temp->next;
                    temp->prev = i->prev;
                    i->prev = temp;
                    temp->next = i;
                    if(i == plist->head)
                    {
                        plist->head = i->prev;
                    }
                    else if(temp == plist->tail)
                    {
                        plist->tail = i;
                    }
                    i = i->prev;
                    j++;
                }
            }
        }
    }
    return 0;
}