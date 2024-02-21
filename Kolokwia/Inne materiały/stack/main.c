#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"
#include <assert.h>

int main() {

    stack_t *ps;

    setvbuf(stdout, NULL, _IONBF, 0);

    ps = stack_create(16, 32, 4);

    stack_print(ps);



    int ret;

    ret = stack_push(ps, (int[]){42});

    assert(ret == 0);

    stack_push(ps, (int[]){10042});

    assert(ret == 0);

    stack_print(ps);



    for (int i = 0; i < 32; i++) {

        ret = stack_push(ps, &i);

        assert(i < 30 && ret == 0 || i >= 30 && ret == -2);

    }

    stack_print(ps);



    int val;

    stack_pop(ps, &val);

    stack_pop(ps, &val);

    stack_pop(ps, &val);

    stack_print(ps);



    stack_destory(ps);

    return 0;

}