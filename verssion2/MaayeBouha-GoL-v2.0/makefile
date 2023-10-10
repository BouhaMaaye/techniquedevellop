main: main.o grille.o io.o jeu.o
	gcc -o main main.o grille.o io.o jeu.o -lm

main.o: main.c grille.h io.h jeu.h
	gcc -c main.c

jeu.o: jeu.c jeu.h
	gcc -c jeu.c

grille.o: grille.c grille.h
	gcc -c grille.c

io.o: io.c io.h
	gcc -c io.c

clean:
	rm -rf *.o main  MaayeBouha-GoL-"v2.0".tar.xz


dist:
	tar -J -cvf MaayeBouha-GoL-"v2.0".tar.xz *.c *.h makefile doxyfile

