#define USAGE "\
Usage: %s  <NUMBER OF CITIES>\n\
\n\
Display a table of the n most populous cities on stdout. The number of cities must not exceed 5000.\n\
\n\
If no argument is provided, the program prints this help and exit.\n\
\n\
Program parameters :\n\
  NUMBER of cities         Number de cities to print (1..500)\n\
  "
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define FORMAT_TITRE    "%4s   %-20.20s   %-20.20s   %s\n"
#define FORMAT_COLONNES "%4d   %-20.20s   %-20.20s   %10ld\n"

/**
 * ----------------
 * Types de données
 * ----------------
 */
struct Pays {
    char nom[50]; // Le nom du pays
    char code[3]; // Le code de deux lettres identifiant le pays
};
const struct Pays PAYS_BIDON = {"??", "??"};

struct Ville {
    char nom[100];    // Le nom ASCII de la ville
    long population;  // La population
    struct Pays pays; // Le pays dans laquelle la ville existe
};
const struct Ville VILLE_BIDON = {"??", -1, {"??", "??"}};

struct city{
    int geonameid;  
    char name[205];
    char asciiname[205];     
    char alternatenames[10005];
    double latitude;
    double longitude;     
    char feature_class[5]; 
    char feature_code[15];
    char country_code[10];
    char cc2[205];
    char admin1_code[25];
    char admin2_code[85];
    char admin3_code[25];
    char admin4_code[25];
    unsigned int population;
    int elevation;
    int dem; 
    char timezone[45];
    char modification_date[15];
};

struct city2{
    char asciiname[205];     
    char country_code[10];
    unsigned int population;
};

/**
 * -----------------------
 * Codes d'erreur
 * -----------------------
 */

enum error {
    OK                      = 0,
    ERREUR_NB_ARGS          = 1,
    ERREUR_NB_VILLES        = 2,
    ERREUR_ARGS_TYPE	    = 3
};

unsigned int count_lines(FILE *fptr);
void load_cities();
FILE* open_cities();
void iterate_cities();
void close_cities(FILE *fptr);
void fill_fields(struct city2 cities[], char buffer[],int city_count);

int main(int argc, char *argv[]) {
    load_cities();
    return 0;
}

unsigned int count_lines(FILE *fptr) {
    unsigned int count = 0;
    char c;

    for (c = getc(fptr); c != EOF; c = getc(fptr))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;

    rewind(fptr);
    return count;
}

void load_cities() {
    FILE *fptr = open_cities();
    iterate_cities();
    
    char buffer[sizeof(struct city) + 1];

    unsigned int file_lines = count_lines(fptr);
    struct city2 cities[file_lines];
    int city_count = 0;

    while (fgets(buffer, sizeof(struct city), fptr) != NULL && strlen(buffer) > 10) {
        fill_fields(cities, buffer, city_count);
        city_count = city_count + 1;
    }

    int i;
    for (i = 0; i < file_lines; ++i)
    {
        printf ("%s %s %u\n", cities[i].asciiname, cities[i].country_code, cities[i].population);
    }

    close_cities(fptr);
}

void close_cities(FILE *fptr) {
    if (fclose(fptr) == EOF) {
        printf("Erreur dans la fermeture du fichier.\n");
        exit(2);
    }
}

void iterate_cities() {
    
}

FILE* open_cities() {
    char *file_name = "cities15000.txt";

    FILE *fptr = fopen(file_name, "r");
    
    if (fptr == NULL) {
        printf("Erreur %d\n", errno);
        exit(1);
    }
    return fptr;
}

void fill_fields(struct city2 cities[], char buffer[], int city_count) {
    char *r = buffer;
    int field_count = 1;
    char *field;

    while ((field = strsep(&r, "\t")) != NULL) {
        if (field_count == 3) {
            strcpy(cities[city_count].asciiname, field);
        } else if (field_count == 9) {
            strcpy(cities[city_count].country_code, field);
        } else if (field_count == 15) {
            cities[city_count].population = (unsigned int) atoi(field);
        }
        field_count = field_count + 1;
    }
}