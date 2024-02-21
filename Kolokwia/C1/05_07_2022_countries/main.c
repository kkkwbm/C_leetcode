#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"


int main() {

    struct countries_t **temp;
    int x = read_countries("test.txt",  &temp);


    if ( x == 0) {
        display_countries(temp);
        free_countries(temp);
    }

    printf("\nERROR: %d" ,x);
    return 0;
}



