char buffer[20];
while (fgets(buffer, sizeof(buffer), f) != NULL)

char text[21];
while (fscanf(file, "%20s", text) == 1)

if (fscanf(file, "%40[^|]|%40[^|]|%d\n", home_name, away_name, &result) != 3);

struct node_t *current = list->head;
struct node_t *prev = NULL;
while (current != NULL)
{
    if (strcmp(current->word->word, word) == 0)
    {
        return current;
    }
    prev = current;
    current = current->next;
}

------------------------- Double Linked List -------------------------

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

void display_table_forward(const struct double_linked_list_t *lists) {
    if (lists == NULL) return;
    struct node_t *node = lists->head;
    while (node != NULL)
    {
        printf();
        node = node->next;
    }
}

*lists = dll_init();
struct double_linked_list_t *dll_init() {
    struct double_linked_list_t *list = malloc(sizeof(struct double_linked_list_t));
    if (list == NULL) return NULL;
    list->head = NULL;
    list->tail = NULL;
    return list;
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

void display_from_end(const struct double_linked_list_t *list) {
    struct node_t *current = list->tail;
    while (current != NULL)
    {
        printf("%d ", current->number);
        current = current->prev;
    }
    printf("\n");
}


------------------------- Linked List -------------------------

void list_init(struct list_t *list) {
    if(list == NULL) return;
    list->head = NULL;
}

int list_clear(struct list_t* list) {
    if (list == NULL) return -1;

    struct node_t* current = list->head;
    while (current != NULL)
    {
        struct node_t* next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;

    return 0;
}

void list_print(const struct list_t* list) {
    if (list == NULL) return;

    if (list->head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    struct node_t* current = list->head;
    while (current != NULL)
    {
        printf();
        current = current->next;
    }
}


if (*list == NULL)
{
    *list = malloc(sizeof(struct list_t));
    if (*list == NULL)
    {
        fclose(file);
        return 3;
    }
    (*list)->head = NULL;
}



------------------------- Main -------------------------
int main(int argc, char* argv[]) // char**argv


if (argc != 3)
{
    printf("Wrong number of parameters\n");
    return -1;
}

FILE* file = fopen(argv[1], "r");
if (file == NULL)
{
    printf("File open error\n");
    return -3;
}

int insert(struct node_t **head, const char *word_en, const char *word_pl);
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

struct double_linked_list_t *list = NULL;

for (int i = 1; i < argc; i++)
{
    int r = read_table(&list, *(argv + i), count01_uint8_t);
    if (r == -2)
    {
        printf("Couldn't open file");
        //free_list(list);
        return 4;
    }
    if (r == -3)
    {
        printf("File corrupted");
        //free_list(list);
        return 6;
    }
    if (r == -4)
    {
        printf("Failed to allocate memory");
        //free_list(list);
        return 8;
    }
}

------------------------- Macro -------------------------
#define CREATE_FUNCTION_COUNT10(TYPE)
TYPE count10_##TYPE(TYPE arg)

0b ULL

if(((arg >> i) & 1) == 1)

for(unsigned int i = 1; i < sizeof(TYPE) * 8; i++)

while (value != 0)
{
    if (value & 1) count_ones++;
    else count_zeros++;
    value >>= 1;
}