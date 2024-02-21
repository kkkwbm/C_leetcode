#include "matrix_utils.h"
#include "tested_declarations.h"
#include "rdebug.h"


int matrix_create(struct matrix_t *m, int width, int height) {
    if (!m || width <= 0 || height <= 0) return 1;

    m->width = width;
    m->height = height;

    m->ptr = malloc(height * sizeof(int *));
    if (!m->ptr) return 2;

    for (int i = 0; i < height; i++) {
        *(m->ptr + i) = malloc(width * sizeof(int));
        if (!(*(m->ptr + i)))
        {
            for (int j = 0; j < i; j++)
            {
                free(*(m->ptr + j));
            }
            free(m->ptr);
            return 2;
        }
    }

    return 0;
}

int matrix_read(struct matrix_t *m) {
    if (!m || !m->ptr || m->width <= 0 || m->height <= 0) return 1;

    for (int i = 0; i < m->height; i++)
    {
        for (int j = 0; j < m->width; j++)
        {
            if (scanf("%d", (*(m->ptr + i) + j)) != 1) return 2;
        }
    }

    return 0;
}

void matrix_display(const struct matrix_t *m) {
    if (!m || !m->ptr || m->width <= 0 || m->height <= 0) return;

    for (int i = 0; i < m->height; i++)
    {
        for (int j = 0; j < m->width; j++)
        {
            printf("%d ", *(*(m->ptr + i) + j));
        }
        printf("\n");
    }
}

void matrix_destroy(struct matrix_t *m) {
    if (!m || !m->ptr) return;

    for (int i = 0; i < m->height; i++) free(*(m->ptr + i));

    free(m->ptr);
}

void matrix_destroy_struct(struct matrix_t **m) {
    if (!m || !(*m) || !(*m)->ptr) return;

    for (int i = 0; i < (*m)->height; i++) free(*((*m)->ptr + i));

    free((*m)->ptr);
    free(*m);
    *m = NULL;
}

struct matrix_t* matrix_create_struct(int width, int height) {
    if (width <= 0 || height <= 0) return NULL;

    struct matrix_t *m = malloc(sizeof(struct matrix_t));
    if (!m) return NULL;

    m->width = width;
    m->height = height;
    m->ptr = malloc(height * sizeof(int *));
    if (!m->ptr)
    {
        free(m);
        return NULL;
    }

    for (int i = 0; i < height; i++) {
        *(m->ptr + i) = malloc(width * sizeof(int));
        if (!(*(m->ptr + i)))
        {
            for (int j = 0; j < i; j++) free(*(m->ptr + j));
            free(m->ptr);
            free(m);
            return NULL;
        }
    }
    return m;
}


struct matrix_t* matrix_transpose(const struct matrix_t *m) {
    if (!m || !m->ptr || m->width <= 0 || m->height <= 0) return NULL;

    struct matrix_t *transposed = matrix_create_struct(m->height, m->width);
    if (!transposed) return NULL;

    for (int i = 0; i < m->height; i++) {
        for (int j = 0; j < m->width; j++)
        {
            *(*(transposed->ptr + j) + i) = *(*(m->ptr + i) + j);
        }
    }

    return transposed;
}

int matrix_save_b(const struct matrix_t *m, const char *filename) {
    if (!m || !m->ptr || !filename || m->width <= 0 || m->height <= 0) return 1;

    FILE *f = fopen(filename, "wb");
    if (!f) return 2;

    if (fwrite(&m->width, sizeof(int), 1, f) != 1 ||
        fwrite(&m->height, sizeof(int), 1, f) != 1)
    {
        fclose(f);
        return 3;
    }

    for (int i = 0; i < m->height; i++)
    {
        if ((int)fwrite(*(m->ptr + i), sizeof(int), m->width, f) != m->width)
        {
            fclose(f);
            return 3;
        }
    }

    fclose(f);
    return 0;
}

int matrix_save_t(const struct matrix_t *m, const char *filename) {
    if (!m || !m->ptr || !filename || m->width <= 0 || m->height <= 0) return 1;

    FILE *f = fopen(filename, "w");
    if (!f) return 2;

    fprintf(f, "%d %d\n", m->width, m->height);
    for (int i = 0; i < m->height; i++)
    {
        for (int j = 0; j < m->width; j++)
        {
            fprintf(f, "%d ", *(*(m->ptr + i) + j));
        }
        fprintf(f, "\n");
    }

    fclose(f);
    return 0;
}

struct matrix_t* matrix_copy(const struct matrix_t *m) {
    if (!m || m->width <= 0 || m->height <= 0 || !m->ptr) return NULL;

