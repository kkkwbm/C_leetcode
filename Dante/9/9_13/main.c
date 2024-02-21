#include "functions.h"
#include "tested_declarations.h"
#include "rdebug.h"

int main() {
    int choice;

    printf("Enter data type: ");
    if (scanf("%d", &choice) != 1)
    {
        printf("Incorrect input\n");
        return 1;
    }

    if (choice < 0 || choice > 2)
    {
        printf("Incorrect input data \n");
        return 2;
    }

    int bits_set, bits_cleared;

    if (choice == 0)
    {
        unsigned int value;
        unsigned int *value_p = &value;
        printf("Enter an integer number: ");
        if (scanf("%u", &value) != 1)
        {
            printf("Incorrect input\n");
            return 1;
        }

        COUNT_BITS(value, &bits_set, &bits_cleared);
        printf("%d\n%d\n", bits_set, bits_cleared);
        DISPLAY_BITS(value);
        REVERSE_BITS(value_p);
        DISPLAY_BITS(value);

    }
    else if (choice == 1)
    {
        unsigned short value;
        unsigned short *value_p = &value;
        printf("Enter an integer number: ");
        if (scanf("%hu", &value) != 1)
        {
            printf("Incorrect input\n");
            return 1;
        }

        COUNT_BITS(value, &bits_set, &bits_cleared);
        printf("%d\n%d\n", bits_set, bits_cleared);
        DISPLAY_BITS(value);
        REVERSE_BITS(value_p);
        DISPLAY_BITS(value);
    }
    else if (choice == 2)
    {
        unsigned long value;
        unsigned long *value_p = &value;
        printf("Enter an integer number: ");
        if (scanf("%lu", &value) != 1)
        {
            printf("Incorrect input\n");
            return 1;
        }

        COUNT_BITS(value, &bits_set, &bits_cleared);
        printf("%d\n%d\n", bits_set, bits_cleared);
        DISPLAY_BITS(value);
        REVERSE_BITS(value_p );
        DISPLAY_BITS(value);
    }

    return 0;
}

