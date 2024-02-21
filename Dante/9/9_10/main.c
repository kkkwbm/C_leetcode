#include <stdio.h>
#include "tested_declarations.h"
#include "rdebug.h"

int longest_series(unsigned int x) {
    int max_streak = 0;
    int current_streak = 0;

    while (x) {
        if (x & 1)
        {
            current_streak++;
            if (current_streak > max_streak)
            {
                max_streak = current_streak;
            }
        }
        else current_streak = 0;
        x >>= 1;
    }

    return max_streak;
}

int main() {
    unsigned int value;

    printf("Podaj liczbę: ");
    if (scanf("%u", &value) != 1)
    {
        printf("Incorrect input\n");
        return 1;
    }

    printf("Wynik: %d\n", longest_series(value));
    return 0;
}

