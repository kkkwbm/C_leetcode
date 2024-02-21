struct node_t {
    int number;
    struct node_t *next;
    struct node_t *prev;
};
struct double_linked_list_t {
    struct node_t *head;
    struct node_t *tail;
};


void display_from_front(const struct double_linked_list_t *list) {
    struct node_t *current = list->head;
    while (current != NULL)
    {
        printf("%d ", current->number);
        current = current->next;
    }
    printf("\n");
}

void display_from_end(const struct double_linked_list_t *list) {
    struct node_t *current = list->tail;
    while (current != NULL)
    {
        printf("%d ", current->number);
        current = current->prev;
    }
    printf("\n");
}

void swap_nodes(struct double_linked_list_t *list, struct node_t *node1, struct node_t *node2) {
    if (node1 == node2) return;

    // Swap prev pointers
    struct node_t *temp = node1->prev;
    node1->prev = node2->prev;
    node2->prev = temp;

    // Swap next pointers
    temp = node1->next;
    node1->next = node2->next;
    node2->next = temp;

    // Fix adjacent nodes
    if (node1->next) node1->next->prev = node1;
    if (node1->prev) node1->prev->next = node1;
    if (node2->next) node2->next->prev = node2;
    if (node2->prev) node2->prev->next = node2;

    // Update head and tail if necessary
    if (list->head == node1) list->head = node2;
    else if (list->head == node2) list->head = node1;

    if (list->tail == node1) list->tail = node2;
    else if (list->tail == node2) list->tail = node1;
}


void remove_node(struct double_linked_list_t *list, struct node_t *node) {
    if (node->prev) node->prev->next = node->next;
    else list->head = node->next;

    if (node->next) node->next->prev = node->prev;
    else list->tail = node->prev;
}

void free_list(struct double_linked_list_t *list) {
    struct node_t *current = list->head;
    while (current != NULL)
    {
        struct node_t *next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
}
