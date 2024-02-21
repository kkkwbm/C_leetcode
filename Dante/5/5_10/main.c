#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "matrix_utils.h"
#include "tested_declarations.h"
#include "rdebug.h"

// Przykład nr.1
// appear.txt+in.txt*ran.bin-song.bin-quotient.txt+age.bin+lie.bin-stead.bin*late.bin+good.txt*wind.bin*paper.txt+your.bin-hope.txt*anger.bin


// Przykład nr.2
// corn.txt+middle.txt-provide.txt-division.bin*mother.txt-left.txt-several.txt-tail.txt*spell.bin+nine.txt

char* extract_filename(const char* expression, int current_pos, int *err_code) {
    if (!expression || current_pos < 0 || current_pos >= (int)strlen(expression)) return NULL;

    const char* start = expression + current_pos;
    const char* end = start;

    if(err_code != NULL) *err_code = 0;

    while (*end)
    {
        if (strstr(end, ".txt") == end)
        {
            end += 4;
            break;
        }
        else if (strstr(end, ".bin") == end)
        {
            end += 4;
            break;
        }

        if (!isalnum(*end) && *end != '.' && *end != '-')
        {
            const char* temp_end = end;
            while (temp_end > start && *(temp_end-1) != '+' && *(temp_end-1) != '*' && *(temp_end-1) != '-') temp_end--;

            if(err_code != NULL) *err_code = 1;
            return NULL;
        }

        end++;
    }

    int length = end - start;
    char* filename = (char*) malloc((length + 1) * sizeof(char));
    if (!filename) return NULL;

    strncpy(filename, start, length);
    *(filename + length) = '\0';

    return filename;
}


