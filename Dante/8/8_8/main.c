#include <stdio.h>
#include "function.h"
#include "tested_declarations.h"
#include "rdebug.h"

int main() {
    int error;
    printf("%lu\n", bits_to_number(&error, 3, 1, 1, 1));
    printf("%lu\n", bits_to_number(&error, 8, 1, 0, 0, 0, 0, 0, 0, 1));
    printf("%lu\n", bits_to_number(&error, 32, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0));
    return 0;
}
