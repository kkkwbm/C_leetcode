#include <stdio.h>
#include <string.h>
#include "defs.h"

int read(const char* fname, struct record_t* buffer, int count) {
    if (fname == NULL || buffer == NULL || count < 1) return 1;

    FILE *file = fopen(fname, "rb");
    if (file == NULL) return 2;

    size_t read_count = fread(buffer, sizeof(struct record_t), count, file);
    fclose(file);

    if (read_count != count) return 3;

    return 0;
}

void show2(const struct record_t* arr, int count) {
    if(arr == NULL || count <= 0) return;
    for (int i = 0; i < count; i++)
    {
        printf("%d. ", i + 1);

        if ((arr + i)->name[0] != '\0')
        {
            printf("%s %s, ", (arr + i)->name, (arr + i)->surname);

            printf("%02u/%02u/%04u ", (arr + i)->bdate.d, (arr + i)->bdate.m, (arr + i)->bdate.y);

            printf("%08x)\n", (arr->bdate.value + i));
        }
        else printf("No data\n");
    }
}

void show(const struct record_t* arr, int count) {
    if (arr == NULL || count < 1) return;

    for (int i = 0; i < count; ++i)
    {
        const struct record_t* current_record = arr + i;
        if (strlen((arr + i)->name) == 0 || strlen((arr + i)->surname) == 0)
        {
            printf("%d. No data⏎\n", i + 1);
        }
        else
        {
            printf("%d. %s %s, %02d/%02d/%04d (0x%08x)⏎\n",
                   i + 1,
                   (arr + i)->name, (arr + i)->surname,
                   (arr + i)->bdate.d, (arr + i)->bdate.m, (arr + i)->bdate.y + 1900,
                   (arr + i)->bdate.value);
        }
    }
}

int main() {
    struct record_t data[10];

    int result = read("birthdays.bin", data, 10);
    if (result == 2)
    {
        printf("Unable to open file birthdays.bin⏎\n");
        return 4;
    }
    else if (result == 3)
    {
        printf("Not enough data⏎\n");
        return 3;
    }
    else if (result != 0) return 1;

    show(data, 10);

    return 0;
}
