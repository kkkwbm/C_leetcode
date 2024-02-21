#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"
#include <math.h>

int stack_push(stack_t* pstack, void* pvalue)
{
    if(pstack==NULL || pvalue == NULL)return -1;
    if( pstack->top==pstack->max_capacity ) return -2;
    float new_memory_amount_f;
    int new_mem;
    void * temp;
    if( pstack->top + 1 >= pstack->current_capacity)
    {
        new_memory_amount_f = pstack->current_capacity * 1.2;
        new_mem = ceil(new_memory_amount_f);
        if( new_mem > pstack->max_capacity)
        {
            new_mem = pstack->max_capacity;
        }
        temp = realloc( pstack->pdata, (size_t) new_mem * pstack->item_size);
        if( !temp)
        {
            return -1;
        }
        pstack->current_capacity = new_mem;
        pstack->pdata = temp;
    }
    pstack->top += 1;
    memcpy((char *) pstack->pdata + (( pstack->top - 1 ) * pstack->item_size), pvalue, pstack->item_size);
    return 0;
}

int stack_pop(stack_t* pstack, void* pvalue)
{
    if(pstack==NULL||pvalue==NULL||pstack->top==0) return -1;
    memcpy( (char *) pvalue, (char *) pstack->pdata + ( (pstack->top - 1) * pstack->item_size), pstack->item_size);
    pstack->top--;
    return 0;
}

void stack_print(const stack_t* pstack)
{
    if(pstack==NULL||pstack->top==0) return;
    for(int i = pstack->top - 1;i >= 0;i--)
    {
        if(i==pstack->top-1) printf("> ");
        for (int j = 0; j < pstack->item_size; ++j) {
            printf("%x ", *( (char *)pstack->pdata + i * pstack->item_size + j));
        }
        printf("\n");
    }

}
stack_t* stack_create(uint32_t initial_capacity, uint32_t max_capacity, uint32_t item_size)
{
    stack_t * stack = (stack_t *) malloc(1 * sizeof(stack_t));
    if( !stack) return NULL;
    stack->pdata = malloc( item_size * initial_capacity);
    if( !(stack->pdata))
    {
        free(stack);
        return NULL;
    }
    stack->current_capacity = initial_capacity;
    stack->max_capacity = max_capacity;
    stack->item_size = item_size;
    stack->top = 0;
    return stack;
}

void stack_destory(stack_t* pstack)
{
    if( !pstack) return;
    free( pstack->pdata);
    free(pstack);
}