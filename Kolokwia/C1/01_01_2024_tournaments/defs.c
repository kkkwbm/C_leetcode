#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

void free_tournaments(struct tournament_t **tournaments) {
    if (!tournaments) return;

    struct tournament_t **current_tournament = tournaments;
    while (*current_tournament)
    {
        struct match_t *match = (*current_tournament)->matches;
        for (size_t i = 0; i < (*current_tournament)->number_of_matches; i++, match++)
        {
            free(match->home);
            free(match->away);
        }
        free((*current_tournament)->matches);
        free(*current_tournament);
        current_tournament++;
    }
    free(tournaments);
}

int read_tournaments(const char *filename, struct tournament_t ***tournaments) {
    if(filename == NULL) return -1;
    FILE *file = fopen(filename, "r");
    if (!file) return 2;

    char input[110];
    *tournaments = NULL;
    struct tournament_t **current_tournament_ptr = NULL;
    int count = 0;

    while (fgets(input, sizeof(input), file))
    {
        if (strstr(input, "World Cup"))
        {
            *tournaments = realloc(*tournaments, (count + 1 + 1) * sizeof(struct tournament_t *)); // +1 for the new tournament, +1 for NULL terminator
            if (!*tournaments)
            {
                fclose(file);
                return 4;
            }

            current_tournament_ptr = *tournaments + count;
            *current_tournament_ptr = malloc(sizeof(struct tournament_t));
            if (!*current_tournament_ptr) {
                fclose(file);
                free_tournaments(tournaments);
                return 4;
            }

            sscanf(input, "World Cup %hu", &((*current_tournament_ptr)->year));
            (*current_tournament_ptr)->number_of_matches = 0;
            (*current_tournament_ptr)->matches = NULL;

            struct match_t *current_match_ptr = NULL;
            size_t match_count = 0;
            while (fgets(input, sizeof(input), file) && !strstr(input, "World Cup"))
            {
                if (*input == '\n' || *input == '\0') continue;

                (*current_tournament_ptr)->matches = realloc((*current_tournament_ptr)->matches, (match_count + 1) * sizeof(struct match_t));
                if (!(*current_tournament_ptr)->matches)
                {
                    fclose(file);
                    free_tournaments(tournaments);
                    return 4;
                }

                current_match_ptr = (*current_tournament_ptr)->matches + match_count; // Move pointer to the new match position
                char *token = strtok(input, "|");
                if (token)
                {
                    current_match_ptr->home = strdup(token);
                    token = strtok(NULL, "|");
                }
                if (token)
                {
                    current_match_ptr->away = strdup(token);
                    token = strtok(NULL, "|");
                }
                if (token)
                {
                    current_match_ptr->result = (unsigned short)atoi(token);
                }

                if (!current_match_ptr->home || !current_match_ptr->away)
                {
                    fclose(file);
                    free_tournaments(tournaments);
                    return 4;
                }

                match_count++;
            }
            (*current_tournament_ptr)->number_of_matches = match_count;
            count++;
            if (strstr(input, "World Cup")) fseek(file, -strlen(input), SEEK_CUR); // If another tournament title was read, rewind the file pointer
        }
    }

    if (*tournaments)
    {
        *(*tournaments + count) = NULL;
    }

    fclose(file);
    return 0;
}

void display_tournaments(struct tournament_t **tournaments) {
    if (!tournaments) return;

    for (struct tournament_t **current_tournament_ptr = tournaments; *current_tournament_ptr; ++current_tournament_ptr) {
        printf("World Cup %hu\n", (*current_tournament_ptr)->year);

        struct match_t *current_match_ptr = (*current_tournament_ptr)->matches;
        for (size_t j = 0; j < (*current_tournament_ptr)->number_of_matches; ++j, ++current_match_ptr)
        {
            if (current_match_ptr->home && current_match_ptr->away)
            {
                printf("%zu: %s vs %s %hu\n", j + 1, current_match_ptr->home, current_match_ptr->away, current_match_ptr->result);
            }
        }
    }
}