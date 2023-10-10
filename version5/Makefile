INC=include
SRC=src
OBJ=obj
BIN=bin
DOC=doc
LIB=lib
MODE=GRAPHIC
CPPFLAGS=
LDFLAGS=

ifeq ($(MODE),TEXTE)
	IOC=io.c
	IOO=io.o
else
	IOC=graphic_io.c
	IOO=graphic_io.o
	CPPFLAGS += -Iinclude -I/usr/include/cairo -DGRAPHIC
	LDFLAGS += -lcairo -lm -lX11
endif

$(BIN)/main: $(OBJ)/main.o $(OBJ)/$(IOO) $(OBJ)/jeu.o $(OBJ)/grille.o
	ar rcs $(LIB)/libjeu.a $(OBJ)/*.o
	cd $(BIN) && gcc -Wall -o main ../$(OBJ)/main.o ../$(OBJ)/$(IOO) ../$(OBJ)/jeu.o ../$(OBJ)/grille.o $(LDFLAGS) && rm ../$(OBJ)/$(IOO)

$(OBJ)/main.o: $(SRC)/main.c $(INC)/*.h
	cd $(OBJ) && gcc -c ../$(SRC)/main.c $(CPPFLAGS)

$(OBJ)/jeu.o: $(SRC)/jeu.c $(INC)/jeu.h
	cd $(OBJ) && gcc -c ../$(SRC)/jeu.c

$(OBJ)/grille.o: $(SRC)/grille.c $(INC)/grille.h
	cd $(OBJ) && gcc -c ../$(SRC)/grille.c

$(OBJ)/$(IOO): $(SRC)/$(IOC) $(INC)/io.h
	cd $(OBJ) && gcc -c ../$(SRC)/$(IOC) $(CPPFLAGS) 

clean:
	rm -rf $(OBJ)/*.o

rmexec: clean
	rm -rf $(BIN)/main

dist:
	tar -J -cvf MaayeBouha-GoL-"verssion5".tar.xz $(SRC)/*.c $(INC)/*.h $(OBJ)/*.o $(BIN)/main $(LIB)/libjeu.a Makefile $(DOC)/*

