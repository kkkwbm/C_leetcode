#include <stdio.h>
#include <stdint.h>
#include "tested_declarations.h"
#include "rdebug.h"

int is_sparse(uint64_t value) {
    return (value & (value >> 1)) == 0;
}

int main() {
    uint64_t value;

    printf("Podaj wartość: ");
    if (scanf("%lu", &value) != 1) {
        printf("Incorrect input\n");
        return 1;
    }

    printf("Liczba: %016lx, Wynik: %d\n", value, is_sparse(value));
    return 0;
}
