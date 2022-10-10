/**
 *  geonames.c
 *
 *  Display a table of the n most populated cities, by looking into
 *  cities15000.txt and countryInfo.txt files.
 *  
 *  ```sh
 *  ./geonames.c 10
 *  ./geonames < fileWithParameters
 *  ```
 *  
 *  @author Leonid Glazyrin
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USAGE "\
Usage: %s <NUMBER OF CITIES>\n\
\n\
Display a table of the n most populous cities on stdout. The number of cities must not exceed 5000.\n\
\n\
If no argument is provided, the program prints this help and exit.\n\
\n\
Program parameters :\n\
  NUMBER of cities         Number de cities to print (1..500)\n\
"
#define FORMAT_TITRE    "%4s   %-20.20s   %-20.20s   %s\n"
#define FORMAT_COLONNES "%4d   %-20.20s   %-20.20s   %10d\n"

#define ARBITRARY_LINE_LENGTH   600

#define FIELD_ASCIINAME         3
#define FIELD_COUNTRY_CODE      9
#define FIELD_POPULATION        15
#define FIELD_14                14

#define FIELD_COUNTRY_NAME      5
#define COUNTRY_FIELD_CODE      1

#define MINIMUM_POPULATION      15000

#define MAX_N                   5000
#define MIN_N                   1

/**
 * ----------------
 * Types de données
 * ----------------
 */

// A country
struct Country {
    char nom[50]; // Le nom du pays
    char code[3]; // Le code de deux lettres identifiant le pays
};

// A city
struct city{
    char asciiname[205];     
    char country_code[10];
    unsigned int population;
    char pays[50]; // Le pays dans laquelle la ville existe
};

// For the length of a line to read into buffer
struct ReadCity{
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
    ERREUR_ARGS_TYPE	    = 3,
    ERREUR_OPEN_FILE	    = 4,
    ERREUR_CLOSE_FILE	    = 5
};


/**
 * -----------------------
 * Function prototypes
 * -----------------------
 */

/**
 *  Verifies the number and type of parameters in argv
 *
 *  @param argc  Parameter count
 *  @param argv  Array of parameters
 *
 *  @return error code from enum error
 */
int handle_parameters(const int argc, char *argv[]);

/**
 *  Check whether a string is not numeric
 *
 *  @param arg  string
 *
 *  @return 0 if not numeric
 *          1 if numeric
 */
unsigned int is_not_numeric(const char arg[]);

/**
 * Handles piping (./geonames < file)
 *
 * @param params array where parameters from stdin redirection
 * will be stored
 *
 * @return error code from enum error
 */
int handle_redirection(char **params);

/**
 *  Removes trailing whitespaces of a string
 *
 *  @param buffer string
 *
 *  @return pointer to the first char which isn't a whitespace
 */
char* trim(char *buffer);

/**
 *  Check whether a char is a whitespace
 *
 *  @param c a character
 *
 *  @return 1 if it is considered a whitespace
 *          0 if not
 */
int is_it_space(char c);

/**
 *  Check whether a file was piped to the program
 *
 *  @return 1 no file was redirected to the standard input
 *          0 if there was a file passed to the standard input
 */
unsigned int check_no_stdin();

/**
 *  Opens a file and handles error cases
 * 
 *  @param file_name name of the file
 *
 *  @return pointer to the file
 */
FILE* open_file(const char *file_name);

/**
 *  Closes a file and handles error cases
 *
 *  @param fptr pointer to the file to close
 */
void close_file(FILE *fptr);

/**
 *  Counts the number of lines in the cities text file
 *  usefull to know when creating the array containing them
 *
 *  @return number of lines
 */
unsigned int count_lines_city();

/**
 *  Counts the number of lines in the counties text file
 *  usefull to know when creating the array containing them
 *
 *  @return number of lines
 */
unsigned int count_lines_country();

