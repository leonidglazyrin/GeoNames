tests_folder=tests
prog=geonames
help_first_line="Usage: ./geonames <NUMBER OF CITIES>"


@test "test0 : Aucun argument" {
    run ./$prog
    [ "$status" -eq 1 ]
    [ "${lines[0]}" = "nombre arguments invalide" ]
    [ "${lines[1]}" = "$help_first_line" ]
}

@test "test1 : Trop d arguments" {
    run ./$prog 4 5 2
    [ "$status" -eq 1 ]
    [ "${lines[0]}" = "nombre arguments invalide" ]
    [ "${lines[1]}" = "$help_first_line" ]
}

@test "test2 : Nombre de ville trop petit" {
    run ./$prog 0
    [ "$status" -eq 2 ]
    [ "${lines[0]}" = "nombre de ville invalide" ]
}

@test "test3 : Nombre de ville trop grand" {
    run ./$prog 5001
    [ "$status" -eq 2 ]
    [ "${lines[0]}" = "nombre de ville invalide" ]
}

@test "test4 : Argument caractère" {
    run ./$prog K
    [ "$status" -eq 3 ]
    [ "${lines[0]}" = "type argument invalide" ]
}

@test "test5 : Argument chaine de caracteres" {
    run ./$prog INF3135
    [ "$status" -eq 3 ]
    [ "${lines[0]}" = "type argument invalide" ]
}

@test "test6 : afficher tableau de 5 villes" {
    run ./$prog 5
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "Rang   Nom                    Pays                   Population" ]
    [ "${lines[1]}" = "----   ---                    ----                   ----------" ]
    [ "${lines[2]}" = "   1   Shanghai               China                    22315474" ]
    [ "${lines[6]}" = "   5   Lagos                  Nigeria                  15388000" ]
}

@test "test7 : affiche 1 ville" {
    run ./$prog 1
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "Rang   Nom                    Pays                   Population" ]
    [ "${lines[2]}" = "   1   Shanghai               China                    22315474" ]
}

@test "test8 : affiche 10 villes" {
    skip
    run ./$prog 10
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "Rang   Nom                    Pays                   Population" ]
    [ "${lines[1]}" = "----   ---                    ----                   ----------" ]
    [ "${lines[2]}" = "   1   Shanghai               China                    22315474" ]
    [ "${lines[11]}" = "  10   Mexico City            Mexico                   12294193" ]
}

@test "test9 : affiche 5000 villes" {
    skip
    run ./$prog 5000
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "Rang   Nom                    Pays                   Population" ]
    [ "${lines[1]}" = "----   ---                    ----                   ----------" ]
    [ "${lines[2]}" = "   1   Shanghai               China                    22315474" ]
    [ "${lines[5001]}" = "5000   Nova Lima              Brazil                      88399" ]
}

@test "test10 : affiche 2500 villes" {
    skip
    run ./$prog 2500
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "Rang   Nom                    Pays                   Population" ]
    [ "${lines[2]}" = "   1   Shanghai               China                    22315474" ]
    [ "${lines[2500]}" = "2499   Liege                  Belgium                    182597" ]
}