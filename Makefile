geonames: geonames.c
	gcc -Wall -Wextra -o geonames -std=c11 geonames.c


html:


database:
	curl -O -s http://download.geonames.org/export/dump/countryInfo.txt
	curl -O -s download.geonames.org/export/dump/cities15000.zip
	sudo apt install unzip
	unzip -o -q cities15000.zip
	rm cities15000.zip

test: geonames database
	bats check.bats


clean :
	rm *.o -f
	rm *.html -f
	rm geonames -f