/**
 *  Substract all lines starting with "#" in countries file
 *
 *  @param fptr pointer to the file containing lines starting with hashtags
 *  @param count total number of lines in the file
 *
 *  @return the new line count
 */
unsigned int remove_hashtags(FILE *fptr, int count);

/**
 *  Iterates over the lines in cities and fills the array of cities
 *
 *  @param cities pointer to the array of struct city
 */
void load_cities(struct city *cities);

/**
 *  Fills the assciname, population and country code of
 *  one city
 *
 *  @param one_city pointer to the particular city in an array
 *  @param buffer the full text line containing all information about a city
 */
void fill_fields_city(struct city *one_city, char *buffer);

/**
 *  Handles filling in the population of a city
 *  (sometimes it's in the 14th column and not the 15th)
 *
 *  @param one_city pointer to the particular city in an array
 *  @param field string of the 15th field
 *  @param field14 value of the 14th field
 */
void handle_population(struct city *one_city, const char *field, const int field14);

/**
 *  Iterates over the lines in countries and fills 
 *  the array of (country - country code) associations
 *
 *  @param countries pointer to the array of struct Country
 */
void load_countries(struct Country *countries);

/**
 *  Fills the country and country code of one country
 *
 *  @param one_country pointer to the particular country in an array
 *  @param buffer the full text line containing all information about a country
 */
void fill_fields_country(struct Country *one_country, char *buffer);

/**
 *  Associates the field pays of every city to the country's full name
 *
 *  @param cities pointer to the array of cities
 *  @param city_count number of cities in that array
 *  @param countries pointer to the array of countries
 *  @param country_count number of countries in that array
 */
void associate_countries(struct city *cities, const unsigned int city_count, 
                            struct Country *countries, const unsigned int country_count);

/**
 *  Returns a pointer to a field delimited by delimiter,
 *  it works by inserting a "\0" insteat of the delimiter
 *  and modifing the buffer pointer to point past that "\0"
 * 
 *  @param buffer a pointer to a pointer to a string where the field
 *                  are separated by the delimiter
 *
 *  @param delimiter string by which the fields are separated
 *
 *  @return pointer to one field in the full line
 */
char* get_field(char **buffer, const char *delimiter);

/**
 *  Compares two instances
 *
 *  @param a one instance
 *  @param b another instance
 *
 *  @return and int > 0 if a is bigger than b
 *                  < 0 if a is smaller than b
 */
int compare_function(const void *a, const void *b);

/**
 *  Iterates over all the cities and prints until number_cities - 1 reached
 *
 *  @param cities array containing the cities to print
 *  @param number_cities number of cities the user wished to see
 */
void print_result(struct city *cities, unsigned const int number_cities);

/**
 *  Prints the correspondant message and USAGE if needed
 *
 *  @param error_code the error code to print
 */
void print_errors(const int error_code);

/**
 *  Executes all the main operations of the program
 *
 *  @param number_cities number of cities passed 
 *                       by the user through command line or pipe
 */
void execute_program(unsigned const int number_cities);


/**
 * -----------------------
 * Function implemenetaions
 * -----------------------
 */

unsigned int count_lines_city() {
    FILE *fptr = open_file("cities15000.txt");
    unsigned int count = 0;
    char c;

    for (c = getc(fptr); c != EOF; c = getc(fptr))
        if (c == '\n')
            count++;

    close_file(fptr);
    return count;
}

unsigned int count_lines_country() {
    FILE *fptr = open_file("countryInfo.txt");
    unsigned int count = 0;
    char c;

    for (c = getc(fptr); c != EOF; c = getc(fptr))
        if (c == '\n')
            count++;
    
    count = remove_hashtags(fptr, count);
    close_file(fptr);
    return count;
}

unsigned int remove_hashtags(FILE *fptr, int count) {
    rewind(fptr);
    char buffer[ARBITRARY_LINE_LENGTH + 1];
    while (fgets(buffer, ARBITRARY_LINE_LENGTH, fptr) != NULL)
        if (buffer[0] == '#') 
            count--;
    return count;
}

