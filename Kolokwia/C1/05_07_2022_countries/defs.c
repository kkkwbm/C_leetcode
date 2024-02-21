#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "defs.h"
#include "tested_declarations.h"
#include "rdebug.h"

int find_city(char** cities, char* new_city){
    int i = 0;
    while(*(cities + i) != NULL)
    {
        if(strcmp (new_city, *(cities + i)) == 0) return 1;
        i++;
    }
    return 0;
}
void printCity(char** TabOfCities){
    int i = 0;
    while( *(TabOfCities + i) != NULL)
    {
        printf("%d %s \n", (i + 1), *(TabOfCities + i));
        i++;
    }
}

int cities_counter(char ** cities){
    int i = 0;
    while(*(cities + i) != NULL) i++;
    return i;
}


char** add_City(char** cities, char* new_city){
    int cities_in_country = cities_counter(cities);
    char **temp = realloc(cities, sizeof(char *) * (cities_in_country + 2));
    if (temp == NULL)
    {
        for (int j = 0; j < cities_in_country; j++)
        {
            free(cities + j);
        }
        free(cities);
        return NULL;
    }

    cities = temp;
    *(cities + cities_in_country) = strdup(new_city);
    if(*(cities + cities_in_country) == NULL)
    {
        for (int j = 0; j < cities_in_country; j++)
        {
            free(cities + j);
        }
        free(cities);
        return NULL;
    }

    cities_in_country++;
    *(cities + cities_in_country) = NULL;
    return cities;
}
struct countries_t* add_Country(char* country_name, struct countries_t* country_pos, int country_population){
    if(country_pos == NULL) return NULL;

    country_pos->name = strdup(country_name);
    if (country_pos->name == NULL)
    {
        free(country_pos);
        return NULL;
    }

    country_pos->population = country_population;

    country_pos->cities = calloc(1, sizeof(char**));
    if(country_pos->cities == NULL)
    {
        free(country_pos->name);
        free(country_pos);
        return NULL;
    }

    *(country_pos->cities) = NULL;
    return country_pos;
}

int read_countries(const char* filename, struct countries_t*** countries){
    if (filename == NULL || countries == NULL) return 1;

    FILE *f = fopen(filename,"r");
    if(f == NULL) return 2;

    char input[110];
    int countries_counter = 0;
    int flag = 0;

    *countries = calloc((countries_counter + 2), sizeof(struct countries_t*));
    if(*countries == NULL)
    {
        fclose(f);
        return 4;
    }

    while (!feof(f))
    {
        *(*(countries) + countries_counter) = NULL;
        fscanf(f, "%109[^\n]s", input);

        fgetc(f);
        if(feof(f)) break;

        char *country = strtok(input, "|");
        if(country == NULL)
        {
            free_countries(*countries);
            fclose(f);
            return 3;
        }
        char *city = strtok(NULL, "|");
        if(city == NULL)
        {
            free_countries(*countries);
            fclose(f);
            return 3;
        }
        char *number = strtok(NULL,"\n");
        // If population hasn't been detected
        if(number == NULL)
        {
            if (isdigit((unsigned char)*city) == 0)
            {
                free_countries(*countries);
                fclose(f);
                return 3;
            }
            // Population is in "city" variable
            int population = atoi(city);

            for(int i = 0; i < countries_counter; i++)
            {
                if(strcmp(country, (*(*countries + i))->name) == 0)
                {
                    flag = 1;
                    (*(*countries + i))->population += population;
                    break;
                }
            }
            // if country isn't on list
            if(flag == 0)
            {
                *countries = realloc(*countries, sizeof(struct countries_t*) * (countries_counter + 2));
                if(*countries == NULL)
                {
                    fclose(f);
                    free_countries(*countries);
                    return 4;
                }

                *(*countries + countries_counter) = calloc(1, sizeof(struct countries_t));
                *(*countries + countries_counter) = add_Country(country, *(*countries + countries_counter), population);
                if(*(*countries + countries_counter) == NULL)
                {
                    fclose(f);
                    free_countries(*countries);
                    return 4;
                }
                countries_counter++;
            }
            flag = 0;
        }
        // with city
        else
        {
            int population = atoi(number);
            for(int i = 0; i < countries_counter; i++)
            {
                if(strcmp(country, (*(*countries + i))->name) == 0)
                {
                    (*(*countries + i))->population += population;
                    flag = 1;
                    if(find_city((*(*countries + i))->cities, city) == 0)
                    {
                        (*(*countries + i))->cities = add_City((*(*countries + i))->cities, city);
                        if((*(*countries + i))->cities == NULL)
                        {
                            fclose(f);
                            free_countries(*countries);
                            return 4;
                        }
                    }
                    break;
                }
            }
            // new country with city
            if(flag == 0)
            {
                *countries = realloc(*countries, sizeof(struct countries_t *) * (countries_counter + 2));
                if(*countries == NULL)
                {
                    fclose(f);
                    free_countries(*countries);
                    return 4;
                }

                *(*countries + countries_counter) = calloc(1, sizeof(struct countries_t));
                if(*(*countries + countries_counter) == NULL)
                {
                    fclose(f);
                    free(*(*countries + countries_counter));
                    free_countries(*countries);
                    return 4;
                }
                *(*countries + countries_counter) = add_Country(country, *(*countries + countries_counter), population);
                if(*(*countries + countries_counter) == NULL )
                {
                    fclose(f);
                    free(*(*countries + countries_counter));
                    free_countries(*countries);
                    return 4;
                }

                (*(*countries + countries_counter))->cities = add_City((*(*countries + countries_counter))->cities, city);
                if((*(*countries + countries_counter))->cities == NULL)
                {
                    fclose(f);
                    free((*(*countries + countries_counter))->name);
                    free(*(*countries + countries_counter));
                    free_countries(*countries);
                    return 4;
                }
                countries_counter++;
            }
            flag = 0;
        }

        *(*(countries) + countries_counter) = NULL;
    }

    fclose(f);
    return 0;
}


void display_countries(struct countries_t** countries){
    if (countries == NULL) return;

    int i = 0;
    while(*(countries + i) != NULL)
    {
        printf("%s: %d\n", (*(countries + i))->name, (*(countries + i))->population);
        printCity((*(countries + i))->cities);
        i++;
    }

}
void free_city(char** TabOfCities){
    int i = 0;
    if(TabOfCities != NULL)
    {
        while (*(TabOfCities + i) != NULL)
        {
            free(*(TabOfCities + i));
            i++;
        }
    }

}

void free_countries(struct countries_t** countries){
    int i = 0;
    if(countries != NULL)
    {
        while (*(countries + i) != NULL)
        {
            if ((*(countries + i))->cities != NULL)
            {
                free_city((*(countries + i))->cities);
                free((*(countries + i))->cities);
            }
            if ((*(countries + i))->name != NULL) free((*(countries + i))->name);
            free(*(countries + i));
            i++;
        }
        free(countries);
    }
}


