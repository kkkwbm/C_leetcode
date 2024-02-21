#include "defs.h"
#include <stdio.h>
#include <string.h>


static char *my_strdup(const char *s) {
    char *dup = malloc(strlen(s) + 1);
    if (dup) strcpy(dup, s);
    return dup;
}

static int find_category_index(struct categories_t **categories, int size, const char *name) {
    struct categories_t **cat_ptr = categories;

    for (int i = 0; i < size; ++i)
    {
        if (strcmp((*cat_ptr)->name, name) == 0) return i;
        cat_ptr++;
    }

    return -1;
}

int read_categories(const char *filename, struct categories_t ***categories) {
    if (!filename || !categories) return 1;

    FILE *file = fopen(filename, "r");
    if (!file) return 2;

    char category_name[41], product_name[61];
    unsigned int price;
    int count = 0;
    *categories = NULL;

    while (fscanf(file, "%40[^|]|%60[^|]|%u\n", category_name, product_name, &price) == 3)
    {
        int category_index = find_category_index(*categories, count, category_name);

        if (category_index == -1)
        {
            struct categories_t **temp = realloc(*categories, (count + 1) * sizeof(struct categories_t *));
            if (!temp)
            {
                fclose(file);
                return 4;
            }
            *categories = temp;

            struct categories_t *new_category = malloc(sizeof(struct categories_t));
            if (!new_category)
            {
                fclose(file);
                return 4;
            }

            *(temp + count) = new_category;
            new_category->name = my_strdup(category_name);
            new_category->products = malloc(sizeof(struct products_t));
            if (!new_category->products)
            {
                fclose(file);
                return 4;
            }
            new_category->products->product_name = my_strdup(product_name);
            new_category->products->price = price;
            new_category->count = 1;
            count++;
        }
        else
        {
            struct categories_t *cat = *(*categories + category_index);
            struct products_t *prod_temp = realloc(cat->products, (cat->count + 1) * sizeof(struct products_t));
            if (!prod_temp)
            {
                fclose(file);
                return 4;
            }
            cat->products = prod_temp;
            struct products_t *new_product = prod_temp + cat->count;
            new_product->product_name = my_strdup(product_name);
            new_product->price = price;
            cat->count++;
        }
    }

    struct categories_t **temp = realloc(*categories, (count + 1) * sizeof(struct categories_t *));
    if (!temp)
    {
        fclose(file);
        return 4;
    }
    *categories = temp;
    *(temp + count) = NULL;

    fclose(file);
    return 0;
}

int read_categories_2(const char *filename, struct categories_t ***categories) {
    if (!filename || !categories) return 1;

    FILE *file = fopen(filename, "r");
    if (!file) return 2;

    char input[110];
    int count = 0;
    *categories = NULL;

    while (fgets(input, sizeof(input), file) != NULL)
    {
        char *category_name = strtok(input, "|");
        char *product_name = strtok(NULL, "|");
        char *price_str = strtok(NULL, "\n");

        if (!category_name || !product_name || !price_str)
        {
            fclose(file);
            return 3;
        }

        unsigned int price = (unsigned int) strtol(price_str, NULL, 10);

        int category_index = find_category_index(*categories, count, category_name);

        if (category_index == -1)
        {
            struct categories_t **temp = realloc(*categories, (count + 1) * sizeof(struct categories_t *));
            if (!temp)
            {
                fclose(file);
                return 4;
            }
            *categories = temp;

            struct categories_t *new_category = malloc(sizeof(struct categories_t));
            if (!new_category)
            {
                fclose(file);
                return 4;
            }

            *(temp + count) = new_category;
            new_category->name = my_strdup(category_name);
            new_category->products = malloc(sizeof(struct products_t));
            if (!new_category->products)
            {
                fclose(file);
                return 4;
            }
            new_category->products->product_name = my_strdup(product_name);
            new_category->products->price = price;
            new_category->count = 1;
            count++;
        }
        else
        {
            struct categories_t *cat = *(*categories + category_index);
            struct products_t *prod_temp = realloc(cat->products, (cat->count + 1) * sizeof(struct products_t));
            if (!prod_temp)
            {
                fclose(file);
                return 4;
            }
            cat->products = prod_temp;
            struct products_t *new_product = prod_temp + cat->count;
            new_product->product_name = my_strdup(product_name);
            new_product->price = price;
            cat->count++;
        }
    }

    struct categories_t **temp = realloc(*categories, (count + 1) * sizeof(struct categories_t *));
    if (!temp)
    {
        fclose(file);
        return 4;
    }
    *categories = temp;
    *(temp + count) = NULL;

    fclose(file);
    return 0;
}

void display_categories(struct categories_t **categories) {
    if (!categories) return;

    struct categories_t **category_ptr = categories;
    while (*category_ptr != NULL)
    {
        printf("%s:\n", (*category_ptr)->name);

        products_t *product_ptr = (*category_ptr)->products;
        for (unsigned int j = 0; j < (*category_ptr)->count; ++j)
        {
            printf("%d. %s - %u\n", j + 1, (product_ptr + j)->product_name, (product_ptr + j)->price);
        }
        category_ptr++;
    }
}

void free_categories(struct categories_t **categories) {
    if (!categories) return;

    struct categories_t **category_ptr = categories;
    while (*category_ptr != NULL)
    {
        products_t *product_ptr = (*category_ptr)->products;
        for (unsigned int j = 0; j < (*category_ptr)->count; ++j)
        {
            free((product_ptr + j)->product_name);
        }
        free((*category_ptr)->products);
        free((*category_ptr)->name);
        free(*category_ptr);
        category_ptr++;
    }
    free(categories);
}