#include "defs.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2)
    {
        printf("Not enough arguments\n");
        return 9;
    }

    struct node_t *head = NULL;

    for (int i = 1; i < argc; i++)
    {
        if (insert(&head, argv[i]) != 0)
        {
            clear(&head);
            return 1;
        }
    }

    for (struct node_t *current = head; current != NULL; current = current->next)
    {
        printf("%s %u\n", current->word, current->bits);
    }

    reverse(&head);

    for (struct node_t *current = head; current != NULL; current = current->next)
    {
        printf("%s %u\n", current->word, current->bits);
    }

    clear(&head);

    return 0;
}