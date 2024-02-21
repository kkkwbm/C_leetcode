#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tested_declarations.h"
#include "rdebug.h"

int main() {
    char *filename = malloc(40 * sizeof(char));
    if (filename == NULL)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Podaj nazwe pliku: ");
    scanf("%39s", filename);

    printf("Co chcesz teraz zrobić: ");
    int choice;
    if (scanf("%d", &choice) != 1)
    {
        printf("Incorrect input\n");
        free(filename);
        return 1;
    }

    struct dictionary_t *dict = NULL;
    int err_code = 0;

    switch (choice)
    {
        case 0:
            dict = load_dictionary_b(filename, &err_code);
            if (dict == NULL)
            {
                if (err_code == 2)
                {
                    printf("Couldn't open file\n");
                    free(filename);
                    return 4;
                }
                else if (err_code == 3)
                {
                    printf("File corrupted\n");
                    free(filename);
                    return 6;
                }
                else
                {
                    printf("Failed to allocate memory\n");
                    free(filename);
                    return 8;
                }
            }
            break;
        case 1:
        {
            FILE *f = fopen(filename, "r");
            if (f == NULL)
            {
                printf("Couldn't open file\n");
                free(filename);
                return 4;
            }

            dict = create_dictionary(10, &err_code);
            if (dict == NULL)
            {
                printf("Failed to allocate memory\n");
                fclose(f);
                free(filename);
                return 8;
            }

            char *word;
            word = (char *)malloc(1024 * sizeof(char));
            if (word == NULL)
            {
                printf("Failed to allocate memory\n");
                fclose(f);
                free(filename);
                destroy_dictionary(&dict);
                return 8;
            }
            while (fscanf(f, " %1023s", word) == 1)
            {
                int i, j;
                for (i = 0, j = 0; *(word + i); i++)
                {
                    if (isalpha(*(word + i)))
                    {
                        *(word + j++) = *(word + i);
                    }
                }
                *(word + j) = '\0';

                dictionary_add_word(dict, word);
            }
            fclose(f);
            free(word);
            break;
        }
        default:
            printf("Incorrect input data\n");
            free(filename);
            return 2;
    }

    char *alpha_filename = malloc((strlen(filename) + 7) * sizeof(char));
    char *occ_filename = malloc((strlen(filename) + 5) * sizeof(char));

    if (alpha_filename == NULL || occ_filename == NULL)
    {
        printf("Failed to allocate memory\n");
        if (alpha_filename) free(alpha_filename);
        if (occ_filename) free(occ_filename);
        destroy_dictionary(&dict);
        free(filename);
        return 8;
    }

    int len = strlen(filename);
    if (len > 4) *(filename + len - 4) = '\0';
    if(choice == 0)
    {
        strcpy(alpha_filename, filename);
        strcat(alpha_filename, "_alpha.bin");
        strcpy(occ_filename, filename);
        strcat(occ_filename, "_occ.bin");
    }
    else
    {
        strcpy(alpha_filename, filename);
        strcat(alpha_filename, "_alpha.txt");
        strcpy(occ_filename, filename);
        strcat(occ_filename, "_occ.txt");
    }



    dictionary_sort_occurence(dict);
    if (save_dictionary_b(dict, occ_filename) == 0) printf("File saved\n");
    else printf("Couldn't create file\n");

    dictionary_sort_alphabetically(dict);
    if (save_dictionary_b(dict, alpha_filename) == 0) printf("File saved\n");
    else printf("Couldn't create file\n");

    destroy_dictionary(&dict);
    free(filename);
    free(alpha_filename);
    free(occ_filename);

    return 0;
}


