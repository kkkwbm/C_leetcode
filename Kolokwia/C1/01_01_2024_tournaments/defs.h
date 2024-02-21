#ifndef DEFS_H
#define DEFS_H

#include <stdlib.h>
#include <stdint.h>

struct match_t {
    char * home;
    char * away;
    unsigned short result;
};


struct tournament_t {
    unsigned short year;
    size_t number_of_matches;
    struct match_t *matches;
};

void free_tournaments(struct tournament_t **tournaments);
int read_tournaments(const char *filename, struct tournament_t ***tournaments);
void display_tournaments(struct tournament_t **tournaments);

#endif