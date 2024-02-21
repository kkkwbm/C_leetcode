#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"

int circular_buffer_create(struct circular_buffer_t *a, int N)
{
    if (a == NULL || N <= 0) return 1;

    a->ptr = (int *) malloc(N * sizeof(int));

    if (a->ptr == NULL) return 2;

    a->capacity = N;
    a->begin = 0;
    a->end = 0;
    a->full = 0;

    return 0;
}
int circular_buffer_create_struct(struct circular_buffer_t **cb, int N)
{
    if(cb == NULL || N <= 0) return 1;

    *cb = malloc(sizeof(struct circular_buffer_t));

    if(*cb == NULL)return 2;

    int res = circular_buffer_create(*cb,N);
    if (res != 0)free(*cb);

    return res;
}
void circular_buffer_destroy(struct circular_buffer_t *a)
{
    if (a!= NULL) free(a->ptr);
}
void circular_buffer_destroy_struct(struct circular_buffer_t **a)
{
    if(a != NULL)
    {
        circular_buffer_destroy(*a);
        free(*a);
    }
}
int circular_buffer_empty(const struct circular_buffer_t *a){

    if (a == NULL || a->ptr == NULL || a->capacity < 1 || a->capacity < a->end || a->begin < 0 || a->end< 0 || a->begin > a->capacity) return -1;
    if (a->begin == a->end && a->full == 0) return 1;
    return 0;
}
int circular_buffer_full(const struct circular_buffer_t *a)
{
    if (a == NULL || a->ptr == NULL || a->capacity < 1 || a->capacity < a->end || a->begin < 0 || a->end< 0 || a->begin > a->capacity) return -1;
    if (a->full == 1) return 1;
    else return 0;
}



int circular_buffer_push_back(struct circular_buffer_t *cb, int value) {
    if(cb == NULL || cb->ptr == NULL || cb->capacity < 1 || cb->end >= cb->capacity
       || cb->begin < 0 || cb->end < 0 || cb->begin > cb->capacity) return 1;

    *(cb->ptr + cb->end) = value;
    cb->end = (cb->end + 1) % cb->capacity;

    if (cb->end == cb->begin && cb->full == 0) {
        cb->full = 1;
    }
    if(cb->full == 1 && cb->end == 0) cb->begin = 0;
    else if (cb->full == 1) {
        cb->begin = (cb->begin + 1) % cb->capacity;
    }


    return 0;
}


int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code){
    if(a == 0 || a->ptr == 0 || a->capacity < 1 || a->begin > a->capacity || a->end < 0 || a->begin < 0 || a->end > a->capacity)
    {
        if(err_code != 0 && err_code != NULL) *(err_code) = 1;
        return 0;
    }
    if(err_code != 0 & err_code != NULL)
    {
        *(err_code) = 0;
        if(a->full == 0 && a->begin == 0) *err_code = 2;
    }
    int liczba = *(a->ptr + a->begin);
    a->full = 0;
    if(a->begin + 1 == a->capacity) a->begin = 0;
    else a->begin = a->begin + 1;
    return liczba;
}

int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code) {
    if(a == 0 || a->ptr == 0 || a->capacity <= 0 || a->begin > a->capacity
       || a->end < 0 || a->begin < 0 || a->end > a->capacity)
    {
        if(err_code != 0 & err_code != NULL) *(err_code) = 1;
        return 0;
    }


    if (a->begin == a->end && !a->full)
    {
        if(err_code != NULL) *err_code = 2;
        return 0;
    }


    int value;
    if (a->end == 0) a->end = a->capacity - 1;
    else a->end--;

    value = *(a->ptr + a->end);
    a->full = 0;
    if(err_code != NULL) *err_code = 0;
    return value;
}



void circular_buffer_display(const struct circular_buffer_t *a) {
    if(a == NULL || a->ptr == NULL || a->capacity <= 0 || a->end < 0 || a->begin < 0
       || a->end >= a->capacity || a->begin >= a->capacity) return;

    if(a->begin == a->end && a->full != 1) return;


    int index = a->begin;
    if(a->end == 0){
        for(int i = 0; i < (a->capacity - a->begin); i++){
            printf("%d ", *(a->ptr + index));
            index++;
        }
        printf("\n");
        return;
    }


    index = a->begin;

    if (a->full)
    {
        index = a->end;
        for (int i = 0; i < a->capacity; i++)
        {
            printf("%d ", *(a->ptr + index));
            index = (index + 1) % a->capacity;
        }
    }
    else if (a->begin > a->end)
    {
        printf("%d ", *(a->ptr + index));
        for (int i = 1; i < (a->capacity + a->end) - a->begin; i++)
        {
            index = (index + 1) % a->capacity;
            printf("%d ", *(a->ptr + index));
        }
    }
    else
    {
        printf("%d ", *(a->ptr + index));
        for (int i = 1; i < a->end - a->begin; i++)
        {
            index = (index + 1) % a->capacity;
            printf("%d ", *(a->ptr + index));
        }
    }
    printf("\n");
}
