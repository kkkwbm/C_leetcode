#ifndef INPUT_TEST_DEFS_H
#define INPUT_TEST_DEFS_H

#include <stdio.h>
#include <crtdefs.h>
#include <stdlib.h>
#include <string.h>

struct entry_t {
    char *name;
    unsigned short points;
    unsigned short matches;
};

struct tournament_t {
    unsigned short year;
    size_t number_of_teams;
    struct entry_t **table;
};

void free_tournaments(struct tournament_t *tournaments, int size);
int read_tournaments(const char *filename, struct tournament_t **tournaments);
void display_tournaments(const struct tournament_t *tournaments, int size);

#endif //INPUT_TEST_DEFS_H
