#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char * str;
    struct node* next;
    struct node* prev;
};

struct list {
    struct node* head;
    struct node* tail;
};

int init_list(struct list * dll){
    if(dll == NULL) return 1;

    dll->head = NULL;
    dll->tail = NULL;
    return 0;
}

int list_size(struct list * dll){
    if(dll == NULL || dll->head == NULL) return -1;

    int size = 0;
    for(struct node * i = dll->head; i; i = i->next, size++);
    return size;
}

int push_back(struct list * dll, struct node * n){
    if(dll == NULL || n == NULL) return 1;

    if(dll->head == NULL){
        dll->head = n;
        dll->tail = n;
        n->next = NULL;
        n->prev = NULL;
        return 0;
    }
    n->prev = dll->tail;
    dll->tail->next = n;
    dll->tail = n;
    n->next = NULL;
    return 0;
}


int push_front(struct list * dll, struct node * n){
    if(dll == NULL || n == NULL) return 1;

    if(dll->head == NULL && dll->tail == NULL){
        dll->head = n;
        dll->tail = n;
        n->next = NULL;
        n->prev = NULL;
        return 0;
    }
    dll->head->prev = n;
    n->next = dll->head;
    n->prev = NULL;
    dll->head = n;
    return 0;
}

void print(struct list * dll){
    if(dll == NULL || dll->head == NULL) return;

    for(struct node * i = dll->head; i; i = i->next){
        puts(i->str);
    }
    puts("END");
}

void print_backwards(struct list * dll){
    if(dll == NULL || dll->head == NULL) return;

    for(struct node * i = dll->tail; i; i = i->prev){
        puts(i->str);
    }
    puts("END");
}

struct node * create_element(const char * str){
    if(str == NULL) return NULL;

    return NULL;
}

void clear(struct list* dll){
    if(dll == NULL || dll->head == NULL) return;

    for(struct node * i = dll->head; i;)
    {
        struct node * tmp = i->next;
        free(i->str);
        free(i);
        i = tmp;
    }
}


void del(struct list* dll, int index){
    if(dll == NULL)
    {
        printf("ERROR");
        return;
    }
    int size = list_size(dll);
    if(index < 0 || size <= index) return;

    struct node * del;
    if(index == 0){
        del = dll->head;
        dll->head = dll->head->next;
        dll->head->prev=NULL;
        free(del);
        return;
    }
    int i;
    struct node * node = dll->head;
    for(i = 0; i < index-1; i++){
        node = node->next;
    }

    del = node->next;

    node->next = node->next->next;
    if(node->next) node->next->prev = node;
    if(index == size - 1) dll->tail = node;
    free(del->str);
    free(del);
}

void insert(struct list * dll, struct node * ins, int index){
    if(dll == NULL || ins == NULL) return;

    if(index < 0 || list_size(dll) <= index) return;

    if(dll->head == NULL) return;

    if(index == 0){
        push_front(dll, ins);
        return;
    }

    if(index == list_size(dll) - 1){
        push_back(dll, ins);
        return;
    }
    int i;
    struct node * node = dll->head;
    for( i = 0; i < index - 1; i++){
        node = node->next;
    }
    if(node->next) node->next->prev = ins;

    ins->next = node->next;
    ins->prev = node;
    node->next=ins;
}

int main(void) {
    struct list l;
    init_list(&l);
    const char*txts[] = {"arbuz", "winogrono", "banan", "agrest"};
    int txts_len = 4;
    for(int i = 0; i < txts_len; i++)
    {
        struct node *n = create_element(txts[i]);
        push_front(&l, n);
    }
    print(&l);
    print_backwards(&l);
    insert(&l, create_element("kiwi"), 2);
    insert(&l, create_element("gruszka"), 0);
    insert(&l, create_element("winogrono"), 20);
    print(&l);
    print_backwards(&l);
    del(&l, 0);
    del(&l, 20);
    del(&l, 2);print(&l);
    print_backwards(&l);
    clear(&l);
    return 0;
}
