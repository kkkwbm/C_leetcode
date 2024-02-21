#include <stdio.h>
#include "array.h"
#include <stdlib.h>



int main(){
    struct array_t arr;
    struct array_t* p_arr = &arr;

    int valid = 0;
    int number = 0;

    printf("Podaj ilosc elementow: ");
    valid=scanf("%d", &number);
    if(valid != 1){
        printf("Incorrect input");
        return 1;
    }

    if(number <= 0){
        printf("Incorrect input data");
        return 2;
    }

    valid = array_create(p_arr, number);
    if(valid == 2){
        printf("Failed to allocate memory");
        return 8;
    }


    int i = 0;

    (p_arr->size) = 0;
    printf("Podaj wartosci: ");
    while(p_arr->capacity > p_arr->size){

        valid = scanf("%d", ((p_arr->ptr) + i));
        if(*((p_arr->ptr) + i) == 0 && p_arr->size == 0 && valid == 1)
        {
            free(p_arr->ptr);
            printf("Buffer is empty");
            return 0;
        }
        if(valid != 1){
            free(p_arr->ptr);
            printf("Incorrect input");
            return 1;
        }

        (p_arr->size) += 1;
        i++;
    }
    if((p_arr->size) == (p_arr->capacity)) printf("Buffer is full\n");

    if(p_arr->size == 0) printf("buffer is empty");
    else{
        array_display(p_arr);
        array_destroy(p_arr);
    }

    return 0;
}