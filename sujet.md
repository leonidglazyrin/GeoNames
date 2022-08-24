# Travail pratique 1: GeoNames
**Lisez bien le sujet jusqu'au bout avant de commencer à travailler sur le projet.**


## Objectifs pédagogiques

Les principaux objectifs pédagogiques visés sont les suivants:

- Vous initier au langage de **programmation C**.
- Vous initier à l'utilisation du logiciel de contrôle de versions **Git** lors
  d'un développement en **solitaire**.
- Vous familiariser à la compilation d'un programme à l'aide d'un **Makefile** simple.
- Vous habituer à décomposer un programme en **petites fonctions**.
- Vous familiariser avec le passage d'arguments par **adresse**.
- Vous familiariser avec l'utilisation de l'**entrée standard** (`stdin`) et de
  la **sortie standard** (`stdout`)
- Vous familiariser avec le traitement des **arguments** d'un programme et des
  **codes de retour**

## Description du travail

Le projet [GeoNames](http://www.geonames.org/) propose gratuitement des données géographiques sous la license [CreativeCommons](http://creativecommons.org/licenses/by/3.0/). Celles-ci peuvent être téléchargées en cliquant [ici](http://download.geonames.org/export/dump/). Elles sont utilisées dans de nombreuses applications et promeuvent par la même occasion la philosophie de [l'Open data](https://fr.wikipedia.org/wiki/Open_data), qui devient de plus en plus répandue.

Votre travail consistera à utiliser certaines des données fournies pour afficher la liste des villes ayant la plus grande population sur notre planète (enfin, en supposant que la base de données est fidèle à la réalité).  Plus précisément, vous devez créer un exécutable nommé `geonames` de telle sorte que si on entre par exemple la commande

```
./geonames 10
```
alors votre programme affiche un tableau des 10 villes les plus populeuses comme suit (notez que le résultat peut différer légèrement s'il y a des mises à jour de la base de données) :

```

   Rang   Nom                    Pays                   Population
   ----   ---                    ----                   ----------
      1   Shanghai               China                    22315474
      2   Buenos Aires           Argentina                13076300
      3   Mumbai                 India                    12691836
      4   Mexico City            Mexico                   12294193
      5   Beijing                China                    11716620
      6   Karachi                Pakistan                 11624219
      7   Istanbul               Turkey                   11174257
      8   Tianjin                China                    11090314
      9   Guangzhou              China                    11071424
     10   Delhi                  India                    10927986
```

Évidemment, si on utilise un nombre `n` plutôt que 10, alors ce sont les `n` villes les plus populeuses qui sont affichées. Afin de simplifier le travail, nous supposerons que `n` n'est pas trop grand (au plus 5000).

Il est également important que l'affichage soit bien présenté. Les colonnes devraient être alignées et il ne devrait pas y avoir de décalage dû à des colonnes trop longues. Par conséquent, il est recommandé de choisir des largeur raisonnable pour chaque colonne et de couper les chaînes de caractères trop longues en utilisant les options de format de la fonction `printf`.

Pour faciliter la correction, `stdin` sera redirigé vers un fichier avec le même contenu.

```
./geonames < test.txt
```


### Suggestions et indices

Bien qu'il y ait plusieurs façons de réaliser ce travail, je vous suggère de vous concentrer sur les deux fichiers suivants :

- `countryInfo.txt`, qui contient les informations principales sur les pays. Vous pouvez entre autres établir la correspondance entre les codes des pays et leur nom (`CA` pour `Canada`, `US` pour `United States`, etc.).
  **Remarque** : afin de minimiser les problèmes d'encodages, utiliser le nom ASCII du pays plutôt que son nom en UTF8.
- ``cities15000.txt``, qui dresse la liste des villes et lieu ayant au moins 15000 habitants. Ici aussi, il est préférable d'utiliser le nom ASCII.

**Attention** : vous ne pouvez pas supposer que les fichiers `countryInfo.txt` et `cities15000.txt` sont toujours les mêmes, mais seulement le contenu des colonnes ! Autrement dit, vous devez charger dynamiquement le contenu de ces fichiers dans votre programme.

Lorsque vous avez chargé en mémoire (dans un tableau) la totalité des villes et des pays, alors vous devriez trier les villes en ordre **décroissant** de leur population à l'aide de l'algorithme de **tri rapide**, que vous devez implémenter (si vous utilisez du code déjà existant, citez vos sources). Puis il ne vous reste plus qu'à afficher les `n` premières villes, où `n` est un argument passé en paramètre à votre fonction `main`.

Je vous suggère les types suivants (les constantes ``PAYS_BIDON`` et ``VILLE_BIDON`` peuvent être utilisées pour représenter des pays et des villes non initialisées ou invalides) :

```
   struct Pays {
       char nom[LONG_NOM_PAYS];   // Le nom ASCII
       char code[LONG_CODE_PAYS]; // Le code de deux lettres
   };
   const struct Pays PAYS_BIDON = {"??", "??"};
   
   struct Ville {
       char nom[LONG_NOM_VILLE]; // Le nom ASCII
       long population;          // La population
       struct Pays pays;         // Le pays de la ville
   };
   const struct Ville VILLE_BIDON = {"??", -1, {"??", "??"}};
```

Vous êtes libre d'utiliser d'autres types de donnés si vous le souhaitez.

**Remarque** : comme l'allocation dynamique n'est pas vue dans les 3 premières semaines, toutes vos chaînes de caractères auront une longueur maximale fixe, précisée par une constante.

### Détails additionnels et exigences

Lorsqu'un utilisateur entre la commande

```
   ./tp1 <nombre de villes>
```

vous devez vous assurer que le paramètre passé est un entier entre 1 et 5000. Si ce n'est pas le cas, un message d'erreur pertinent doit être affiché et un code d'erreur identifiant l'erreur doit être retourné par la fonction `main`.


Les messages d’erreur à afficher doivent être de la forme suivante :

* **"nombre arguments invalide"** Si l'utilisateur oublie le paramètre ou en met en trop. Le manuel d'utilisation doit être affiché sur la sortie standard à la suite de ce message:

```text
$ ./geonames
nombre d'arguments invalide
Usage: ./geonames <NUMBER OF CITIES>

Display a table of the n most populous cities on stdout. 
The number of cities must not exceed 5000.

If no argument is provided, the program prints this help and exit.

Program parameters :

  NUMBER OF CITIES        Number de cities to print (1..500)
                           
```

* **"nombre de ville invalide"** si le nombre de ville est plus petit que 1 et plus grand que 5000 ;

* **"type argument invalide"** si un caractère ou une chaîne de caractères alphanumérique est passé à la fonction main.

Notez que ces messages d’erreur ne doivent comporter aucun **accent**, doivent être ecrits en minuscules et sans espace au début et à la fin : bref, ils doivent être orthographiés exactement comme décrit plus haut, car vos programmes seront vérifiés de façon automatique.

Afin d'éviter des pénalités, il est important de respecter les contraintes suivantes :

- Vous devez utiliser un **unique** fichier source nommé ``geonames.c``;
- Le nom de votre **exécutable** doit être ``geonames``;
- Les **prototypes** de toutes les fonctions doivent être déclarés en en-tête avant d'être implémentés;
- **Aucune variable globale** (à l'exception des constantes);
- **Aucune bibliothèque (librairie)** autre que ``stdio``, ``string`` et ``stdlib`` n'est permise;
- Il est interdit de **copier intégralement** des bouts de code provenant d'autres sources, même en mentionnant leur source (en revanche, vous pouvez vous **inspirer** d'autre code en citant sa provenance).
- **Aucune allocation dynamique** n'est permise (fonctions ``malloc`` et ``free``);
- Il est obligatoire de **ne pas versionner avec Git** les fichiers inutiles ou trop volumineux, tels que :

  * les fichiers avec l'extension ``.o``;
  * le fichier exécutable ``geonames``;
  * les données provenant du projet [GeoNames](http://www.geonames.org/)(autant les archives ``.zip`` que les données non compressées).

Advenant le non-respect d'une ou plusieurs de ces contraintes, des pénalités **pouvant aller jusqu'à l'attribution de la note 0** pourraient être appliquées.


## Tâches à accomplir

Afin de compléter ce travail pratique, vous devrez suivre les étapes suivantes:

1. Créez un clone (*fork*) du [dépôt du projet](https://gitlab.info.uqam.ca/inf3135-sdo/geonames).
2. Assurez-vous que le dépôt soit privé, pour éviter le plagiat.
3. Donnez accès à votre dépôt aux usagers `dogny_g` et `correcteur` en mode `Developer`.
4. Familiarisez-vous avec le contenu du dépôt, en étudiant chacun des fichiers
   (`README.md`, `sujet.md`, `check.bats`, `.gitlab-ci.yml`, etc.).
5. Commencez votre développement en versionnant fréquemment l'évolution de
   votre projet avec Git. La qualité de votre versionnement sera évaluée, il
   est donc important de valider (*commit*) chaque fois que vous avez terminé
   une petite tâche.
6. Ajoutez un fichier `Makefile` pour qu'il exécute toutes les tâches demandées.
7. Complétez le fichier `README.md` en respectant le format Markdown et en
   tenant compte des instructions qui y sont présentes.
8. Complétez le fichier `geonames.c`.

### Clone et création du dépôt

Vous devez cloner le dépôt fourni et l'héberger sur la plateforme [Gitlab du
département](https://gitlab.info.uqam.ca/). Votre dépôt devra se nommer
**exactement** `inf3135-tp1-a22` et l'URL devra être **exactement**
`https://gitlab.info.uqam.ca/<utilisateur>/inf3135-tp1-a22`, où
`<utilisateur>` doit être remplacé par votre code MS de l'UQAM ou par votre nom d'utilisateur. Il devra être **privé** et accessible seulement par vous et les usagers `dogny_g` et `correcteurs`.

### Fichier `geonames.c`

L'organisation du contenu de votre fichier `geonames.c` est laissé à votre discrétion, mais je vous suggère tout de même d'utiliser minimalement les déclarations suivantes (n'oubliez pas de les documenter):

```c
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

/**
 * -----------------------
 * Codes d'erreur
 * -----------------------
 */

enum error {
    OK                      = 0,
    ERREUR_NB_ARGS          = 1,
    ERREUR_NB_VILLES        = 2,
    ERREUR_ARGS_TYPE	     = 3
};
```

### Makefile

Il est obligatoire d'inclure un fichier `Makefile` dans votre projet pour
faciliter la compilation et la récupération des données. 

Vous devrez supporter les cibles suivantes dans votre Makefile:

- La commande `make` crée l'exécutable `geonames` s'il y a eu une modification
  du fichier `geonames.c` en le compilant selon le standard C11, avec les
  options `-Wall` et `-Wextra` lors de la compilation.
- La commande `make html` transforme les fichiers `README.md` et `sujet.md` en
  HTML à l'aide du logiciel [Pandoc](https://pandoc.org/) en utilisant le style
  CSS fourni dans le fichier [`misc/github-pandoc.css`](misc/github-pandoc.css)
- La commande `make database` télécharge les données dans le répertoire de votre choix à l'aide du programme `curl`.
- La commande `make test` recompile l'exécutable si nécessaire, puis lance la
  suite de tests contenue dans le fichier `check.bats` **non modifié**, livré
  dans le dépôt que vous avez cloné.
- La commande `make clean` supprime les fichiers inutiles ou générés (`.o`, `.html`, etc.).

N'oubliez pas les **dépendances** pour chaque cible s'il y en a.

### Fichier `README.md`

Vous devez compléter le fichier `README.md` livré dans le dépôt en suivant les
instructions qui y sont indiquées. Assurez-vous également de répondre aux
questions suivantes:

- À quoi sert votre programme?
- Comment le compiler?
- Comment l'exécuter?
- Quels sont les formats d'entrées et de sorties?
- Quels sont les cas d'erreur gérés?

Vous devez utiliser la syntaxe Markdown pour écrire une documentation claire et
lisible. Vous pouvez en tout temps vérifier localement le fichier HTML produit
sur votre machine à l'aide de [Pandoc](https://pandoc.org/), mais il est aussi
conseillé de vérifier, avant la remise finale, que le résultat produit sur la
page d'accueil de GitLab est celui auquel vous vous attendez.

Évitez d'abuser du gras, de l'italique et du HTML brut dans le fichier
`README.md`. Exploitez au maximum les listes à puces et formatez les noms de
fichier et le code à l'aide des apostrophes inversés. Finalement, soignez la
qualité de votre français, qui sera prise en considération dans le fichier
`README.md`.

### Git

Il est important de suivre l'évolution de votre projet à l'aide de Git. Vous
devez cloner (à l'aide du bouton *fork*) le gabarit du projet fourni et ajouter
vos modifications à l'aide de *commits*. En particulier, il est possible que je
doive apporter des corrections ultérieures à l'énoncé que vous pourrez
récupérer facilement si nous avons un historique **commun**.

N'oubliez pas de bien configurer correctement votre fichier `.gitconfig` qui
permet de vous identifier comme auteur de *commits*, en y indiquant vos
**véritables** prénom, nom et courriel UQAM.

Les messages de *commit* doivent suivre une des conventions suivantes:

- [How to write a Git commit
  message](https://chris.beams.io/posts/git-commit/), par Chris Beams
- [Conventional commits](https://www.conventionalcommits.org/en/v1.0.0/), par
  différentes personnes

Finalement, n'oubliez pas d'inclure un fichier `.gitignore` en fonction de
votre environnement de développement. Aussi, assurez-vous de ne pas versionner
de fichiers inutiles (les fichiers binaires, entre autres, mais pas seulement).

### Correction

L'exécution de votre programme sera vérifiée automatiquement grâce à une suite
de tests rédigée en [Bats](https://github.com/bats-core/bats-core). Bien
entendu, vous devez installer Bats pour le faire fonctionner. Pour faciliter
votre développement, vous avez accès à un certain nombre de tests *publics*
pour corriger vos travaux (dans le fichier `check.bats`). Il suffit d'entrer la commande

```sh
$ bats check.bats
```

pour lancer la suite de tests.

Cependant, prenez note que la couverture de tests n'est pas **complète**. Je me
réserve donc la possibilité d'ajouter des tests supplémentaires pour la
correction finale. Si vous avez un doute sur le comportement attendu d'une
certaine situation, je vous invite à me poser des questions pour que je puisse
apporter des précisions à l'ensemble de la classe si nécessaire.

### Pénalités

Tout programme qui ne compile pas se verra automatiquement attribuer **la note 0**.

En outre, si vous ne respectez pas les critères suivants, une pénalité
de **50%** sera imposée :

- Votre dépôt doit se nommer **exactement** `inf3135-tp1-a22`
- L'URL de votre dépôt doit être **exactement** `https://gitlab.info.uqam.ca/<utilisateur>/inf3135-tp1-a22` où
  `<utilisateur>` doit être remplacé par votre identifiant.
- Les usagers `dogny_g` et `correcteurs` doivent avoir accès à votre projet en mode `Developer`.
- Votre dépôt doit être un *fork* du [gabarit fourni](https://gitlab.info.uqam.ca/inf3135-sdo/geonames).
- Votre dépôt doit être **privé**.
- Il est interdit d'utiliser les fonctions `getopt` et `getopt_long` des bibliothèques `unistd.h` et `getopt.h`.
- Il est interdit d'utiliser l'**allocation dynamique** dans ce travail (fonctions `malloc`, `calloc`, `realloc`, `free`).

## Remise

Le travail est automatiquement remis à la date de remise prévue. Vous n'avez rien de plus à faire. Assurez-vous d’avoir votre travail disponible sur votre branche `master/main` qui sera considérée pour la correction. Tous les commits après le **9 octobre 2022 à 23:55** ne seront pas considérés pour la correction.

### Barème

Les critères d'évaluation sont les suivants:

Critère | Sous-critère | Points
---- | -------------- | ---------:
Foncrionnalité | Chargement des pays |10|
  | Chargement des villes | 10 |
  | Tri selon la population | 10 |
  | Arguments de la fonction `main` | 5 |
  | Qualité de l'affichage (colonnes alignées) | 10 |
Qualité du code | Modularité fonctionnelle |10|
  | Style de programmation | 5 |
  | Documentation (en-tête du fichier et des fonctions)|5|
Makefile |Compilation, tests et nettoyage |10|
  | Téléchargement des données et génération de la page HTML | 10 |
Utilisation de Git |Commits significatifs |10|
  | Qualité des messages de commits | 5 |
**Total**  |	|        **100**  |

Plus précisément, les éléments suivants seront pris en compte:

- **Fonctionnalité (45 points)**: Le programme passe les tests *publics* et
  *privés* en affichant le résultat attendu.

- **Qualité du code (20 points)**: Les identifiants utilisés sont significatifs
  et ont une syntaxe uniforme, le code est bien indenté, il y a de l'aération
  autour des opérateurs et des parenthèses, le programme est simple et lisible.
  Pas de bout de code en commentaire ou de commentaires inutiles. Pas de valeur
  magique. Le code doit être bien factorisé (pas de redondance). Il est
  décomposé en petites fonctions qui effectuent des tâches spécifiques. La
  présentation est soignée. *Note*: si votre style est impeccable mais que
  votre travail est peu avancé, vous aurez peu de points pour cette partie. Le fichier `README.md` est complet et respecte
  le format Markdown. L'en-tête du fichier `geonames.c` est bien documentée,
  de même que chacune des fonctions (*docstrings*) en suivant le standard
  Javadoc.

- **Makefile (20 points)**: Le Makefile supporte les appels `make`, `make html`, `make test`, `make database` et `make clean`. Toutes les dépendances de ces cibles sont présentes.

- **Utilisation de Git (15 points)**: Les modifications sont réparties en
  *commits* atomiques. Le fichier `.gitignore` est complet. Les messages de
  *commit* sont significatifs, uniformes et suivent une des conventions
  suggérées.

---

Si vous êtes arrivé à ce stade du document, c'est que vous l'avez lu en entier, comme demandé dans la consigne au tout début du sujet. Envoyez en message privé au professeur sur le Slack une photo d'un animal mignon (p.-ex. une loutre, un chaton, un chiot, un capybara) pour en témoigner. Les cinq (5) premiers étudiants à remplir cette condition bénéficieront de cinq (5) points bonus sur l'évaluation de ce projet (la note maximale reste de 100). 

---