void load_cities(struct city *cities) {
    FILE *fptr = open_file("cities15000.txt");
    char buffer[sizeof(struct ReadCity) + 1];
    unsigned int city_count = 0;

    while (fgets(buffer, sizeof(struct ReadCity), fptr) != NULL) {
        fill_fields_city(&cities[city_count++], buffer);
    }

    close_file(fptr);
}

void close_file(FILE *fptr) {
    if (fclose(fptr) == EOF) {
        printf("Erreur dans la fermeture du fichier.\n");
        exit(ERREUR_CLOSE_FILE);
    }
}

FILE* open_file(const char *file_name) {
    FILE *fptr = fopen(file_name, "r");
    
    if (fptr == NULL) {
        printf("Erreur dans l'ouverture du fichier.\n");
        exit(ERREUR_OPEN_FILE);
    }
    return fptr;
}

void fill_fields_city(struct city *one_city, char *buffer) {
    unsigned int field_count = 1;
    char *field;
    int field14; // Handle some cases where population is in 14th and not 15th

    while ((field = get_field(&buffer, "\t")) != NULL) {
        if (field_count == FIELD_ASCIINAME) 
        {
            strcpy(one_city -> asciiname, field);
        } 
        else if (field_count == FIELD_COUNTRY_CODE) 
        {
            strcpy(one_city -> country_code, field);
        } 
        else if (field_count == FIELD_14) 
        {
            field14 = (unsigned int) atoi(field);
        } 
        else if (field_count == FIELD_POPULATION) 
        {
            handle_population(one_city, field, field14);
            break;
        }
        field_count++;
    }
}

void handle_population(struct city *one_city, const char *field, const int field14) {
    if (atoi(field) < MINIMUM_POPULATION)
        one_city -> population = field14;
    else
        one_city -> population = (unsigned int) atoi(field);
}

void load_countries(struct Country *countries) {
    FILE *fptr = open_file("countryInfo.txt");
    char buffer[ARBITRARY_LINE_LENGTH + 1];
    unsigned int country_count = 0;

    while (fgets(buffer, ARBITRARY_LINE_LENGTH, fptr) != NULL)
        if (buffer[0] != '#')
            fill_fields_country(&countries[country_count++], buffer);

    close_file(fptr);
}

void fill_fields_country(struct Country *one_country, char *buffer) {
    int field_count = COUNTRY_FIELD_CODE;
    char *field;

    while ((field = get_field(&buffer, "\t")) != NULL) {
        if (field_count == COUNTRY_FIELD_CODE) 
            strcpy(one_country -> code, field);
        else if (field_count == FIELD_COUNTRY_NAME) 
            strcpy(one_country -> nom, field);
        
        field_count++;
    }
}

void associate_countries(struct city *cities, const unsigned int city_count, 
                            struct Country *countries, const unsigned int country_count) {
    unsigned int city_counter;
    unsigned int country_counter;

    for (city_counter = 0; city_counter < city_count; city_counter++)
        for (country_counter = 0; country_counter < country_count; country_counter++)
            if (strcmp(cities[city_counter].country_code, countries[country_counter].code) == 0) {
                strcpy(cities[city_counter].pays, countries[country_counter].nom);
                break;
            }
}

int compare_function(const void *a, const void *b) {
    const unsigned int city_one = ((struct city *) a) -> population;
    const unsigned int city_other = ((struct city *) b) -> population; 
    return (city_other - city_one);
}

int handle_parameters(const int argc, char *argv[]) {
    if (argc != 2)
        return ERREUR_NB_ARGS;
    
    if (is_not_numeric(argv[1]))
        return ERREUR_ARGS_TYPE;

    if ((atoi(argv[1]) < MIN_N) || (atoi(argv[1]) > MAX_N))
        return ERREUR_NB_VILLES;

    return OK;
}

