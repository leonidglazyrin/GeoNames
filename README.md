# TP1: GeoNames


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

Le contenu du projet:

* `README.md`: ce fichier
* `Makefile`: permet d'automatiser la compilation
* `check.bats`: serie de tests
* `sujet.md`: sujet du travail
* `geonames.c`: code source
* `.gitignore`: ignorer certains fichiers lors de la gestion des version
* `.gitla-ci.yml`: instructions d'intégration continu avec GitLab CI/CD
* `github-pandoc.css`: style CSS pour les version HTML des fichiers généré
par la commande `make html`

[Contraintes du travail](sujet.md)

## Auteur

Leonid Glazyrin (GLAL77080105)

## Fonctionnement

Pour faire fonctionner le projet il vous faudra vous assurez d'avoir `git`
installé, ainsi que `make`, `unzip`, `pandoc`, `bats` et peut-être quelques 
autres programme sur votre terminal. Referez vous à la section [Dépendances](#dépendances) 
pour les sites officiels.

Tout d'abord cloner le projet avec la commande :
```sh
git clone https://gitlab.info.uqam.ca/glazyrin.leonid/inf3135-tp1-a22.git
```
Si le projet n'est pas publique vous devrez vous authentifier.

Ensuite exécuté les commandes suivantes pour vous déplacer dans le répertoire, 
compiler le programme et télécharger les données nécessaires à l'exécution :
```sh
cd inf3135-tp1-a22
make
make database
```

Finalement pour pourrait exécuter le programme avec un chiffre `n` entre 1 et 5000 :
```sh
./geonames n
```

Alternativement le nombre peut être passé par un fichier :
```sh
./geonames < fichier-contenant-un-nombre
```


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

* [Manipuler des fichier en C](https://www.programiz.com/c-programming/c-file-input-output)
* [Compter nombre de ligne dans un fichier](https://www.geeksforgeeks.org/c-program-count-number-lines-file/)
* [Iterer sur les champs d'une ligne de texte](https://opensource.apple.com/source/Libc/Libc-186/string.subproj/strsep.c.auto.html)
* [Tri rapide](https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm)
* [Redirection de l'entrée standard](https://stackoverflow.com/questions/3495092/read-from-file-or-stdin)
