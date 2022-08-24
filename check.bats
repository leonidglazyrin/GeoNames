tests_folder=tests
prog=geonames
help_first_line="Usage: ./geonames <NUMBER OF CITIES>"


@test "test0 : Aucun argument" {
    skip
    run ./$prog
    [ "$status" -eq 1 ]
    [ "${lines[0]}" = "nombre arguments invalide" ]
    [ "${lines[1]}" = "$help_first_line" ]
}

@test "test1 : Trop d arguments" {
    skip
    run ./$prog 4 5 2
    [ "$status" -eq 1 ]
    [ "${lines[0]}" = "nombre arguments invalide" ]
    [ "${lines[1]}" = "$help_first_line" ]
}

@test "test2 :Nombre de ville trop petit" {
    skip
    run ./$prog 0
    [ "$status" -eq 2 ]
    [ "${lines[0]}" = "nombre de ville invalide" ]
}

@test "test3 :Nombre de ville trop grand" {
    skip
    run ./$prog 5001
    [ "$status" -eq 2 ]
    [ "${lines[0]}" = "nombre de ville invalide" ]
}

@test "test4 : Argument caractère" {
    skip
    run ./$prog K
    [ "$status" -eq 3 ]
    [ "${lines[0]}" = "type argument invalide" ]
}

@test "test5 : Argument chaine de caracteres" {
    skip
    run ./$prog INF3135
    [ "$status" -eq 3 ]
    [ "${lines[0]}" = "type argument invalide" ]
}

@test "test6 : afficher tableau de 5 villes" {
    skip
    run ./$prog 5
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "Rang   Nom                    Pays                   Population" ]
    [ "${lines[1]}" = "----   ---                    ----                   ----------" ]
    [ "${lines[2]}" = "   1   Shanghai               China                    22315474" ]
    [ "${lines[6]}" = "   5   Lagos                  Nigeria                  15388000" ]
}

@test "test7 : affiche 1 ville" {
    skip
    run ./$prog < $tests_folder/test1
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "Rang   Nom                    Pays                   Population" ]
    [ "${lines[2]}" = "   1   Shanghai               China                    22315474" ]
}

@test "test8 : affiche 10 villes" {
    skip
    run ./$prog < $tests_folder/test10
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
    [ "${lines[4999]}" = "5000   Pergamino              Argentina                   87652" ]
}

@test "test10 : affiche 2500 villes" {
    skip
    run ./$prog 2500
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "Rang   Nom                    Pays                   Population" ]
    [ "${lines[2]}" = "   1   Shanghai               China                    22315474" ]
    [ "${lines[2499]}" = "2500   Varamin                Iran                       179603" ]
}