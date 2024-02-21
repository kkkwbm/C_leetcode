#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tested_declarations.h"
#include "rdebug.h"


int load_maze(const char *filename, char ***labirynth) {
    if(filename == NULL || labirynth == NULL) return 1;
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        return 2;
    }
    char ch;

    rewind(file);
    int cols = 0;
    while ((ch = fgetc(file)) != '\n' && ch != EOF) cols++;

    if (ch == EOF && cols == 0)
    {
        fclose(file);
        free(*labirynth);
        *labirynth = NULL;
        return 3;
    }

    int rows = 1;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n') rows++;
    }

    if (ch != '\n') rows++;

    rewind(file);

    *labirynth = (char **)malloc((rows + 1) * sizeof(char *));
    if (!*labirynth)
    {
        fclose(file);
        return 4;
    }

    for (int i = 0; i < rows; i++)
    {
        *(*labirynth + i) = malloc((cols + 1) * sizeof(char));
        if (!*(*labirynth + i))
        {
            for (int j = 0; j < i; j++)
            {
                free(*(*labirynth + j));
                *(*labirynth + j) = NULL;
            }
            free(*labirynth);
            *labirynth = NULL;
            fclose(file);
            return 4;
        }

        for (int j = 0; j < cols; j++)
        {
            ch = fgetc(file);
            if (ch == EOF)
            {

                for (int k = 0; k <= i; k++)
                {
                    free(*(*labirynth + k));
                }
                free(*labirynth);
                *labirynth = NULL;

                fclose(file);
                return 3;
            }
            *(*(*labirynth + i) + j) = ch;
        }

        *(*(*labirynth + i) + cols) = '\0';

        fgetc(file);
    }
    *(*labirynth + rows) = NULL;

    fclose(file);
    return 0;
}

int solve_maze(char **maze, int x, int y) {
    if (!maze || y < 0 || !*(maze + y) || x < 0 || *(*(maze + y) + x) == '#' || *(*(maze + y) + x) == '\0') return -1;
    else
    {
        for(int i = 1 ; *(maze + i) != NULL; i++){
            if(strlen(*(maze + i)) != strlen(*(maze + i - 1))) return -1;
        }
        if (x >= (int)strlen(*(maze + y))) return -1;

        char curr = *(*(maze + y) + x);

        if (curr == '\0' || curr == '#' || curr == '*') return -1;
        if (curr == 'b') return 1;

        if (curr != 'a') *(*(maze + y) + x) = '*';
        else *(*(maze + y) + x) = 'a';

        if (solve_maze(maze, x + 1, y) == 1 ||
            solve_maze(maze, x - 1, y) == 1 ||
            solve_maze(maze, x, y + 1) == 1 ||
            solve_maze(maze, x, y - 1) == 1)
        {
            return 1;
        }

        if (curr != 'a') *(*(maze + y) + x) = ' ';
        else *(*(maze + y) + x) = 'a';

        return 0;
    }

}



void free_maze(char **maze) {
    if (maze) {
        char **temp = maze;
        while (*temp)
        {
            free(*temp);
            temp++;
        }
        free(maze);
    }
}


int main() {
    char *filename = (char *)malloc(31 * sizeof(char));
    if (!filename)
    {
        printf("Failed to allocate memory\n");
        exit(8);
    }
    char **maze;
    printf("Enter filename: ");
    scanf("%30s", filename);

    int load_status = load_maze(filename, &maze);
    switch (load_status)
    {
        case 1:
            printf("File corrupted\n");
            free(filename);
            return 6;
        case 2:
            printf("Couldn't open file\n");
            free(filename);
            return 4;
        case 3:
            printf("File corrupted\n");
            free(filename);
            return 6;
        case 4:
            printf("Failed to allocate memory\n");
            free(filename);
            return 8;
    }

    int startX = -1, startY = -1;
    int a_count = 0, b_count = 0;
    char **row = maze;
    char *col;
    int i = 0, j;
    while (*row)
    {
        j = 0;
        col = *row;
        while (*col)
        {
            if (*col == 'a')
            {
                startX = j;
                startY = i;
                a_count++;
            }
            if (*col == 'b')
            {
                b_count++;
            }
            col++;
            j++;
        }
        row++;
        i++;
    }


    if (a_count != 1 || b_count != 1)
    {
        printf("File corrupted\n");
        free(filename);
        free_maze(maze);
        return 6;
    }

    if (solve_maze(maze, startX, startY))
    {
        char **row_ptr = maze;
        while (*row_ptr)
        {
            printf("%s\n", *row_ptr);
            row_ptr++;
        }
    }
    else
    {
        printf("Couldn't find path\n");
        free(filename);
        free_maze(maze);
        return 0;
    }

    free(filename);
    free_maze(maze);
    return 0;
}



