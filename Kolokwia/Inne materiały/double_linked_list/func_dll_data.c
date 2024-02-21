#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

struct info_t {
    char *company_name;
    int budget;
    char **names;
};

struct node_t {
    struct info_t info;
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
        printf("Company: %s, Budget: %d, Names: ", current->info.company_name, current->info.budget);

        char **name_ptr = current->info.names;
        while (*name_ptr != NULL)
        {
            printf("%s", *name_ptr);
            if (*(name_ptr + 1) != NULL) printf(", ");
            name_ptr++;
        }

        printf("\n");
        current = current->next;
    }
}

void display_from_end(const struct double_linked_list_t *list) {
    struct node_t *current = list->tail;
    while (current != NULL)
    {
        printf("Company: %s, Budget: %d, Names: ", current->info.company_name, current->info.budget);

        char **name_ptr = current->info.names;
        while (*name_ptr != NULL)
        {
            printf("%s", *name_ptr);
            if (*(name_ptr + 1) != NULL) printf(", ");
            name_ptr++;
        }

        printf("\n");
        current = current->prev;
    }
}

struct node_t *create_node(const struct info_t *info) {
    struct node_t *new_node = malloc(sizeof(struct node_t));
    if (new_node)
    {
        new_node->info = *info; // Shallow copy; ensure deep copy if needed
        new_node->next = NULL;
        new_node->prev = NULL;
    }
    return new_node;
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
   = node2;
    if (node2->prev) node2->prev->next = node2;

    // Update head and tail if necessary
    if (list->head == node1) list->head = node2;
    else if (list->head == node2) list->head = node1;

    if (list->tail == node1) list->tail = node2;
    else if (list->tail == node2) list->tail = node1;
}

void add_to_list(struct double_linked_list_t *list, struct node_t *node) {
    if (!list->head)
    {
        // The list is empty, so the new node becomes both the head and tail
        list->head = node;
        list->tail = node;
        node->prev = NULL; // No previous node
        node->next = NULL; // No next node
    }
    else
    {
        // The list is not empty, so append the new node at the end
        list->tail->next = node; // Point the current tail's next to the new node
        node->prev = list->tail; // Set the new node's prev to the current tail
        node->next = NULL;       // The new node is now the last node, so its next is NULL
        list->tail = node;       // Update the list's tail to the new node
    }
}

char **split_names(const char *str, int *count) {
    int name_count = 1;
    for (const char *p = str; *p; ++p)
    {
        if (*p == ',') ++name_count;
    }

    char **names = malloc(name_count * sizeof(char *));
    if (!names) return NULL;

    const char *start = str;
    char **current_name_ptr = names;
    for (const char *p = str; ; ++p)
    {
        if (*p == ',' || *p == '\0')
        {
            int len = p - start;
            *current_name_ptr = malloc(len + 1);
            if (!*current_name_ptr)
            {
                char **temp_ptr = names;
                while (temp_ptr < current_name_ptr)
                {
                    free(*temp_ptr);
                    temp_ptr++;
                }
                free(names);
                return NULL;
            }
            strncpy(*current_name_ptr, start, len);
            *(*current_name_ptr + len) = '\0';
            current_name_ptr++;
            start = p + 1;
        }
        if (*p == '\0') break;
    }

    *count = name_count;
    return names;
}

void read_from_file(struct double_linked_list_t *list, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file");
        return;
    }

    char line[300];
    while (fgets(line, sizeof(line), file))
    {
        struct info_t info;
        char *token = strtok(line, "|");
        info.company_name = strdup(token);

        token = strtok(NULL, "|");
        info.budget = atoi(token);

        token = strtok(NULL, "|");
        int name_count;
        info.names = split_names(token, &name_count);

        struct node_t *new_node = create_node(&info);
        add_to_list(list, new_node);
    }
    fclose(file);
}

void free_node(struct node_t *node) {
    free(node->info.company_name);

    char **name_ptr = node->info.names;
    while (*name_ptr != NULL)
    {
        free(*name_ptr);
        name_ptr++;
    }

    free(node->info.names);
    free(node);
}
void free_list(struct double_linked_list_t *list) {
    struct node_t *current = list->head;
    while (current != NULL)
    {
        struct node_t *next = current->next;
        free_node(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

int main() {
    struct double_linked_list_t list = {NULL, NULL};

    read_from_file(&list, "data.txt");

    display_from_front(&list);

    free_list(&list);
    return 0;
}