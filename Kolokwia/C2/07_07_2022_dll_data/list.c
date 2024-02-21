#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void* aggregate_list(const struct list_t* list, const char* column_name, void(accumulate)(const void*, void*)){
    if(list == NULL || column_name == NULL) return NULL;

    int index = -1;
    for(unsigned int i = 0; i < list->header->size; i++)
    {
        if(strcmp(column_name, *(list->header->names + i)) == 0)
        {
            index = (int)i;
            break;
        }
    }

    if(index == -1) return NULL;
    int ERROR = 1;
    if(*(list->header->types + index) == INT && accumulate == accumulate_int)
    {
        ERROR = 0;
    }
    else if(*(list->header->types + index) == DBL && accumulate == accumulate_double)
    {
        ERROR = 0;
    }
    else if(*(list->header->types + index) == STR && accumulate == accumulate_string)
    {
        ERROR = 0;
    }
    if(ERROR) return NULL;

    int* int_res = NULL;
    int int_act;
    double* dbl_res = NULL;
    double dbl_act;
    char* str_res = NULL;
    char* str_act = NULL;
    struct node_t* node = list->head;

    switch (*(list->header->types + index))
    {
        case INT:
            int_res = calloc(1, sizeof(int));
            if(int_res == NULL)
            {
                return NULL;
            }
            int_act = 0;
            break;
        case DBL:
            dbl_res = calloc(1, sizeof(double));
            if(dbl_res == NULL)
            {
                return NULL;
            }
            dbl_act = 0;
            break;
        case STR:
            break;
    }

    while(node){
        switch (*(list->header->types + index))
        {
            case INT:
                int_act = (node->vals + index)->as_int;
                accumulate_int(&int_act, int_res);
                break;
            case DBL:
                dbl_act = (node->vals + index)->as_double;
                accumulate_double(&dbl_act, dbl_res);
                break;
            case STR:
                str_act = (node->vals + index)->as_str;
                accumulate_string(str_act, &str_res);
                break;
        }
        node = node->next;
    }

    switch (*(list->header->types + index))
    {
        case INT:
            return int_res;
        case DBL:
            return dbl_res;
        case STR:
            return str_res;
    }

    return NULL;
}

void accumulate_int(const void* cell_value, void* result){
    if(cell_value == NULL || result == NULL) return;

    *((int*)result) += *((int*)cell_value);
}

void accumulate_double(const void* cell_value, void* result){
    if(cell_value == NULL || result == NULL) return;

    *((double*)result) += *((double*)cell_value);
}

void accumulate_string(const void* cell_value, void* result){
    if(cell_value == NULL || result == NULL) return;

    char *val = (char*)cell_value;
    char **res = (char**)result;

    char *txt;
    if(*res != NULL)
    {
        txt = realloc(*res, strlen(*res) + strlen(val) + 1);
    }
    else
    {
        txt = calloc( strlen(val) + 1, 1);
        *txt='\0';
    }
    if(txt == NULL) return;

    if(*res != NULL)
    {
        strcpy(txt, *res);
        strcat(txt, val);
    }
    else
    {
        strcpy(txt, val);
    }

    *res = txt;
}

