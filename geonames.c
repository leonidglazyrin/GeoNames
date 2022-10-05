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

// int getIndex(int len, char *buffer) {
//     int i;
//     for (i = 0; i < len; i++)
//     {
//         if (buffer[i] == '\t')
//         {
//             return i;
//         }
//     }
//     return 0;
// }


int main(int argc, char *argv[]) {
    FILE *fptr;
    // struct country country1;
    char buffer[sizeof(struct country) + 1];

    fptr = fopen("cities15000.txt", "r");
    
    if (fptr == NULL)
    {
        printf("Erreur %d\n", errno);
        return 1;
    }
    
    printf("Contenu du fichier :\n\n");

    // while(fread(&country1, sizeof(struct country), 1, fptr))
    // {
    //     printf("%d\n", country1.geonameid);
    // }

    while (fgets(buffer, sizeof(struct country), fptr) != NULL) 
    {
        struct country country1;
        sscanf(buffer,"%i\t%s\t%s\t%s\t%lf\t%lf\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%u\t%i\t%i\t%s\t%s\n", &country1.geonameid, country1.name, country1.asciiname, country1.alternatenames, &country1.latitude, &country1.longitude, country1.feature_class, country1.feature_code, country1.country_code, country1.cc2, country1.admin1_code, country1.admin2_code, country1.admin3_code, country1.admin4_code, &country1.population, &country1.elevation, &country1.dem, country1.timezone, country1.modification_date);
        // if (atoi(country1.admin1_code) > atoi(country1.admin2_code))
        // {
        //     printf ("%s %s %s\n", country1.name, country1.country_code, country1.admin1_code);
        // }
        // else
        // {
        //     printf ("%s %s %s\n", country1.name, country1.country_code, country1.admin2_code);
        // }
        printf ("%s %s %s\n", country1.asciiname, country1.country_code, country1.admin1_code);
        // printf ("%i\t%s\t%s\t%s\t%lf\t%lf\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%u\t%i\t%i\t%s\t%s\n", country1.geonameid, country1.name, country1.asciiname, country1.alternatenames, country1.latitude, country1.longitude, country1.feature_class, country1.feature_code, country1.country_code, country1.cc2, country1.admin1_code, country1.admin2_code, country1.admin3_code, country1.admin4_code, country1.population, country1.elevation, country1.dem, country1.timezone, country1.modification_date);
        // printf("%s", buffer);
    }

    if (fclose(fptr) == EOF)
    {
        printf("Erreur dans la fermeture du fichier.\n");
    }

    return 0;
    
    // fscanf(fptr,"%i %s %s %s %lf %lf %s %s %s %s %s %s %s %s %u %i %i %s %s\n", name, &age, &id, town);

    // fgets(text, 1000, fptr);
    // printf ("%s", text);

    // fclose(fptr);
    // return 0;
}
