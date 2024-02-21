#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"
#include "utils.h"

int main(int argc, char **argv) {
    if (argc < 3 || argc % 2 != 0)
    {
        printf("Not enough arguments\n");
        return 9;
    }

    struct node_t *head = NULL;
    for (int i = 2; i < argc; i += 2)
    {
        const char *word_en = *(argv + i);
        const char *word_pl = *(argv + i + 1);

        if (insert(&head, word_en, word_pl) == 2)
        {
            clear(&head);
            printf("Memory allocation error\n");
            return 2;
        }
    }

    struct node_t *current = head;
    while (current != NULL)
    {
        printf("%s %s %d\n", current->word_en, current->word_pl, current->bits);
        current = current->next;
    }

    if (reverse(&head) != 0)
    {
        clear(&head);
        printf("Failed to reverse the list\n");
        return 1;
    }

    printf("\n");

    current = head;
    while (current != NULL)
    {
        printf("%s %s %d\n", current->word_en, current->word_pl, current->bits);
        current = current->next;
    }

    clear(&head);
    return 0;
}
