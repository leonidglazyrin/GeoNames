# TP1: GeoNames


## Format Markdown (supprimer cette section avant la remise)

N'oubliez pas de bien exploiter le format Markdown.

Sauter une ligne pour changer de paragraphe.

Mettre les noms de fichier et bout de code courts entre apostrophes inversés.
Par exemple, si vous parlez du fichier `Makefile`.

Mettre les longs bouts de code dans des blocs de code (triples apostrophes
inversés). Par exemple, vous pouvez donner un exemple de commande comme suit:

```sh
$ make
$ ls -a
```

Utiliser des listes à puces ou des énumérations le plus possible (plus agréable
à lire). Par exemple, pour décrire le contenu du projet:

* `README.md`: ce fichier
* `Makefile`: permet d'automatiser la compilation
* etc.

Bien aérer le contenu du fichier source (`README.md`). Éviter les longues
lignes dans le fichier Markdown (par exemple, limiter à 80) pour une meilleure
lisibilité avec un éditeur de texte.

## Description

Le projet [GeoNames](http://www.geonames.org/) propose gratuitement des données
géographiques sous la license [CreativeCommons](http://creativecommons.org/licenses/by/3.0/). 
Elles sont utilisées dans de nombreuses applications et promeuvent par 
la même occasion la philosophie de [l'Open data](https://fr.wikipedia.org/wiki/Open_data).

Le programme consiste à utiliser certaines de ces données pour afficher la liste des 
villes ayant la plus grande population sur notre planète. Si on éxecute l'executable 
avec, par exemple, le paramètre `10`, la liste des 10 villes les plus populées 
en ordre décroissant sera affiché.

Travail accompli dans le contexte du cours 
Construction et maintenance de logiciels (INF3135) donnee par Serge Dogny à
l'UQAM.

[Contraintes du travail](sujet.md)

## Auteur

Leonid Glazyrin (GLAL77080105)

## Fonctionnement

Expliquez d'abord en mots comment faire fonctionner le projet (imaginez que la
personne qui l'utilisera ne connaît pas C, ne connaît pas le projet et souhaite
seulement saisir une série de commandes pour l'exécuter). En particulier,
indiquez les commandes qui doivent être entrées pour la compilation et
l'exécution.

## Tests

Entrez `make test` pour exécuter la suite de tests automatiques.

Mes résultats:
```sh
ok 1 test0 : Aucun argument
ok 2 test1 : Trop d arguments
ok 3 test2 : Nombre de ville trop petit
ok 4 test3 : Nombre de ville trop grand
ok 5 test4 : Argument caractère
ok 6 test5 : Argument chaine de caracteres
ok 7 test6 : afficher tableau de 5 villes
ok 8 test7 : affiche 1 ville
not ok 9 test8 : affiche 10 villes
not ok 10 test9 : affiche 5000 villes
not ok 11 test10 : affiche 2500 villes
```
8 tests réussissent, tandis 3 échouent.

> Étant donné que les données évoluent rapidement, l'ordre des villes
change fréquement.

## Dépendances

* [GCC](https://gcc.gnu.org/)
* [Bats](https://github.com/bats-core/bats-core)
* [Unzip](https://linux.die.net/man/1/unzip)
* [Pandoc](https://pandoc.org/)
* [Bats](https://github.com/bats-core/bats-core)
* [Make](https://www.gnu.org/software/make/manual/make.html)
* [Curl](https://curl.se/)

## Références

Indiquez ici les références que vous avez utilisées pour compléter le projet,
avec l'hyperlien vers la référence. Pas besoin de mentionner les diapositives
du cours, mais si vous avez eu recours à un site d'aide, un fragment de code ou
une discussion sur un forum, mentionnez-le.

## État du projet

Indiquez toutes les tâches qui ont été complétés en insérant un `X` entre les
crochets. Si une tâche n'a pas été complétée, expliquez pourquoi (lors de la
remise, vous pouvez supprimer ce paragraphe).

* [ ] Le nom du dépôt GitLab est exactement `inf3135-tp1-a22` (Pénalité de
  **50%**).
* [ ] L'URL du dépôt GitLab est exactement (remplacer `utilisateur` par votre
  nom identifiant GitLab) `https://gitlab.info.uqam.ca/utilisateur/inf3135-tp1-a22`
  (Pénalité de **50%**).
* [ ] Les usagers `dogny_g` et `correcteurs` a accès au projet en mode *Developer*
  (Pénalité de **50%**).
* [ ] Le dépôt GitLab est un *fork* de [ce
  dépôt](https://gitlab.info.uqam.ca/inf3135-sdo/geonames)
  (Pénalité de **50%**).
* [ ] Le dépôt GitLab est privé (Pénalité de **50%**).
* [ ] Le dépôt contient au moins un fichier `.gitignore`.
* [ ] Le fichier `Makefile` permet de compiler le projet lorsqu'on entre
  `make`. Il supporte les cibles `html`, `test`, `database` et `clean`.
* [ ] Le nombre de tests qui réussissent/échouent avec la `make test` est
  indiqué quelque part dans le fichier `README.md`.
* [ ] Les sections incomplètes de ce fichier (`README.md`) ont été complétées.
* [ ] L'en-tête du fichier est documentée.
* [ ] L'en-tête des déclarations des fonctions est documentée (*docstring*).
* [ ] Le programme ne contient pas de valeurs magiques.
