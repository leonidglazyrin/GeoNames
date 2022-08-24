prog=geonames
help_first_line="Usage: ./geonames <NUMBER OF CITIES>"


@test "test0 : Aucun argument, afficher aide" {
    skip
    run ./$prog
    [ "$status" -eq 4 ]
    [ "${lines[0]}" = "$help_first_line" ]
}

@test "test1 : Trop d arguments" {
    skip
    run ./$prog 4 5 2
    [ "$status" -eq 1 ]
    [ "${lines[0]}" = "trop d arguments" ]
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
    [ "${lines[0]}" = "nombre de ville invalide" ]
}

@test "test4 : Argument caratere invalide" {
    skip
    run ./$prog K
    [ "$status" -eq 3 ]
    [ "${lines[0]}" = "argument invalide" ]
}

@test "test5 : Argument chaine de carateres invalide" {
    skip
    run ./$prog INF3135
    [ "$status" -eq 3 ]
    [ "${lines[0]}" = "argument invalide" ]
}

@test "test6 : afficher tableau de 5 villes" {
    skip
    run ./$prog 5
    [ "$status" -eq 0 ]
}