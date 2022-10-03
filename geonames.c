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

// typedef struct {
//     int geonameid;  
//     char name[200];
//     char asciiname[200];     
//     char alternatenames[10000];
//     double latitude;
//     double longitude;     
//     char feature_class[1]; 
//     char feature_code[10];
//     char country_code[3];
//     char cc2[200];
//     char admin1_code[20];
//     char admin2_code[80];
//     char admin3_code[20];
//     char admin4_code[20];
//     unsigned int population;
//     int elevation;
//     int dem; 
//     char timezone[40];
//     char modification 
//     char date[15];
// } Country;

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


int main(int argc, char *argv[]) {
    FILE *fptr;
    char buffer[1001];

    fptr = fopen("cities15000.txt", "r");
    
    if (fptr == NULL)
    {
        printf("Erreur %d\n", errno);
        return 1;
    }
    
    printf("Contenu du fichier :\n\n");
    while (fgets(buffer, 1000, fptr)!=NULL) 
        printf ("%s", buffer);

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
