//
// Created by root on 9/9/22.
//

#ifndef KOL5_07_DEFS_H
#define KOL5_07_DEFS_H


struct countries_t
{
    char* name;
    unsigned int population;
    char** cities;
};

int read_countries(const char* filename, struct countries_t*** countries);
void display_countries(struct countries_t** countries);
void free_countries(struct countries_t** countries);


#endif //KOL5_07_DEFS_H