void display_list(const struct list_t *list){
    if(list == NULL) return;

    for(unsigned int i = 0; i < list->header->size; i++)
    {
        printf("%12s",*(list->header->names + i));
    }
    printf("\n");

    struct node_t*node = list->head;
    while (node)
    {
        for(unsigned int i = 0; i < list->header->size; i++){
            switch (*(list->header->types + i))
            {
                case INT:
                    printf("%12d",(node->vals + i)->as_int);
                    break;
                case DBL:
                    printf("%12.3lf",(node->vals + i)->as_double);
                    break;
                case STR:
                    printf("%12s",(node->vals + i)->as_str);
                    break;
            }
        }
        printf("\n");
        node = node->next;
    }
}
int read_header(struct header_t *header, FILE *fp){
    if(header == NULL || fp == NULL) return 1;

    char c;
    while ((c = (char)fgetc(fp)) == '\n');
    if(feof(fp))
    {
        return 4;
    }

    ungetc(c,fp);
    int first_data_line_position= ftell(fp);
    char buf[1024];
    fscanf(fp,"%1023[^\n]",buf);
    header->types = NULL;
    header->size = 0;
    header->names = NULL;
    unsigned int words = 0;
    int word_len = 0;
    for(int i = 0; i <= (int)strlen(buf); i++)
    {
        if(*(buf + i) == ' ' || *(buf + i) == '\t' || *(buf + i) == '\0')
        {
            if(word_len != 0)
            {
                if(words == 0)
                {
                    header->names= calloc(1, sizeof(char *));
                    if(header->names == NULL)
                    {
                        free_header(header);
                        return 2;
                    }
                    header->size = words;
                }
                else
                {
                    char **mem_names = realloc(header->names,(words + 1) * sizeof(char *));
                    if(mem_names == NULL)
                    {
                        free_header(header);
                        return 2;
                    }
                    header->names = mem_names;
                    header->size = words;
                }
                *(header->names + words)= calloc(word_len + 1, sizeof(char));
                if(*(header->names + words) == NULL)
                {
                    free_header(header);
                    return 2;
                }
                strncpy(*(header->names + words),(buf + i - word_len),word_len + 1);
                *(*(header->names + words) + word_len) = '\0';
                words++;
                header->size = words;
            }
            word_len = 0;
        }
        else
        {
            word_len++;
        }
    }
    header->size=words;
    while ((c = (char)fgetc(fp)) == '\n');
    if(feof(fp))
    {
        free_header(header);
        return 4;
    }
    enum type_t * types = calloc(words, sizeof(enum type_t));
    if(types == NULL)
    {
        free_header(header);
        return 2;
    }
    ungetc(c,fp);
    fscanf(fp,"%1023[^\n]", buf);
    word_len = 0;
    words = 0;
    int flag_litera = 0;
    int flag_kropka = 0;
    for(int i = 0; i <= (int)strlen(buf); i++)
    {
        if(*(buf + i) == ' '|| *(buf + i) == '\t' || *(buf + i) == '\0')
        {
            if(word_len!=0)
            {
                if(flag_litera)
                {
                    *(types + words) = STR;
                }
                else if(flag_kropka)
                {
                    *(types + words) = DBL;
                }
                else
                {
                    *(types + words) = INT;
                }
                words++;
            }
            word_len = 0;
            flag_kropka = 0;
            flag_litera = 0;
        }
        else
        {
            if(isalpha(*(buf + i)))
            {
                flag_litera = 1;
            }
            else if(*(buf + i) == '.')
            {
                flag_kropka = 1;
            }
            word_len++;
        }
    }
    header->types=types;
    fseek(fp,first_data_line_position,SEEK_SET);
    return 0;
}
int read_file(struct list_t **list, const char *fname){
    if(list == NULL || fname == NULL) return 1;

    FILE *file = fopen(fname,"r");
    if(file == NULL) return 3;

    *list = calloc(1, sizeof(struct list_t));
    if(*list == NULL)
    {
        fclose(file);
        return 2;
    }

    (*list)->head = NULL;
    (*list)->tail = NULL;
    (*list)->header = calloc(1, sizeof(struct header_t));
    if((*list)->header == NULL)
    {
        free(*list);
        fclose(file);
        return 2;
    }
    switch (read_header((*list)->header,file))
    {
        case 1:
            free((*list)->header);
            fclose(file);
            free(*list);
            return 1;
        case 2:
            free((*list)->header);
            fclose(file);
            free(*list);
            return 2;
        case 4:
            free((*list)->header);
            fclose(file);
            free(*list);
            return 4;
        default:
            break;
    }

    while (!feof(file)) {

        while (fgetc(file) != '\n');
        while (isspace(fgetc(file)));
        if(feof(file)) break;
        fseek(file, -1, SEEK_CUR);

        struct node_t *node = malloc(sizeof(struct node_t));
        if (node == NULL)
        {
            fclose(file);
            free_list(list);
            return 2;
        }

        node->next = NULL;
        node->prev = NULL;
        node->vals = calloc((*list)->header->size, sizeof(union val_t));
        if (node->vals == NULL)
        {
            fclose(file);
            free(node);
            free_list(list);
            return 2;
        }

        char buf[1024];
        for (unsigned int i = 0; i < (*list)->header->size; i++)
        {
            enum type_t *types = (*list)->header->types;
            switch (*(types + i))
            {
                case INT:
                    if (fscanf(file, "%d", &((node->vals + i)->as_int)) != 1)
                    {
                        fclose(file);
                        node->prev = (*list)->tail;
                        (*list)->tail = node;
                        free_list(list);
                        return 4;
                    }
                    break;
                case DBL:
                    if (fscanf(file, "%lf", &((node->vals + i)->as_double)) != 1)
                    {
                        fclose(file);
                        node->prev = (*list)->tail;
                        (*list)->tail = node;
                        free_list(list);
                        return 4;
                    }
                    break;
                case STR:
                    if (fscanf(file, "%1023s", buf) != 1)
                    {
                        fclose(file);
                        node->prev = (*list)->tail;
                        (*list)->tail = node;
                        free_list(list);
                        return 4;
                    }
                    (node->vals + i)->as_str = calloc(strlen(buf) + 1, sizeof(char));
                    if ((node->vals + i)->as_str == NULL)
                    {
                        fclose(file);
                        node->prev = (*list)->tail;
                        (*list)->tail = node;
                        free_list(list);
                        return 2;
                    }
                    strcpy((node->vals + i)->as_str, buf);
                    break;
            }
        }
        node->prev = (*list)->tail;
        (*list)->tail = node;
        if((*list)->head == NULL) (*list)->head = node;
        else
        {
            struct node_t *akt = (*list)->head;
            while (akt->next!=NULL) akt = akt->next;
            akt->next = node;
        }

    }
    fclose(file);
    return 0;
}

void free_header(struct header_t *header){
    if(header == NULL) return;
    if(header->types != NULL)
    {
        free(header->types);
    }

    if(header->names != NULL)
    {
        for(int i = 0; i < (int)header->size; i++)
        {
            if((*(header->names + i)) != NULL)
            {
                free(*(header->names + i));
            }
            else break;
        }
        free(header->names);
    }
}

void free_list(struct list_t **list){
    if(list == NULL || *list == NULL) return;

    struct node_t *node = (*list)->tail;
    while (node != NULL)
    {
        (*list)->tail = (*list)->tail->prev;
        for(int i = 0; i < (int)(*list)->header->size; i++)
        {
            if (*((*list)->header->types + i) == STR)
            {
                char *str = (node->vals + i)->as_str;
                free(str);
            }
        }
        free(node->vals);
        free(node);
        node = (*list)->tail;
    }
    free_header((*list)->header);
    free((*list)->header);
    free(*list);
}