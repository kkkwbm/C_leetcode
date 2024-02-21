#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "tested_declarations.h"
#include "rdebug.h"

int main(void) {
    struct linked_list_t *ll1 = ll_create();
    struct linked_list_t *ll2 = ll_create();

    if (!ll1 || !ll2)
    {
        printf("Failed to allocate memory\n");
        ll_clear(ll1);
        ll_clear(ll2);
        free(ll1);
        free(ll2);
        return 8;
    }

    printf("Podaj liczby do pierwszej listy ");
    int input;
    while (1)
    {
        int res = scanf("%d", &input);
        if (res == 1 && input != -1)
        {
            if (ll_push_back(ll1, input) != 0)
            {
                printf("Failed to allocate memory\n");
                ll_clear(ll1);
                ll_clear(ll2);
                free(ll1);
                free(ll2);
                return 8;
            }
        }
        else if (res != 1)
        {
            printf("Incorrect input\n");
            ll_clear(ll1);
            ll_clear(ll2);
            free(ll1);
            free(ll2);
            return 1;
        }
        else if (input == -1) break;
    }

    if (ll_is_empty(ll1) == -1)
    {
        printf("Incorrect input\n");
        ll_clear(ll1);
        ll_clear(ll2);
        free(ll1);
        free(ll2);
        return 1;
    }

    printf("Podaj liczby do drugiej listy ");
    while (1)
    {
        int res = scanf("%d", &input);
        if (res == 1 && input != -1)
        {
            if (ll_push_back(ll2, input) != 0)
            {
                printf("Failed to allocate memory\n");
                ll_clear(ll1);
                ll_clear(ll2);
                free(ll1);
                free(ll2);
                return 8;
            }
        }
        else if (res != 1)
        {
            printf("Incorrect input\n");
            ll_clear(ll1);
            ll_clear(ll2);
            free(ll1);
            free(ll2);
            return 1;
        }
        else if (input == -1) break;
    }


    if (ll_is_empty(ll2) == 1 || ll_is_empty(ll1) == 1)
    {
        printf("Not enough data available\n");
        ll_clear(ll1);
        ll_clear(ll2);
        free(ll1);
        free(ll2);
        return 3;
    }

    else if (ll_is_empty(ll2) == -1)
    {
        printf("Incorrect input\n");
        ll_clear(ll1);
        ll_clear(ll2);
        free(ll1);
        free(ll2);
        return 1;
    }

    int sequencesRemoved = ll_remove_sequence(ll1, ll2);
    if (sequencesRemoved == -1)
    {
        printf("Incorrect input\n");
        ll_clear(ll1);
        ll_clear(ll2);
        free(ll1);
        free(ll2);
        return 1;
    }

    printf("%d\n", sequencesRemoved);

    if (ll_is_empty(ll1) == 1) printf("Nothing to show\n");
    else if (ll_is_empty(ll1) == -1)
    {
        printf("Incorrect input\n");
        ll_clear(ll1);
        ll_clear(ll2);
        free(ll1);
        free(ll2);
        return 1;
    }
    else ll_display(ll1);

    ll_clear(ll1);
    ll_clear(ll2);
    free(ll1);
    free(ll2);

    return 0;
}

