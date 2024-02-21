#include <stdio.h>
#include "circular_buffer.h"


int main()
{
    printf("Podaj rozmiar bufora:");
    int buff_number;
    int valid;
    struct circular_buffer_t * buff;
    valid = scanf("%i",&buff_number);
    if(valid == 0)
    {
        printf("incorrect input");
        return 1;
    }
    if(buff_number < 1)
    {
        printf("incorrect input data");
        return 2;
    }
    valid = circular_buffer_create_struct(&buff, buff_number);
    if(valid == 2)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    int tryb;
    int liczba;
    while (1)
    {
        /*
        -6 4 0 -2 5 0 3 -7 -10
        printf("0 - Zakonczenie dzialania programu.\n");
        printf("1 - Dodanie elementu do tablicy.\n");
        printf("2 - Pobranie ostatnio dodanego elementu do bufora.\n");
        printf("3 - Pobranie najwczesniej dodanego elementu do bufora. \n");
        printf("4 - Wyswietlanie calej zawartosci bufora.\n");
        printf("5 - Sprawdzanie czy bufor jest pusty.\n");
        printf("6 - Sprawdzanie czy bufor jest pelny.\n");
         */
        printf("Co chcesz zrobic?");
        valid = scanf(" %i", &tryb);
        if(valid == 0)
        {
            circular_buffer_destroy_struct(&buff);
            printf("Incorrect input\n");
            return 1;
        }
        if(tryb == 0)
        {
            circular_buffer_destroy_struct(&buff);
            return 0;
        }
        else if(tryb == 1)
        {
            printf("Podaj liczbe: ");
            valid = scanf(" %i", &liczba);
            if(valid == 0)
            {
                printf("Incorrect input\n");
                circular_buffer_destroy_struct(&buff);
                return 1;
            }
            else circular_buffer_push_back(buff, liczba);
        }
        else if(tryb == 2)
        {
            if(circular_buffer_empty(buff) == 1) printf("Buffer is empty\n");
            else printf("%i\n", circular_buffer_pop_back(buff, 0));
        }
        else if(tryb == 3)
        {
            if(circular_buffer_empty(buff) == 1) printf("Buffer is empty\n");
            else printf("%i\n", circular_buffer_pop_front(buff, 0));
        }
        else if(tryb == 4)
        {
            if(circular_buffer_empty(buff) == 1) printf("Buffer is empty\n");
            else circular_buffer_display(buff);
        }
        else if(tryb == 5) printf("%i\n", circular_buffer_empty(buff));
        else if(tryb == 6) printf("%i\n", circular_buffer_full(buff));
        //else if(tryb == 7) printf("%d %d %d\n", buff.begin, buff.end, buff.capacity);
        else if (tryb < 0 || tryb > 6) printf("Incorrect input data\n");
    }
}