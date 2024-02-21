#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"
#include "tested_declarations.h"
#include "rdebug.h"

int main() {
    struct doubly_linked_list_t* dll = dll_create();
    if (dll == NULL)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    int option;
    int value;
    int index;
    int err_code;
    int valid;

    while (1) {
        printf("Co chcesz zrobić?\n");
        /*
        0 - Zakończenie działania programu - dll_clear
        1 - Dodanie elementu na koniec listy - dll_push_back
        2 - Usunięcie ostatniego elementu z listy - dll_pop_back
        3 - Dodanie elementu na początek listy - dll_push_front
        4 - Usunięcie pierwszego elementu z listy - dll_pop_front
        5 - Dodanie elementu do listy na podanym indeksie - dll_insert
        6 - Usunięcie elementu spod podanego indeksu - dll_remove
        7 - Wyświetlenie wartości ostatniego elementu listy - dll_back
        8 - Wyświetlenie wartości pierwszego elementu listy
        9 - Sprawdzenie, czy lista jest pusta
        10 - Wyświetlenie liczby elementów w liście
        11 - Usunięcie wszystkich elementów z listy
        12 - Wyświetlenie wartości elementu spod podanego indeksu
        13 - Wyświetlenie wartości wszystkich elementów listy
        14 - Wyświetlenie wartości wszystkich elementów listy od końca
         */

        if (scanf("%d", &option) != 1)
        {
            printf("Incorrect input\n");
            dll_clear(dll);
            free(dll);
            return 1;
        }

        switch (option) {
            case 0:
                dll_clear(dll);
                free(dll);
                return 0;

            case 1:
                printf("Podaj liczbę: ");
                if (scanf("%d", &value) != 1)
                {
                    printf("Incorrect input\n");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                valid = dll_push_back(dll, value);
                if (valid == 1) printf("Failed to add element\n");
                else if(valid == 2)
                {
                    printf("Failed to allocate memory\n");
                    dll_clear(dll);
                    free(dll);
                    return 8;
                }
                break;

            case 2:
                if (dll_is_empty(dll) == 1)
                {
                    printf("List is empty\n");
                    break;
                }

                value = dll_pop_back(dll, &err_code);
                if (value == 0 && err_code == 1)
                {
                    printf("Failed to remove element\n");
                }
                printf("%d\n", value);
                break;

            case 3:
                printf("Podaj liczbę: ");
                if (scanf("%d", &value) != 1) {
                    printf("Incorrect input\n");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                valid = dll_push_front(dll, value);
                if (valid == 1) printf("Failed to add element\n");
                else if(valid == 2)
                {
                    printf("Failed to allocate memory\n");
                    dll_clear(dll);
                    free(dll);
                    return 8;
                }
                break;

            case 4:
                if (dll_is_empty(dll) == 1)
                {
                    printf("List is empty\n");
                    break;
                }

                value = dll_pop_front(dll, &err_code);
                if (value == 0 && err_code == 1)
                {
                    printf("Failed to remove element\n");
                }
                printf("%d\n", value);
                break;

            case 5:
                printf("Podaj liczbę: ");
                if (scanf("%d", &value) != 1) {
                    printf("Incorrect input\n");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                printf("Podaj indeks: ");
                if (scanf("%d", &index) != 1) {
                    printf("Incorrect input\n");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                if(index > dll_size(dll))
                {
                    printf("Index out of range\n");
                    break;
                }
                valid = dll_insert(dll, index, value);
                if (valid == 1)
                {
                    printf("Failed to insert element\n");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                else if(valid == 2)
                {
                    printf("Failed to allocate memory\n");
                    dll_clear(dll);
                    free(dll);
                    return 8;
                }
                break;

            case 6:
                if (dll_is_empty(dll) == 1)
                {
                    printf("List is empty\n");
                    break;
                }
                printf("Podaj indeks: ");
                if (scanf("%d", &index) != 1)
                {
                    printf("Incorrect input\n");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }

                if(index > dll_size(dll))
                {
                    printf("Index out of range\n");
                    break;
                }
                value = dll_remove(dll, index, &err_code);
                if (value == 0 && err_code == 1)
                {
                    printf("Failed to remove element\n");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                else printf("%d\n", value);
                break;

            case 7:
                if (dll_is_empty(dll) == 1)
                {
                    printf("List is empty\n");
                    break;
                }

                value = dll_back(dll, &err_code);
                if (value == 0 && err_code == 1)
                {
                    printf("Failed to get last element\n");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                else printf("%d\n", value);
                break;

            case 8:
                if (dll_is_empty(dll) == 1)
                {
                    printf("List is empty\n");
                    break;
                }
                value = dll_front(dll, &err_code);
                if (value == 0 && err_code == 1)
                {
                    printf("Failed to get first element\n");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                else printf("%d\n", value);
                break;

            case 9:
                if (dll_is_empty(dll) == 1)
                {
                    printf("1\n");
                    break;
                }
                else printf("0\n");
                break;

            case 10:
                printf("Liczba elementów w liście: %d\n", dll_size(dll));
                break;

            case 11:
                dll_clear(dll);
                printf("List cleared\n");
                break;

            case 12:
                if (dll_is_empty(dll) == 1)
                {
                    printf("List is empty\n");
                    break;
                }

                printf("Podaj indeks: ");
                if (scanf("%d", &index) != 1)
                {
                    printf("Incorrect input\n");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }

                if(index > dll_size(dll))
                {
                    printf("Index out of range\n");
                    break;
                }

                value = dll_at(dll, index, &err_code);
                if (value == 0 && err_code == 1)
                {
                    printf("Failed to get element\n");
                }
                else printf("%d\n", value);
                break;

            case 13:
                dll_display(dll);
                break;

            case 14:
                dll_display_reverse(dll);
                break;

            default:
                printf("Incorrect input data\n");
                break;
        }
    }

    return 0;
}