void print_errors(const int error_code) {
    if (error_code == ERREUR_NB_ARGS) {
        printf("%s\n", "nombre arguments invalide");
        printf(USAGE, "./geonames");
    } else if (error_code == ERREUR_ARGS_TYPE)
        printf("%s\n", "type argument invalide");
    else if (error_code == ERREUR_NB_VILLES)
        printf("%s\n", "nombre de ville invalide");
}

unsigned int is_not_numeric(const char arg[]) {
    unsigned int i;
    if ('-' == arg[0]) 
        return 0;
    for (i = 0; i < strlen(arg); i++)
        if(arg[i] < '0' || arg[i] > '9')
            return 1;
    return 0;
}

void print_result(struct city *cities, unsigned const int number_cities) {
    unsigned int i;
    printf(FORMAT_TITRE, "Rang", "Nom", "Pays", "Population");
    printf("%s\n", "----   ---                    ----                   ----------");
    for (i = 0; i < number_cities; i++)
        printf (FORMAT_COLONNES, i + 1, cities[i].asciiname, cities[i].pays, cities[i].population);
}

char* get_field(char **buffer, const char *delimiter) {
    char *field = *buffer;
    if (field) {
        *buffer += strcspn(*buffer, delimiter);
        if (**buffer){
            *(*buffer) = '\0';
            *buffer = *buffer + 1;
        } else {
            *buffer = NULL; 
        }
    }
    return field;
}

int handle_redirection(char **params) {
    FILE *fptr = stdin;

    char buffer[ARBITRARY_LINE_LENGTH + 1];
    fgets(buffer, ARBITRARY_LINE_LENGTH, fptr);
    buffer[strlen(buffer) - 1] = '\0';

    char *buffer_no_space = trim(buffer);
    unsigned int field_count = 1;
    char *field;

    while ((field = get_field(&buffer_no_space, " ")) != NULL && field_count < 3 && strcmp(field, "") != 0)
        params[field_count++] = field;

    return handle_parameters(field_count, params);
}

unsigned int check_no_stdin() {
    if ((fseek(stdin, 0, SEEK_END), ftell(stdin)) > 0) {
        rewind(stdin);
        return 0;
    } else {
        return 1;
    }
}

char* trim(char *buffer) {
    unsigned int j = 0;

    while(is_it_space(buffer[j]))
        j++;
    
    return &buffer[j];
}

int is_it_space(const char c) {
	return (c == '\t' || c == ' ' ? 1 : 0);
}

void execute_program(unsigned const int number_cities) {
    unsigned const int country_count = count_lines_country();
    struct Country countries[country_count];
    load_countries(countries);

    unsigned const int city_count = count_lines_city();
    struct city cities[city_count];
    load_cities(cities);

    associate_countries(cities, city_count, countries, country_count);

    qsort(cities, city_count, sizeof(struct city), compare_function);

    print_result(cities, number_cities);
}

int main(int argc, char *argv[]) {
    unsigned int number_cities;

    unsigned const int status_code = handle_parameters(argc, argv);
    unsigned int status_code_redirect;

    char *params[3];

    if ((status_code == OK && !check_no_stdin()) ||
        (status_code == ERREUR_NB_ARGS && check_no_stdin()) ||
        (status_code == ERREUR_NB_ARGS && argc != 1)) 
    {
        print_errors(ERREUR_NB_ARGS);
        return ERREUR_NB_ARGS;
    }
    else if (status_code == ERREUR_NB_ARGS) 
    {
        status_code_redirect = handle_redirection(params);
        if (status_code_redirect != OK) {
            print_errors(status_code_redirect);
            return status_code_redirect;
        }
        number_cities = atoi(params[1]);
    } 
    else if (status_code != OK) 
    {
        print_errors(status_code);
        return status_code;
    }
    else 
    {
        number_cities = atoi(argv[1]);
    }

    execute_program(number_cities);

    return 0;
}