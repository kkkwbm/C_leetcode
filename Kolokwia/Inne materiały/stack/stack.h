#ifndef STACK_H
#define STACK_H
#define STACK_CAPACITY 12

#include <stdint.h>

typedef struct {

    void* pdata;

    uint32_t item_size;

    uint32_t top;

    uint32_t current_capacity, max_capacity;

} stack_t;

stack_t* stack_create(uint32_t initial_capacity, uint32_t max_capacity, uint32_t item_size);

void stack_destory(stack_t* pstack);

int stack_push(stack_t* pstack, void* pvalue);

int stack_pop(stack_t* pstack, void* pvalue);

void stack_print(const stack_t* pstack);

#endif