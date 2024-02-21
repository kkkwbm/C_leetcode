struct node_t {
    struct node_t *next;
    int number;
};

struct list_t {
    struct node_t *head;
};

void display_from_front(const struct list_t *list) {
    struct node_t *current = list->head;
    while (current != NULL)
    {
        printf("%d ", current->number);
        current = current->next;
    }
    printf("\n");
}

void display_from_end(const struct list_t *list) {
    int length = 0;
    struct node_t *temp = list->head;
    while (temp != NULL)
    {
        length++;
        temp = temp->next;
    }

    for (int i = length; i > 0; i--)
    {
        temp = list->head;
        for (int j = 1; j < i; j++)
        {
            temp = temp->next;
        }
        printf("%d ", temp->number);
    }
    printf("\n");
}

void swap_nodes(struct list_t *list, int num1, int num2) {
    struct node_t *node1 = NULL, *node2 = NULL, *temp = list->head;

    while (temp)
    {
        if (temp->number == num1) node1 = temp;
        if (temp->number == num2) node2 = temp;
        temp = temp->next;
    }

    if (node1 && node2)
    {
        int tmp = node1->number;
        node1->number = node2->number;
        node2->number = tmp;
    }
}

void remove_node(struct list_t *list, int num) {
    struct node_t *temp = list->head, *prev = NULL;

    if (temp != NULL && temp->number == num)
    {
        list->head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->number != num)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return; // Number not found

    prev->next = temp->next;
    free(temp);
}

void free_list(struct list_t *list) {
    struct node_t *current = list->head;
    while (current != NULL)
    {
        struct node_t *next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}