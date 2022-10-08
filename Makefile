CC = gcc
OPTIONS = -Wall -Wextra -std=c11
EXE = geonames

geonames: geonames.c
	$(CC) geonames.c $(OPTIONS) -o $(EXE)

html:
	pandoc -f markdown -t html5 -o README.html README.md -c misc/github-pandoc.css
	pandoc -f markdown -t html5 -o sujet.html sujet.md -c misc/github-pandoc.css

database:
	curl -O -s http://download.geonames.org/export/dump/countryInfo.txt
	curl -O -s download.geonames.org/export/dump/cities15000.zip
	unzip -o -q cities15000.zip
	rm cities15000.zip

test: geonames database
	bats check.bats

clean :
	rm *.o -f
	rm *.html -f
	rm $(EXE) -f
	rm cities15000.zip -f