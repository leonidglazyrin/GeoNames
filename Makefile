geonames: geonames.c
	gcc -o geonames -std=c11 geonames.c

test:
	bats check.bats
