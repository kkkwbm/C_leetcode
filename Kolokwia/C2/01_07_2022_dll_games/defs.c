 #include "defs.h"

struct double_linked_list_t *dll_init() {
    struct double_linked_list_t *list = malloc(sizeof(struct double_linked_list_t));
    if (list == NULL) return NULL;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

int dll_push_back(struct double_linked_list_t *dll, struct info_t *info) {
    if(dll == NULL || info == NULL) return 2;

    struct node_t *node = malloc(sizeof(struct node_t));
    if (node == NULL) return 1;

    node->info = info;
    node->prev = dll->tail;
    node->next = NULL;

    if (dll->tail != NULL) dll->tail->next = node;

    dll->tail = node;

    if (dll->head == NULL) dll->head = node;

    return 0;
}

struct info_t *dll_find(struct double_linked_list_t *dll, char *name) {
    struct node_t *node = dll->head;
    while (node != NULL)
    {
        if (strcmp(name, node->info->name) == 0) return node->info;
        node = node->next;
    }
    return NULL;
}

struct info_t *get_info_for_team(struct double_linked_list_t *dll, char *team_name) {
    struct info_t *info = dll_find(dll, team_name);
    if (info == NULL)
    {
        info = malloc(sizeof(struct info_t));
        if (info == NULL) return NULL;
        info->name = strdup(team_name);
        if (info->name == NULL)
        {
            free(info);
            return NULL;
        }
        info->hash_value = 0;
        info->points = 0;
        info->games = 0;
        if(dll_push_back(dll, info) == 1)
        {
            free(info->name);
            free(info);
            return NULL;
        }
    }
    return info;
}

int read_table(struct double_linked_list_t **lists, const char *filename, uint8_t (*wsk)(uint8_t)) {
    if (lists == NULL || filename == NULL || wsk == NULL) return -1;
    if (*lists == NULL)
    {
        *lists = dll_init();
        if (*lists == NULL) return -4;
    }

    FILE *file = fopen(filename, "rt");
    if (file == NULL)
    {
        free_list(*lists);
        return -2;
    }

    char home_name[41], away_name[41];
    int result;
    while (!feof(file))
    {
        if (fscanf(file, "%40[^|]|%40[^|]|%d\n", home_name, away_name, &result) != 3)
        {
            free_list(*lists);
            fclose(file);
            return -3;
        }
        struct info_t *info = get_info_for_team(*lists, home_name);
        if (info == NULL)
        {
            fclose(file);
            free_list(*lists);
            return -4;
        }
        info->games++;

        if (result == 1) info->points += 3;
        if (result == 0) info->points += 1;

        info->hash_value = wsk(info->points);

        info = get_info_for_team(*lists, away_name);
        if (info == NULL)
        {
            free_list(*lists);
            fclose(file);
            return -4;
        }
        info->games++;

        if (result == 2) info->points += 3;
        if (result == 0) info->points += 1;

        info->hash_value = wsk(info->points);

        //printf("%s %s %d\n", home_name, away_name, result);
    }

    fclose(file);
    return 0;
}

void display_table_forward(const struct double_linked_list_t *lists) {
    if (lists == NULL) return;
    struct node_t *node = lists->head;
    while (node != NULL)
    {
        printf("%s: %hhu %hhu %hhu\n", node->info->name, node->info->games, node->info->points, node->info->hash_value);
        node = node->next;
    }
}

void free_list(struct double_linked_list_t *lists) {
    if (lists == NULL) return;
    struct node_t *prev;
    struct node_t *node = lists->head;
    while (node != NULL)
    {
        prev = node;
        node = node->next;
        free(prev->info->name);
        free(prev->info);
        free(prev);
    }
    free(lists);
}


