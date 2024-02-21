#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct info_t {
    char *school_name;
    char *student_name;
};
struct node_t {
    struct info_t *info;
    struct node_t *next;
    struct node_t *prev;
};
struct double_linked_list_t {
    struct node_t *head;
    struct node_t *tail;
    char *school_name;
    char **surnames;
    int counter;
};


int read_list(const char *filename, struct double_linked_list_t *list) {
    FILE *file = fopen(filename, "r");
    if (!file) return 1;

    char line[110];
    while (fgets(line, sizeof(line), file))
    {
        struct node_t *new_node = malloc(sizeof(struct node_t));
        if (!new_node)
        {
            fclose(file);
            return 2;
        }

        new_node->info = malloc(sizeof(struct info_t));
        if (!new_node->info) {
            free(new_node);
            fclose(file);
            return 2;
        }

        char *school_name = strtok(line, ", ");
        char *student_name = strtok(NULL, ", ");
        char *student_surname = strtok(NULL, ", \n");

        /*
         If without spaces
         char *school_name = strtok(line, " ");
         char *student_name = strtok(NULL, " ");
         char *student_surname = strtok(NULL, " \n");
         */

        new_node->info->school_name = strdup(school_name);
        new_node->info->student_name = strdup(student_name);
        // Handle student_surname here if needed

        // Add new_node to the list
        new_node->next = NULL;
        new_node->prev = list->tail;
        if (list->tail) {
            list->tail->next = new_node;
        } else {
            list->head = new_node;
        }
        list->tail = new_node;
    }

    fclose(file);
    return 0;
}

// read list if entire data in one line
int read_list_2(const char *filename, struct double_linked_list_t *list)
        {
    FILE *file = fopen(filename, "r");
    if (!file) return 1;

    char line[1024]; // Assuming the whole line fits in this buffer
    if (fgets(line, sizeof(line), file) == NULL)
    {
        fclose(file);
        return 3; // Failed to read the line
    }
    fclose(file);

    char *token = strtok(line, " ");
    while (token != NULL) {
        char *school_name = token;
        char *student_name = strtok(NULL, " ");
        char *student_surname = strtok(NULL, " ");

        if (!student_name || !student_surname) {
            return 3; // Invalid data format
        }

        // Rest of the code to create a new node and add to the list
        // ...

        token = strtok(NULL, " "); // Move to the next school name
    }

    return 0;
}

void display_list(const struct double_linked_list_t *list) {
    struct node_t *current = list->head;
    while (current != NULL)
    {
        printf("School: %s, Student: %s\n", current->info->school_name, current->info->student_name);
        current = current->next;
    }
}

void free_list(struct double_linked_list_t *list) {
    struct node_t *current = list->head;
    while (current != NULL)
    {
        struct node_t *next = current->next;
        free(current->info->school_name);
        free(current->info->student_name);
        free(current->info);
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

int main() {
    struct double_linked_list_t list = {NULL, NULL, NULL, NULL, 0};
    int result = read_list("Students.txt", &list);
    if (result != 0)
    {
        printf("Failed to read file.\n");
        return result;
    }

    display_list(&list);
    free_list(&list);
    return 0;
}

int main_2_from_user() {
    struct double_linked_list_t list = {NULL, NULL, NULL, NULL, 0};

    char filename[256];
    printf("Enter the filename: ");
    if (fgets(filename, sizeof(filename), stdin) == NULL)
    {
        printf("Error reading filename.\n");
        return 1;
    }

    // Remove newline character if it exists
    size_t len = strlen(filename);
    if (len > 0 && filename[len - 1] == '\n') {
        filename[len - 1] = '\0';
    }

    int result = read_list(filename, &list);
    if (result != 0) {
        printf("Failed to read file.\n");
        return result;
    }

    display_list(&list);
    free_list(&list);

    return 0;
}

int main_3_from_arguments(int argc, char *argv[]) {
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];

    struct double_linked_list_t list = {NULL, NULL, NULL, NULL, 0};
    int result = read_list(filename, &list);
    if (result != 0)
    {
        fprintf(stderr, "Failed to read file %s.\n", filename);
        return result;
    }

    display_list(&list);
    free_list(&list);

    return 0;
}