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

Décrivez ici le projet. Commencez d'abord par une description générale, puis
donnez ensuite des détails. Indiquez le contexte dans lequel ce travail est
accompli (cours, sigle, enseignant, université).

Aussi, insérer un lien vers le [sujet du travail](sujet.md).

## Auteur

Indiquez ici votre prénom et nom, puis votre code permanent entre parenthèses,
sans mettre en gras ou en italique.

Par exemple,

Serge Dogny (ABCD12345678)

## Fonctionnement

Expliquez d'abord en mots comment faire fonctionner le projet (imaginez que la
personne qui l'utilisera ne connaît pas C, ne connaît pas le projet et souhaite
seulement saisir une série de commandes pour l'exécuter). En particulier,
indiquez les commandes qui doivent être entrées pour la compilation et
l'exécution.

## Tests

Expliquez ici comment lancer la suite de tests automatiques avec la commande
`make test`, ainsi que le résultat que vous obtenez.

## Dépendances

Indiquez les dépendances du projet, avec lien officiel. Il faudrait au moins
mentionner GCC et [Bats](https://github.com/bats-core/bats-core). Utiliser une
liste à puces pour donner la liste des dépendances.

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
