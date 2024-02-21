#include "doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include "tested_declarations.h"
#include "rdebug.h"

int main() {
    struct doubly_linked_list_t *dll = dll_create();

    if (!dll)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Enter list (-1 when done): ");
    int input_value;
    while (1)
    {
        if (scanf("%d", &input_value) != 1)
        {
            printf("Incorrect input\n");
            dll_clear(dll);
            free(dll);
            return 1;
        }

        if (input_value == -1) break;

        if (dll_push_back(dll, input_value) != 0)
        {
            printf("Failed to allocate memory\n");
            dll_clear(dll);
            free(dll);
            return 8;
        }
    }

    if (dll_is_empty(dll) == 1)
    {
        printf("Not enough data available\n");
        dll_clear(dll);
        free(dll);
        return 3;
    }

    printf("Choose sorting (0 or 1): ");
    int choice;
    if (scanf("%d", &choice) != 1) {
        printf("Incorrect input\n");
        dll_clear(dll);
        free(dll);
        return 1;
    }
    if (choice != 0 && choice != 1)
    {
        printf("Incorrect input data\n");
        dll_clear(dll);
        free(dll);
        return 2;
    }

    if (choice == 0)
    {
        if (dll_sort_asc(dll) != 0)
        {
            printf("Failed to sort\n");
            dll_clear(dll);
            free(dll);
            return 1;
        }
    }
    else
    {
        if (dll_sort_desc(dll) != 0)
        {
            printf("Failed to sort\n");
            dll_clear(dll);
            free(dll);
            return 1;
        }
    }

    dll_display(dll);
    dll_display_reverse(dll);

    dll_clear(dll);
    free(dll);

    return 0;
}


