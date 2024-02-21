#include "defs.h"


void free_tournaments(struct tournament_t *tournaments, int size) {
    if (tournaments == NULL || size <= 0) return;

    struct tournament_t *current_tournament = tournaments;
    for (int i = 0; i < size; ++i, ++current_tournament)
    {
        struct entry_t **current_entry = current_tournament->table;
        for (size_t j = 0; j < current_tournament->number_of_teams; ++j)
        {
            free((*current_entry)->name);
            free(*current_entry);
            current_entry++;
        }
        free(current_tournament->table);
    }

    free(tournaments);
}

struct entry_t *find_or_add_team(struct tournament_t *tournament, const char *team_name) {
    struct entry_t **current_team = tournament->table;
    for (size_t i = 0; i < tournament->number_of_teams; i++, current_team++)
    {
        if (strcmp((*current_team)->name, team_name) == 0)
        {
            return *current_team;
        }
    }

    struct entry_t *new_team = malloc(sizeof(struct entry_t));
    if (new_team == NULL) return NULL;

    new_team->name = strdup(team_name);
    if (new_team->name == NULL)
    {
        free(new_team);
        return NULL;
    }

    new_team->points = 0;
    new_team->matches = 0;

    struct entry_t **new_table = realloc(tournament->table, (tournament->number_of_teams + 1) * sizeof(struct entry_t *));
    if (new_table == NULL)
    {
        free(new_team->name);
        free(new_team);
        return NULL;
    }

    tournament->table = new_table;
    *(tournament->table + tournament->number_of_teams) = new_team;
    tournament->number_of_teams++;

    return new_team;
}

void update_tournament(struct tournament_t *tournament, const char *home, const char *away, int result) {
    struct entry_t *home_team = find_or_add_team(tournament, home);
    struct entry_t *away_team = find_or_add_team(tournament, away);

    if (home_team == NULL || away_team == NULL) {
        if (home_team != NULL && find_or_add_team(tournament, home) == home_team)
        {
            free(home_team->name);
            free(home_team);
        }
        if (away_team != NULL && find_or_add_team(tournament, away) == away_team)
        {
            free(away_team->name);
            free(away_team);
        }
        return;
    }

    home_team->matches++;
    away_team->matches++;

    switch (result)
    {
        case 1:
            home_team->points += 3;
            break;
        case 2:
            away_team->points += 3;
            break;
        case 0:
            home_team->points += 1;
            away_team->points += 1;
            break;
        default:
            printf("Error!\n");
    }
}

int read_tournaments(const char *filename, struct tournament_t **tournaments) {
    if (filename == NULL || tournaments == NULL) return -1;
    FILE *file = fopen(filename, "r");
    if (file == NULL) return -2;

    char input[110];
    int current_year = 0;
    int tournament_count = 0;
    while (fgets(input, sizeof(input), file))
    {
        if (sscanf(input, "World Cup %d", &current_year) == 1)
        {
            tournament_count++;
        }
    }
    rewind(file);

    *tournaments = malloc(tournament_count * sizeof(struct tournament_t));
    if (*tournaments == NULL)
    {
        fclose(file);
        return -4;
    }

    struct tournament_t *current_tournament = *tournaments;
    int processed_tournaments = 0;

    while (fgets(input, sizeof(input), file))
    {
        current_year = 0;
        if (sscanf(input, "World Cup %d", &current_year) == 1) {
            current_tournament->year = current_year;
            current_tournament->number_of_teams = 0;
            current_tournament->table = NULL;
            current_tournament++;
            processed_tournaments++;
        }
        else
        {
            char *home_name = strtok(input, "|");
            char *away_name = strtok(NULL, "|");
            char *result_str = strtok(NULL, "|");

            if (home_name && away_name && result_str)
            {
                int result = atoi(result_str);
                update_tournament(current_tournament - 1, home_name, away_name, result);
            }
            else
            {
                free_tournaments(*tournaments, processed_tournaments);
                fclose(file);
                return -3;
            }
        }
    }

    fclose(file);
    return processed_tournaments;
}

int read_tournaments_realloc(const char *filename, struct tournament_t **tournaments) {
    if (filename == NULL || tournaments == NULL) return -1;
    FILE *file = fopen(filename, "r");
    if (file == NULL) return -2;

    *tournaments = NULL;
    int tournament_count = 0;

    char input[110];
    while (fgets(input, sizeof(input), file))
    {
        int current_year = 0;
        if (sscanf(input, "World Cup %d", &current_year) == 1)
        {
            struct tournament_t *temp = realloc(*tournaments, (tournament_count + 1) * sizeof(struct tournament_t));
            if (temp == NULL)
            {
                free_tournaments(*tournaments, tournament_count);
                fclose(file);
                return -4;
            }
            *tournaments = temp;

            struct tournament_t *current_tournament = *tournaments + tournament_count;
            current_tournament->year = current_year;
            current_tournament->number_of_teams = 0;
            current_tournament->table = NULL;
            tournament_count++;
        }
        else
        {
            char *home_name = strtok(input, "|");
            char *away_name = strtok(NULL, "|");
            char *result_str = strtok(NULL, "|");

            if (home_name && away_name && result_str)
            {
                int result = atoi(result_str);
                update_tournament(*tournaments + tournament_count - 1, home_name, away_name, result);
            }
            else
            {
                free_tournaments(*tournaments, tournament_count);
                fclose(file);
                return -3;
            }
        }
    }

    fclose(file);
    return tournament_count;
}


void display_tournaments(const struct tournament_t *tournaments, int size) {
    if (tournaments == NULL || size <= 0) return;

    const struct tournament_t *current_tournament = tournaments;
    for (int i = 0; i < size; ++i, ++current_tournament)
    {
        printf("World Cup %d\n", current_tournament->year);
        const struct entry_t **current_entry = (const struct entry_t **) current_tournament->table;
        for (size_t j = 0; j < current_tournament->number_of_teams; ++j, ++current_entry)
        {
            printf("%zu: %s: %hu %hu\n",
                   j + 1,
                   (*current_entry)->name,
                   (*current_entry)->matches,
                   (*current_entry)->points);
        }
    }
}