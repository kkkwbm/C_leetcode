#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "tested_declarations.h"
#include "rdebug.h"

int main() {
    struct linked_list_t* list = ll_create();

    if (!list)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    while (1)
    {
        printf("Co chcesz zrobic? ");
        int choice;
        if (scanf("%d", &choice) != 1)
        {
            printf("Incorrect input\n");
            ll_clear(list);
            free(list);
            return 1;
        }

        switch (choice)
        {
            case 0:
                ll_clear(list);
                free(list);
                return 0;
            case 1:
            {
                printf("Podaj liczbe ");
                int value;
                if (scanf("%d", &value) != 1)
                {
                    printf("Incorrect input\n");
                    ll_clear(list);
                    free(list);
                    return 1;
                }
                if (ll_push_back(list, value) == 2)
                {
                    printf("Failed to allocate memory\n");
                    ll_clear(list);
                    free(list);
                    return 8;
                }
                break;
            }
            case 2:
            {
                if (ll_is_empty(list) == 1)
                {
                    printf("List is empty\n");
                    break;
                }
                int err_code;
                int popped = ll_pop_back(list, &err_code);

                if (err_code == 0) printf("%d\n", popped);
                else if (err_code == 1) printf("List is empty\n");

                break;
            }
            case 3:
            {
                printf("Podaj liczbe ");
                int value;
                if (scanf("%d", &value) != 1)
                {
                    printf("Incorrect input\n");
                    ll_clear(list);
                    free(list);
                    return 1;
                }
                if (ll_push_front(list, value) == 2)
                {
                    printf("Failed to allocate memory\n");
                    ll_clear(list);
                    free(list);
                    return 8;
                }
                break;
            }
            case 4:
            {
                if (ll_is_empty(list) == 1)
                {
                    printf("List is empty\n");
                    break;
                }
                int err_code;
                int popped = ll_pop_front(list, &err_code);

                if (err_code == 0) printf("%d\n", popped);
                else if (err_code == 1) printf("List is empty\n");

                break;
            }
            case 5:
            {
                printf("Podaj liczbe ");
                int value;
                if (scanf("%d", &value) != 1)
                {
                    printf("Incorrect input\n");
                    ll_clear(list);
                    free(list);
                    return 1;
                }
                printf("Podaj index ");
                unsigned int index;
                if (scanf("%u", &index) != 1)
                {
                    printf("Incorrect input\n");
                    ll_clear(list);
                    free(list);
                    return 1;
                }
                int result = ll_insert(list, index, value);
                if (result == 1) printf("Index out of range\n");
                else if (result == 2)
                {
                    printf("Failed to allocate memory\n");
                    ll_clear(list);
                    free(list);
                    return 8;
                }
                break;
            }
            case 6:
            {
                if (ll_is_empty(list) == 1)
                {
                    printf("List is empty\n");
                    break;
                }
                printf("Podaj index ");
                unsigned int index;
                if (scanf("%u", &index) != 1)
                {
                    printf("Incorrect input\n");
                    ll_clear(list);
                    free(list);
                    return 1;
                }
                int err_code;
                int removed = ll_remove(list, index, &err_code);
                if (err_code == 0) printf("%d\n", removed);
                else if (err_code == 1) printf("Index out of range\n");
                break;
            }
            case 7:
            {
                int err_code;
                int last = ll_back(list, &err_code);
                if (err_code == 0) printf("%d\n", last);
                else if (err_code == 1) printf("List is empty\n");
                break;
            }
            case 8:
            {
                int err_code;
                int first = ll_front(list, &err_code);
                if (err_code == 0) printf("%d\n", first);
                else if (err_code == 1) printf("List is empty\n");
                break;
            }
            case 9:
                printf("%d\n", ll_is_empty(list));
                break;
            case 10:
                printf("%d\n", ll_size(list));
                break;
            case 11:
                ll_clear(list);
                break;
            case 12:
            {
                if (ll_is_empty(list) == 1)
                {
                    printf("List is empty\n");
                    break;
                }
                printf("Podaj index ");
                unsigned int index;
                if (scanf("%u", &index) != 1)
                {
                    printf("Incorrect input\n");
                    ll_clear(list);
                    free(list);
                    return 1;
                }
                int err_code;
                int value = ll_at(list, index, &err_code);
                if (err_code == 0) printf("%d\n", value);
                else if (err_code == 1) printf("Index out of range\n");
                break;
            }
            case 13:
                if (ll_is_empty(list) == 1)
                {
                    printf("List is empty\n");
                    break;
                }
                ll_display(list);
                break;
            default:
                printf("Incorrect input data\n");
        }
    }
    return 0;
}
