#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tested_declarations.h"
#include "rdebug.h"

struct double_linked_list_t * dll_innit(){
    struct double_linked_list_t * list = malloc(sizeof(struct double_linked_list_t));
    if(list == NULL) return NULL;

    list->head = NULL;
    list->tail = NULL;
    return list;
}

int products_counter(struct products_t ** products){
    int i = 0;
    while( *(products + i) != NULL ) i++;
    return i;
}

struct products_t ** add_product(struct products_t ** products, char * product_name, int price, int (*wsk)(int)){
    int products_in_category = products_counter(products);
    struct products_t **temp = realloc(products, sizeof(struct products_t *) * (products_in_category + 2));
    if (temp == NULL)
    {
        for (int j = 0; j < products_in_category; j++)
        {
            free(*(products + j));
        }
        free(products);
        return NULL;
    }

    products = temp;

    struct products_t * temp_product = malloc(sizeof(struct products_t));
    if(temp_product == NULL)
    {
        for (int j = 0; j < products_in_category; j++)
        {
            free(*(products + j));
        }
        free(products);
        return NULL;
    }
    temp_product->product_name = strdup(product_name);
    if(product_name == NULL)
    {
        for (int j = 0; j < products_in_category; j++)
        {
            free(*(products + j));
        }
        free(products);
        free(temp_product);
        return NULL;
    }
    temp_product->price = price;
    temp_product->hash_value = wsk(price);

    *(products + products_in_category) = temp_product;

    products_in_category++;
    *(products + products_in_category) = NULL;
    return products;
}

struct categories_t *dll_find(struct double_linked_list_t *dll, char *name) {
    struct node_t *node = dll->head;
    while (node != NULL)
    {
        if (strcmp(name, node->categories->name) == 0) return node->categories;
        node = node->next;
    }
    return NULL;
}

int dll_push_back(struct double_linked_list_t *dll, struct categories_t *info){
    if(dll == NULL || info == NULL) return 2;

    struct node_t *node = malloc(sizeof(struct node_t));
    if (node == NULL) return 1;

    node->categories = info;
    node->prev = dll->tail;
    node->next = NULL;

    if (dll->tail != NULL) dll->tail->next = node;

    dll->tail = node;

    if (dll->head == NULL) dll->head = node;

    return 0;
}



struct categories_t *get_info_for_category(struct double_linked_list_t * dll, char * category_name){
    struct categories_t * category = dll_find(dll, category_name);
    if(category == NULL)
    {
        category = malloc(sizeof(struct categories_t));
        if(category == NULL) return NULL;
        category->name = strdup(category_name);
        if(category->name == NULL)
        {
            free(category);
            return NULL;
        }
        category->products = calloc(1, sizeof(struct products_t **));
        if(category->products == NULL)
        {
            free(category->name);
            free(category);
            return NULL;
        }

        if(dll_push_back(dll, category) == 1)
        {
            free(category->name);
            free(category->products);
            free(category);
            return NULL;
        }

    }
    return category;
}

int read_list(struct double_linked_list_t** lists, const char* filename, int (*wsk)(int)){
    if(filename == NULL || wsk == NULL) return -1;

    if(*lists == NULL)
    {
        *lists = dll_innit();
        if(*lists == NULL)
        {
            return -4;
        }
    }

    FILE * f = fopen(filename, "r");
    if(f == NULL)
    {
        free_list(*lists);
        return -2;
    }

    char categorie_name[41], product_name[61];
    int price;

    while(!feof(f))
    {

        if (fscanf(f, "%40[^|]|%60[^|]|%d", categorie_name, product_name, &price) != 3)
        {
            free_list(*lists);
            fclose(f);
            return -3;
        }

        struct categories_t *category = get_info_for_category(*lists, categorie_name);
        if (category == NULL)
        {
            fclose(f);
            free_list(*lists);
            return -4;
        }
        category->products = add_product(category->products, product_name, price, wsk);
        if(category->products == NULL)
        {
            fclose(f);
            free_list(*lists);
            return -4;
        }

    }
    return 0;
}

void display_list(const struct double_linked_list_t* lists){
    if (lists == NULL) return;
    int counter = 0;
    struct node_t *current_node = lists->head;
    while (current_node != NULL)
    {
        printf("%s\n", current_node->categories->name);
        struct products_t ** temp = current_node->categories->products;
        while(temp != NULL)
        {
            printf("%d %s - %d %d\n",counter, (*temp)->product_name, (*temp)->price, (*temp)->hash_value);
            counter++;
            temp++;
        }
        current_node = current_node->next;
    }
}


void free_list(struct double_linked_list_t* lists){
    if (lists == NULL) return;
    struct node_t *prev;
    struct node_t *node = lists->head;
    while (node != NULL)
    {
        prev = node;
        node = node->next;
        free(prev->categories->name);
        struct products_t ** temp = prev->categories->products;
        for(int i = 0; *(temp + i) != NULL; i++)
        {
            free((*temp + i)->product_name);
            free((*temp + i));
        }
        free(prev->categories->products);
        free(prev->categories);
        free(prev);
    }
    free(lists);
}


