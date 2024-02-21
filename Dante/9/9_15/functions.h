#ifndef INC_9_15_FUNCTIONS_H
#define INC_9_15_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

#define INIT_ARRAY(TYPE)\
DEFINE_ARRAY(TYPE)\
CREATE_ARRAY(TYPE)\
FREE_ARRAY(TYPE)\
SAVE_ARRAY(TYPE)\
LOAD_ARRAY(TYPE)\
SORT_ARRAY(TYPE)

#define DEFINE_ARRAY(TYPE)\
struct array_##TYPE##_t{\
    int size;\
    int capacity;\
    TYPE *data;\
};

#define CREATE_ARRAY(TYPE)\
struct array_##TYPE##_t *create_array_##TYPE (int size){\
    if (size < 1) return NULL;\
    struct array_##TYPE##_t *var = (struct array_##TYPE##_t *)malloc(sizeof(struct array_##TYPE##_t));\
    if (var == NULL) return NULL;\
    var->data = ( TYPE *) calloc(sizeof(TYPE), size);\
    if (var->data == NULL)\
    {\
        free(var);\
        return NULL;\
    }\
    var->size = 0;\
    var->capacity = size;\
    return var;\
}

#define FREE_ARRAY(TYPE)\
void free_array_##TYPE (struct array_ ##TYPE##_t *array){\
        if (array == NULL) return;\
        free(array->data);\
        free(array);\
    }


#define SAVE_ARRAY(TYPE)\
int save_array_##TYPE (const struct array_ ##TYPE##_t *array, const char *filename){\
    if (array == NULL || !array->data || filename == NULL|| array->size > array->capacity || array->size < 1 || array->capacity < 1) return 1;\
    FILE *f = fopen(filename, "wb");\
    if (!f) return 2;\
    if (!fwrite(&(array->size), sizeof(int), 1, f))\
    {\
        fclose(f);\
        return 2;\
    }\
    if (fwrite(array->data, sizeof(TYPE), (array->size), f) != (unsigned int) (array->size))\
    {\
        fclose(f);\
        return 2;\
    }\
    fclose(f);\
    return 0;\
}

#define LOAD_ARRAY(TYPE)\
int load_array_##TYPE (struct array_ ##TYPE##_t** array, const char* filename) {\
    if (array == NULL || filename == NULL) return 1;\
    *array = (struct array_##TYPE##_t*)malloc(sizeof(struct array_ ##TYPE##_t));\
    if (!(*array)) return 4;\
    FILE *f = fopen(filename, "rb");\
    if (!f)\
    {\
        free(*array);\
        return 2;\
    }\
    int size;\
    if (fread(&size, sizeof(int), 1, f) != 1)\
    {\
        fclose(f);\
        free(*array);\
        return 3;\
    }\
    if (size < 1)\
    {\
        fclose(f);\
        free(*array);\
        return 3;\
    }\
    TYPE *p = ( TYPE *)malloc(sizeof(TYPE) * size);\
    if (!p)\
    {\
        fclose(f);\
        free(*array);\
        return 4;\
    }\
    if (fread(p, sizeof(TYPE), size, f) != (unsigned int) size)\
    {\
        fclose(f);\
        free(*array);\
        free(p);\
        return 3;\
    }\
    (*array)->size = size;\
    (*array)->capacity = size;\
    (*array)->data = p;\
    fclose(f);\
    return 0;\
}

#define SORT_ARRAY(TYPE)\
int sort_array_##TYPE (struct array_##TYPE##_t *array){\
    if (!array || !array->data || array->size > array->capacity || array->size < 1 || array->capacity < 1) return 1;\
    TYPE temp = 0;\
    for (int i = 0; i < (array->size - 1); i++)\
    {\
        for (int j = 0; j < (array->size - 1 - i); j++)\
        {\
            if (*(array->data + j) > *(array->data + j + 1)) \
            {\
                temp = *(array->data + j);\
                *(array->data + j) = *(array->data + j + 1);\
                *(array->data + j + 1) = temp;\
            }\
        }\
    }\
    return 0;\
}

#endif //INC_9_15_FUNCTIONS_H
