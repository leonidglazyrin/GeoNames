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

struct country{
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

//Prototypes
unsigned int count_lines(FILE *fptr);

int main(int argc, char *argv[]) {
    FILE *fptr;
    char buffer[sizeof(struct country) + 1];
    char *file_name = "cities15000.txt";

    fptr = fopen(file_name, "r");
    
    if (fptr == NULL)
    {
        printf("Erreur %d\n", errno);
        return 1;
    }

    unsigned int file_lines = count_lines(fptr);
    printf("%d", file_lines);
    
    while (fgets(buffer, sizeof(struct country), fptr) != NULL) 
    {
        char *geonameid, *name, *asciiname, *alternatenames, *latitude, *longitude, *feature_class, *feature_code, *country_code, *cc2, *admin1_code, *admin2_code, *admin3_code, *admin4_code, *population, *elevation, *dem, *timezone, *modification_date;

        char *r = buffer;

        geonameid = strsep(&r, "\t");
        name = strsep(&r, "\t");
        asciiname = strsep(&r, "\t");
        alternatenames = strsep(&r, "\t");
        latitude = strsep(&r, "\t");
        longitude = strsep(&r, "\t");
        feature_class = strsep(&r, "\t");
        feature_code = strsep(&r, "\t");
        country_code = strsep(&r, "\t");
        cc2 = strsep(&r, "\t");
        admin1_code = strsep(&r, "\t");
        admin2_code = strsep(&r, "\t");
        admin3_code = strsep(&r, "\t");
        admin4_code = strsep(&r, "\t");
        population = strsep(&r, "\t");
        elevation = strsep(&r, "\t");
        dem = strsep(&r, "\t");
        timezone = strsep(&r, "\t");
        modification_date = strsep(&r, "\n");

        // printf ("%s %s %s\n", asciiname, country_code, population);

    }

    if (fclose(fptr) == EOF)
    {
        printf("Erreur dans la fermeture du fichier.\n");
    }

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