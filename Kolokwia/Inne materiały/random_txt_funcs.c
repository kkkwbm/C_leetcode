#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

/*
 Napisz funkcję o zmiennej liście argumentów, która spośród łańcuchów znakowych przekazanych
jako argumenty funkcji wyznaczy najdłuższy. Funkcja powinna zwracać wskaźnik do najdłuższego
łańcucha znakowego.
Przykładowo:
dla napisów: "ala" ,"ma", "kota" funkcja powinna zwrócić wskaźnik do "kota"
dla napisów: "ala" ,"ma", "kota", "w" ,"kropki" funkcja powinna zwrócić wskaźnik do "kropki"
 */


const char* find_largest_string(int size, ...) {
    va_list args;
    va_start(args, size);

    const char* longest = NULL;
    int max_length = 0;
    const char* temp;
    for (int i = 0; i < size; i++) {

        temp = va_arg(args, const char*);
        int length = strlen(temp);

        if (length > max_length) {
            longest = temp;
            max_length = length;
        }
    }

    va_end(args);
    return longest;
}

/*
Napisz funkcję o zmiennej liczbie argumentów, która będzie alokowała tablicę wektorów liczb
całkowitych. Pierwszym argumentem funkcji ma być liczba wektorów w tablicy, kolejnymi liczb
elementów poszczególnych wektorów.

int** array_of_int_vectors = alloc_array_of_int_vectors(5, 10, 20, 30, 40, 50);
Alokuje tablicę 5 wektorów o liczbach elementów 10, 20, 30, 40 i 50.

int** array_of_int_vectors = alloc_array_of_int_vectors(3, 10, 10, 10);
Alokuje tablicę 3 dziesięcioelementowych wektorów

*/

int ** alloc_array_of_int_vectors(int size, ...) {

    int **array_of_int_vectors = calloc(size, sizeof(int *));
    if (array_of_int_vectors == NULL) {
        printf("Failed to allocate memory\n");
        return NULL;
    }

    va_list args;
    va_start(args, size);
    int vector_size = 0;

    for (int i = 0; i < size; i++) {
        vector_size = va_arg(args, int);
        *(array_of_int_vectors + i) = calloc(vector_size, sizeof(int));

        if (*(array_of_int_vectors + i) == NULL) {
            printf("Failed to allocate memory");
            va_end(args);
            free(array_of_int_vectors);
            return NULL;
        }
    }

    va_end(args);

    return array_of_int_vectors;
}

/*
char* strfindlongest(int n, ...)
wyszukuje pierwszy najdłuższy łańcuch spośród
podanych jako argumenty, n – liczba łańcuchów, zwraca wskaźnik do znalezionego
łańcucha lub NULL w przypadku błędu

char* strfindshortest(int n, ...)
wyszukuje pierwszy najkrótszy łańcuch spośród
podanych jako argumenty, n – liczba łańcuchów, zwraca wskaźnik do znalezionego
łańcucha lub NULL w przypadku błędu

char* strfindfirst(int n, ...)
wyszukuje pierwszy pierwszy alfabetycznie (według
kodów ASCII) łańcuch spośród podanych jako argumenty, n – liczba łańcuchów, zwraca
wskaźnik do znalezionego łańcucha lub NULL w przypadku błędu

char* strfindlast(int n, ...)
wyszukuje pierwszy ostatni alfabetycznie (według
kodów ASCII) łańcuch spośród podanych jako argumenty, n – licz
 */

char* strfindlongest(int n, ...){
    if(n <= 0) return NULL;
    va_list args;
    va_start(args, n);

    char* longest = NULL;
    int max_length = 0;
    const char* temp;
    for (int i = 0; i < n; i++) {

        temp = va_arg(args, const char*);
        int length = strlen(temp);

        if (length > max_length) {
            longest = temp;
            max_length = length;
        }
    }

    va_end(args);
    return longest;
}
char* strfindshortest(int n, ...){
    if(n <= 0) return NULL;
    va_list args;
    va_start(args, n);

    char* smallest = NULL;
    int min_length = 0;
    char* temp;
    temp = va_arg(args, char*);
    min_length = strlen(temp);
    for (int i = 1; i < n; i++) {

        temp = va_arg(args, char*);
        int length = strlen(temp);

        if (length < min_length) {
            smallest = temp;
            min_length = length;
        }
    }

    va_end(args);
    return smallest;
}
char* strfindfirst(int n, ...){
    if(n <= 0) return NULL;
    va_list args;
    va_start(args, n);

    char* first = va_arg(args, char*);
    char* temp = va_arg(args, char*);

    if(first < temp) first = temp;

    for (int i = 1; i < n; i++) {
        temp = va_arg(args, char*);
        if(first < temp) first = temp;
    }

    va_end(args);
    return first;
}
char* strfindlast(int n, ...){
    if(n <= 0) return NULL;
    va_list args;
    va_start(args, n);

    char* last = va_arg(args, char*);
    char* temp = va_arg(args, char*);

    if(last > temp) last = temp;

    for (int i = 1; i < n; i++) {
        temp = va_arg(args, char*);
        if(last > temp) last = temp;
    }

    va_end(args);
    return last;
}

int main() {
    const char* longest_str1 = find_largest_string(3, "ala", "ma", "kota",NULL);
    printf("The longest provided string is: %s\n", longest_str1);

    const char* longest_str2 = find_largest_string(5, "ala", "ma", "kota", "w", "kropki");
    printf("The longest provided string is: %s\n", longest_str2);


    int ** array_of_int_vectors = alloc_array_of_int_vectors(5, 10, 20, 30, 40, 50);
    array_of_int_vectors = alloc_array_of_int_vectors(3, 10, 10, 10);

    char* first_str = strfindfirst(5, "ala", "ma", "kota","aaala", "xyzala");
    printf("Alphabetically first provided string is: %s\n", first_str);

    char* last_str = strfindlast(5, "ala", "ma", "kota", "aaala", "xyzala");
    printf("Alphabetically last provided string is: %s\n", last_str);

    return 0;
}

