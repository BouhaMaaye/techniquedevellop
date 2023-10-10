INC=include
SRC=src
OBJ=obj
BIN=bin
DOC=doc

$(BIN)/main: $(OBJ)/main.o $(OBJ)/io.o $(OBJ)/jeu.o $(OBJ)/grille.o
	cd $(BIN) && gcc -o main ../$(OBJ)/main.o ../$(OBJ)/io.o ../$(OBJ)/jeu.o ../$(OBJ)/grille.o -lm

$(OBJ)/main.o: $(SRC)/main.c $(INC)/*.h
	cd $(OBJ) && gcc -c ../$(SRC)/main.c

$(OBJ)/jeu.o: $(SRC)/jeu.c $(INC)/jeu.h
	cd $(OBJ) && gcc -c ../$(SRC)/jeu.c

$(OBJ)/grille.o: $(SRC)/grille.c $(INC)/grille.h
	cd $(OBJ) && gcc -c ../$(SRC)/grille.c

$(OBJ)/io.o: $(SRC)/io.c $(INC)/io.h
	cd $(OBJ) && gcc -c ../$(SRC)/io.c

clean:
	rm -rf $(OBJ)/*.o

rmexec: clean
	rm -rf $(BIN)/main

dist:
	tar -J -cvf MaayeBouha-GoL-"verssion3".tar.xz $(SRC)/*.c $(INC)/*.h $(OBJ)/*.o $(BIN)/main Makefile $(DOC)/*