int main() {
    char *expression = (char *)malloc(501 * sizeof(char));
    if (expression == NULL)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Podaj wyrazenie: ");
    fgets(expression, 501, stdin);
    *(expression + strcspn(expression, "\n")) = '\0';

    struct matrix_t *result = NULL;
    struct matrix_t *temp = NULL;
    struct matrix_t *current = NULL;

    int err_code = 0;
    char* filename = extract_filename(expression, 0, &err_code);
    if(filename == NULL && err_code == 0)
    {
        printf("Failed to allocate memory\n");
        free(expression);
        return 8;
    }
    else if(filename == NULL && err_code == 1)
    {
        printf("Unsupported file format\n");
        free(expression);
        return 7;
    }
    size_t filename_length = strlen(filename);

    char* filename_2;
    size_t filename_length_2;

    if (strstr(filename, ".txt"))
    {
        result = matrix_load_t(filename, &err_code);
    }
    else if (strstr(filename, ".bin"))
    {
        result = matrix_load_b(filename, &err_code);
    }
    else
    {
        printf("Unsupported file format\n");
        if(result != NULL) matrix_destroy_struct(&result);
        if(current != NULL) matrix_destroy_struct(&current);
        if(temp != NULL) matrix_destroy_struct(&temp);
        free(expression);
        free(filename);
        return 7;
    }

    if (err_code)
    {
        if (err_code == 4)
        {
            printf("Failed to allocate memory\n");
            if(result != NULL) matrix_destroy_struct(&result);
            if(current != NULL) matrix_destroy_struct(&current);
            if(temp != NULL) matrix_destroy_struct(&temp);
            free(expression);
            free(filename);
            return 8;
        }
        if (err_code == 3)
        {
            printf("File corrupted\n");
            if(result != NULL) matrix_destroy_struct(&result);
            if(current != NULL) matrix_destroy_struct(&current);
            if(temp != NULL) matrix_destroy_struct(&temp);
            free(expression);
            free(filename);
            return 6;
        }
        else if (err_code == 2)
        {
            printf("Couldn't open file\n");
            if(result != NULL) matrix_destroy_struct(&result);
            if(current != NULL) matrix_destroy_struct(&current);
            if(temp != NULL) matrix_destroy_struct(&temp);
            free(expression);
            free(filename);
            return 4;
        }
    }

    // printf("MAIN | Openning file -> %s \n", filename);

    char operation = *(expression + strlen(filename));
    // printf("MAIN | Wartosc zmiennej operation -> %c \n", operation);

    filename_2 = extract_filename(expression, filename_length + 1, &err_code);
    if(filename_2 == NULL && err_code == 0)
    {
        printf(" \n %d \n", err_code);
        printf("Failed to allocate memory\n");
        free(expression);
        free(filename);
        return 8;
    }
    else if(filename_2 == NULL && err_code == 1)
    {
        printf("Unsupported file format\n");
        free(expression);
        free(filename);
        return 7;
    }
    filename_length_2 = strlen(filename_2);

    if (strstr(filename_2, ".txt"))
    {
        current = matrix_load_t(filename_2, &err_code);
    }
    else if (strstr(filename_2, ".bin"))
    {
        current = matrix_load_b(filename_2, &err_code);
    }
    else
    {
        printf("Unsupported file format\n");
        if(result != NULL) matrix_destroy_struct(&result);
        if(current != NULL) matrix_destroy_struct(&current);
        if(temp != NULL) matrix_destroy_struct(&temp);
        free(expression);
        free(filename);
        free(filename_2);
        return 7;
    }

    free(filename_2);

    if (err_code)
    {
        if (err_code == 4)
        {
            printf("Failed to allocate memory\n");
            if(result != NULL) matrix_destroy_struct(&result);
            if(current != NULL) matrix_destroy_struct(&current);
            if(temp != NULL) matrix_destroy_struct(&temp);
            free(expression);
            free(filename);
            return 8;
        }
        if (err_code == 3)
        {
            printf("File corrupted\n");
            if(result != NULL) matrix_destroy_struct(&result);
            if(current != NULL) matrix_destroy_struct(&current);
            if(temp != NULL) matrix_destroy_struct(&temp);
            free(expression);
            free(filename);
            return 6;
        }
        else if (err_code == 2)
        {
            printf("Couldn't open file\n");
            if(result != NULL) matrix_destroy_struct(&result);
            if(current != NULL) matrix_destroy_struct(&current);
            if(temp != NULL) matrix_destroy_struct(&temp);
            free(expression);
            free(filename);
            return 4;
        }
    }

    // printf("MAIN | Openning file -> %s \n", filename_2);

    switch (operation)
    {
        case '+':
            // printf("MAIN | Wykonanie dzialania + \n");
            if (result->width != current->width || result->height != current->height)
            {
                printf("Illegal operation\n");
                if(result != NULL) matrix_destroy_struct(&result);
                if(current != NULL) matrix_destroy_struct(&current);
                if(temp != NULL) matrix_destroy_struct(&temp);
                free(expression);
                free(filename);
                return 1;
            }
            temp = matrix_add(result, current);
            if (!temp)
            {
                printf("Failed to allocate memory\n");
                if(result != NULL) matrix_destroy_struct(&result);
                if(current != NULL) matrix_destroy_struct(&current);
                if(temp != NULL) matrix_destroy_struct(&temp);
                free(expression);
                free(filename);
                return 8;
            }
            if(result != NULL) matrix_destroy_struct(&result);
            result = temp;
            temp = NULL;
            break;
        case '-':
            // printf("MAIN | Wykonanie dzialania - \n");
            if (result->width != current->width || result->height != current->height)
            {
                printf("Illegal operation\n");
                if(result != NULL) matrix_destroy_struct(&result);
                if(current != NULL) matrix_destroy_struct(&current);
                if(temp != NULL) matrix_destroy_struct(&temp);
                free(expression);
                free(filename);
                return 1;
            }
            temp = matrix_subtract(result, current);
            if (!temp)
            {
                printf("Failed to allocate memory\n");
                if(result != NULL) matrix_destroy_struct(&result);
                if(current != NULL) matrix_destroy_struct(&current);
                if(temp != NULL) matrix_destroy_struct(&temp);
                free(expression);
                free(filename);
                return 8;
            }
            if(result != NULL) matrix_destroy_struct(&result);
            result = temp;
            temp = NULL;
            break;
        case '*':
            // printf("MAIN | Wykonanie dzialania * \n");
            if (result->width != current->height)
            {
                printf("Illegal operation\n");
                if(result != NULL) matrix_destroy_struct(&result);
                if(current != NULL) matrix_destroy_struct(&current);
                if(temp != NULL) matrix_destroy_struct(&temp);
                free(expression);
                free(filename);
                return 1;
            }
            temp = matrix_multiply(result, current);
            if (!temp)
            {
                printf("Failed to allocate memory\n");
                if(result != NULL) matrix_destroy_struct(&result);
                if(current != NULL) matrix_destroy_struct(&current);
                if(temp != NULL) matrix_destroy_struct(&temp);
                free(expression);
                free(filename);
                return 8;
            }
            if(result != NULL) matrix_destroy_struct(&result);
            result = temp;
            temp = NULL;
            break;
        default:
            break;
    }

    while (*(expression + filename_length + filename_length_2 + 2) != '\0')
    {
        operation = *(expression + filename_length + filename_length_2 + 1);
        free(filename);
        filename = extract_filename(expression, filename_length + filename_length_2 + 2, &err_code);
        if(filename == NULL && err_code == 0)
        {
            printf("Failed to allocate memory\n");
            if(result != NULL) matrix_destroy_struct(&result);
            if(current != NULL) matrix_destroy_struct(&current);
            if(temp != NULL) matrix_destroy_struct(&temp);
            free(expression);
            free(filename);
            return 8;
        }
        else if(filename == NULL && err_code == 1)
        {
            printf("Unsupported file format\n");
            if(result != NULL) matrix_destroy_struct(&result);
            if(current != NULL) matrix_destroy_struct(&current);
            if(temp != NULL) matrix_destroy_struct(&temp);
            free(expression);
            free(filename);
            return 7;
        }

        filename_length += strlen(filename) + 1;

        // printf("LOOP | Wartosc zmiennej operation -> %c \n", operation);

        matrix_destroy_struct(&current);
        if (strstr(filename, ".txt"))
        {
            current = matrix_load_t(filename, &err_code);
        }
        else if (strstr(filename, ".bin"))
        {
            current = matrix_load_b(filename, &err_code);
        }
        else
        {
            printf("Unsupported file format\n");
            if(result != NULL) matrix_destroy_struct(&result);
            if(current != NULL) matrix_destroy_struct(&current);
            if(temp != NULL) matrix_destroy_struct(&temp);
            free(expression);
            free(filename);
            return 7;
        }

        if (err_code)
        {
            if (err_code == 4)
            {
                printf("Failed to allocate memory\n");
                if(result != NULL) matrix_destroy_struct(&result);
                if(current != NULL) matrix_destroy_struct(&current);
                if(temp != NULL) matrix_destroy_struct(&temp);
                free(expression);
                free(filename);
                return 8;
            }
            if (err_code == 3)
            {
                printf("File corrupted\n");
                if(result != NULL) matrix_destroy_struct(&result);
                if(current != NULL) matrix_destroy_struct(&current);
                if(temp != NULL) matrix_destroy_struct(&temp);
                free(expression);
                free(filename);
                return 6;
            }
            else if (err_code == 2)
            {
                printf("Couldn't open file\n");
                if(result != NULL) matrix_destroy_struct(&result);
                if(current != NULL) matrix_destroy_struct(&current);
                if(temp != NULL) matrix_destroy_struct(&temp);
                free(expression);
                free(filename);
                return 4;
            }
        }

        // printf("LOOP | Opening file -> %s \n", filename);

        switch (operation)
        {
            case '+':
                // printf("LOOP | Wykonanie dzialania + \n");
                if (result->width != current->width || result->height != current->height)
                {
                    printf("Illegal operation\n");
                    if(result != NULL) matrix_destroy_struct(&result);
                    if(current != NULL) matrix_destroy_struct(&current);
                    if(temp != NULL) matrix_destroy_struct(&temp);
                    free(expression);
                    free(filename);
                    return 1;
                }
                temp = matrix_add(result, current);
                if (!temp)
                {
                    printf("Failed to allocate memory\n");
                    if(result != NULL) matrix_destroy_struct(&result);
                    if(current != NULL) matrix_destroy_struct(&current);
                    if(temp != NULL) matrix_destroy_struct(&temp);
                    free(expression);
                    free(filename);
                    return 8;
                }
                if(result != NULL) matrix_destroy_struct(&result);
                result = temp;
                temp = NULL;
                break;
            case '-':
               //  printf("LOOP | Wykonanie dzialania - \n");
                if (result->width != current->width || result->height != current->height)
                {
                    printf("Illegal operation\n");
                    if(result != NULL) matrix_destroy_struct(&result);
                    if(current != NULL) matrix_destroy_struct(&current);
                    if(temp != NULL) matrix_destroy_struct(&temp);
                    free(expression);
                    free(filename);
                    return 1;
                }
                temp = matrix_subtract(result, current);
                if (!temp)
                {
                    printf("Failed to allocate memory\n");
                    if(result != NULL) matrix_destroy_struct(&result);
                    if(current != NULL) matrix_destroy_struct(&current);
                    if(temp != NULL) matrix_destroy_struct(&temp);
                    free(expression);
                    free(filename);
                    return 8;
                }
                if(result != NULL) matrix_destroy_struct(&result);
                result = temp;
                temp = NULL;
                break;
            case '*':
                // printf("LOOP | Wykonanie dzialania * \n");
                if (result->width != current->height)
                {
                    printf("Illegal operation\n");
                    if(result != NULL) matrix_destroy_struct(&result);
                    if(current != NULL) matrix_destroy_struct(&current);
                    if(temp != NULL) matrix_destroy_struct(&temp);
                    free(expression);
                    free(filename);
                    return 1;
                }
                temp = matrix_multiply(result, current);
                if (!temp)
                {
                    printf("Failed to allocate memory\n");
                    if(result != NULL) matrix_destroy_struct(&result);
                    if(current != NULL) matrix_destroy_struct(&current);
                    if(temp != NULL) matrix_destroy_struct(&temp);
                    free(expression);
                    free(filename);
                    return 8;
                }
                if(result != NULL) matrix_destroy_struct(&result);
                result = temp;
                temp = NULL;
                break;
        }
    }
    // printf(" TEST ");
    if (result) matrix_display(result);
    if(result != NULL) matrix_destroy_struct(&result);
    if(current != NULL) matrix_destroy_struct(&current);
    if(temp != NULL) matrix_destroy_struct(&temp);
    free(expression);
    free(filename);
    return 0;
}
