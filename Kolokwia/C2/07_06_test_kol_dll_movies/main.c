#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct list_t{
    struct node_t *head;
    struct node_t *tail;
};

struct film_data{
    int Number;
    char Film_Name[100];
    char Main_Actor[100];
    float IMDb_Rating;
    int Year;
    int bit_diff;
};

struct node_t{
    struct film_data data;
    struct node_t * next;
    struct node_t * prev;

};

void init_list(struct list_t * list){
    if(list == NULL) return;
    list->head = NULL;
    list->tail = NULL;
}

void create_list(struct list_t** list){
    if(list == NULL){
        printf("ERROR");
        return;
    }
    struct list_t * l = malloc(sizeof(struct list_t));
    if(l == NULL){
        printf("ERROR");
        return;
    }

    *list = l;
    init_list(l);
}

struct node_t* create_node(struct film_data data){
    struct node_t * new = malloc(sizeof(struct film_data));
    new->data = data;
    new->prev = NULL;
    new->prev = NULL;
    return new;
}
void add_to_begin_of_list(struct list_t* list, struct film_data data){
    if(list == NULL) return;
    if(list->tail == NULL && list->head == NULL){
        list->tail->data = data;
        list->tail->next == NULL;
        list->tail->prev == NULL;
        list->head = list->tail;
    }
    else{
        struct node_t * tmp = malloc(sizeof(struct node_t));
        tmp->next = NULL;
        tmp->prev = list->tail;
        tmp->data = data;
        list->tail = tmp;
    }
}
void add_to_end_of_list(struct list_t* list, struct  film_data data){
    if(list == NULL)
    {
        printf("ERROR");
        return;
    }
    if(list->head == NULL && list->tail == NULL){
        list->head->data = data;
        list->head->next == NULL;
        list->head->prev == NULL;
        list->tail = list->head;
    }
    else
    {
        struct node_t * tmp = malloc(sizeof(struct node_t));
        tmp->prev = NULL;
        tmp->next = list->head;
        tmp->data = data;
        list->head = tmp;
    }
}
void delete_node(struct list_t* list, struct node_t* node){
    if(list == NULL || node == NULL)
    {
        printf("ERROR");
        return;
    }

    if(list->head == node && list->tail == node){
        free(list->head);
        free(list->tail);
        list->head = NULL;
        list->tail = NULL;
    }

    struct node_t *current = list->head;
    while (current != node) {
        current = current->next;
    }
    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);
}

void swap_nodes(struct list_t* list, struct node_t* node1, struct node_t* node2) {
    if (list == NULL || node1 == NULL || node2 == NULL) {
        printf("ERROR\n");
        return;
    }
    if (node1 == node2) {
        printf("Nodes are identical\n");
        return;
    }

    struct node_t* prev1 = node1->prev;
    struct node_t* next1 = node1->next;
    struct node_t* prev2 = node2->prev;
    struct node_t* next2 = node2->next;

    // Handle the case when nodes are adjacent
    if (next1 == node2) { // node1 is right before node2
        if (prev1 != NULL) prev1->next = node2;
        else list->head = node2;
        if (next2 != NULL) next2->prev = node1;
        else list->tail = node1;
        node1->prev = node2;
        node1->next = next2;
        node2->prev = prev1;
        node2->next = node1;
    } else if (next2 == node1) { // node2 is right before node1
        if (prev2 != NULL) prev2->next = node1;
        else list->head = node1;
        if (next1 != NULL) next1->prev = node2;
        else list->tail = node2;
        node2->prev = node1;
        node2->next = next1;
        node1->prev = prev2;
        node1->next = node2;
    } else { // nodes are not adjacent
        if (prev1 != NULL) prev1->next = node2;
        else list->head = node2;
        if (next1 != NULL) next1->prev = node2;
        else list->tail = node2;
        if (prev2 != NULL) prev2->next = node1;
        else list->head = node1;
        if (next2 != NULL) next2->prev = node1;
        else list->tail = node1;
        node1->next = next2;
        node1->prev = prev2;
        node2->next = next1;
        node2->prev = prev1;
    }
}



void swap_nodes2(struct list_t* list, struct node_t* node1, struct node_t* node2) {
    if (list == NULL || node1 == NULL || node2 == NULL)
    {
        printf("ERROR\n");
        return;
    }
    if (node1 == node2)
    {
        printf("Nodes are identical\n");
        return;
    }

    struct film_data temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
}

void free_data(struct list_t* list){
    if(list == NULL){
        printf("ERROR\n");
        return;
    }

    struct node_t *temp;
    struct node_t *current = list->head;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}
void load_from_file(struct list_t* list, const char* filename){
    if(list == NULL || filename == NULL){
        printf("ERROR\n");
        return;
    }
    FILE *f = fopen(filename,"r");
    if(f == NULL){
        printf("ERROR\n");
        return;
    }
    char line[256];
    struct film_data temp;
    while(!fgets(line, sizeof(line),f)){
        fscanf(line,"%d,%[^,],%[^,],%f,%d",temp.Number,temp.Film_Name,temp.Main_Actor,temp.IMDb_Rating,temp.Year);
        add_to_begin_of_list(list, temp);
    }
}
void print_list_forward(struct list_t* list){
    if(list == NULL){
        printf("ERROR\n");
        return;
    }

    struct node_t *current = list->head;

    while (current != NULL) {
        printf("Number: %d\n", current->data.Number);
        printf("Film Name: %s\n", current->data.Film_Name);
        printf("Main Actor: %s\n", current->data.Main_Actor);
        printf("IMDB Rating: %.1f\n", current->data.IMDb_Rating);
        printf("Year: %d\n", current->data.Year);
        printf("BIT DIFF: %d\n\n", current->data.bit_diff);
        current = current->prev;
    }
    return;
}
void print_list_backward(struct list_t* list){
    if(list == NULL){
        printf("ERROR\n");
        return;
    }

    struct node_t *current = list->tail;

    while (current != NULL) {
        printf("Number: %d\n", current->data.Number);
        printf("Film Name: %s\n", current->data.Film_Name);
        printf("Main Actor: %s\n", current->data.Main_Actor);
        printf("IMDB Rating: %.1f\n", current->data.IMDb_Rating);
        printf("Year: %d\n", current->data.Year);
        printf("BIT DIFF: %d\n\n", current->data.bit_diff);
        current = current->next;
    }
    return;
}

int main(void) {
    struct list_t l;
    init_list(&l);
    load_from_file(&l,"dane.txt");
    print_list_forward(&l);
    print_list_backward(&l);
    return 0;
}