    struct matrix_t *copy = matrix_create_struct(m->width, m->height);
    if (!copy) return NULL;

    for (int i = 0; i < m->height; i++)
    {
        for (int j = 0; j < m->width; j++)
        {
            *(*(copy->ptr + i) + j) = *(*(m->ptr + i) + j);
        }
    }

    return copy;
}

struct matrix_t* matrix_add(const struct matrix_t *m1, const struct matrix_t *m2) {
    if (!m1 || !m2 || m1->width != m2->width || m1->height != m2->height ||
        m1->width <= 0 || m1->height <= 0 || !m1->ptr || !m2->ptr) return NULL;

    struct matrix_t *result = matrix_create_struct(m1->width, m1->height);
    if (!result) return NULL;

    for (int i = 0; i < m1->height; i++)
    {
        for (int j = 0; j < m1->width; j++)
        {
            *(*(result->ptr + i) + j) = *(*(m1->ptr + i) + j) + *(*(m2->ptr + i) + j);
        }
    }

    return result;
}

struct matrix_t* matrix_load_t(const char *filename, int *err_code) {
    if(filename == NULL){
        if(err_code) *err_code = 1;
        return NULL;
    }
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        if (err_code) *err_code = 2;
        return NULL;
    }

    int width, height;
    if (fscanf(file, "%d %d", &width, &height) != 2 || width <= 0 || height <= 0) {
        fclose(file);
        if (err_code) *err_code = 3;
        return NULL;
    }

    struct matrix_t *matrix = matrix_create_struct(width, height);
    if (!matrix) {
        fclose(file);
        if (err_code) *err_code = 4;
        return NULL;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (fscanf(file, "%d", (*(matrix->ptr + i) + j)) != 1) {
                matrix_destroy_struct(&matrix);
                fclose(file);
                if (err_code) *err_code = 3;
                return NULL;
            }
        }
    }

    fclose(file);
    if (err_code) *err_code = 0;
    return matrix;
}

struct matrix_t* matrix_load_b(const char *filename, int *err_code) {
    if(filename == NULL){
        if(err_code) *err_code = 1;
        return NULL;
    }
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        if (err_code) *err_code = 2;
        return NULL;
    }

    int width, height;
    if (fread(&width, sizeof(int), 1, file) != 1 || fread(&height, sizeof(int), 1, file) != 1 ||
        width <= 0 || height <= 0)
    {
        fclose(file);
        if (err_code) *err_code = 3;
        return NULL;
    }

    struct matrix_t *matrix = matrix_create_struct(width, height);
    if (!matrix)
    {
        fclose(file);
        if (err_code) *err_code = 4;
        return NULL;
    }

    for (int i = 0; i < height; i++)
    {
        if (fread(*(matrix->ptr + i), sizeof(int), width, file) != (size_t)width)
        {
            matrix_destroy_struct(&matrix);
            fclose(file);
            if (err_code) *err_code = 3;
            return NULL;
        }
    }

    fclose(file);
    if (err_code) *err_code = 0;
    return matrix;
}

struct matrix_t* matrix_subtract(const struct matrix_t *m1, const struct matrix_t *m2) {
    if (!m1 || !m2 || m1->width != m2->width || m1->height != m2->height ||
        m1->width <= 0 || m1->height <= 0 || !m1->ptr || !m2->ptr) return NULL;

    struct matrix_t *result = matrix_create_struct(m1->width, m1->height);
    if (!result) return NULL;

    for (int i = 0; i < m1->height; i++)
    {
        for (int j = 0; j < m1->width; j++)
        {
            *(*(result->ptr + i) + j) = *(*(m1->ptr + i) + j) - *(*(m2->ptr + i) + j);
        }
    }

    return result;
}

struct matrix_t* matrix_multiply(const struct matrix_t *m1, const struct matrix_t *m2) {
    if (!m1 || !m2 || m1->width != m2->height || m1->width <= 0 || m1->height <= 0 || !m1->ptr || !m2->ptr) return NULL;

    struct matrix_t *result = matrix_create_struct(m2->width, m1->height);
    if (!result) return NULL;

    for (int i = 0; i < m1->height; i++)
    {
        for (int j = 0; j < m2->width; j++)
        {
            int sum = 0;
            for (int k = 0; k < m1->width; k++)
            {
                sum += *(*(m1->ptr + i) + k) * *(*(m2->ptr + k) + j);
            }
            *(*(result->ptr + i) + j) = sum;
        }
    }

    return result;
}
