#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"

unsigned long long add(unsigned long long a, unsigned long long b) {
    while (b != 0)
    {
        unsigned long long carry = a & b;

        a = a ^ b;

        b = carry << 1;
    }
    return a;
}

int main() {
    unsigned long long num1, num2;

    printf("Enter numbers: ");
    if (scanf("%llu %llu", &num1, &num2) != 2)
    {
        printf("Incorrect input\n");
        return 1;
    }

    printf("%llu\n", add(num1, num2));
    return 0;
}

