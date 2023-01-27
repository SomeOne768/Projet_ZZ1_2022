CC=gcc
FLAGS=-Wall -Wextra -g -lSDL2 -lSDL2_image
OBJ=main.o labyrinthe.o affichage_laby.o

prog: main.o labyrinthe.o affichage_laby.o
	$(CC) -o prog $(OBJ) $(FLAGS)


main.o: main.c labyrinthe.h  affichage_laby.h
	$(CC) -c main.c $(FLAGS)


entrainement.exe: entrainement_laby.o labyrinthe.o
	$(CC) -o entrainement.exe entrainement_laby.o labyrinthe.o $(FLAGS)


entrainement_laby.o: entrainement_laby.c labyrinthe.h 
	$(CC) -c entrainement_laby.c $(FLAGS)

labyrinthe.o: labyrinthe.c labyrinthe.h 
	$(CC) -c labyrinthe.c $(FLAGS)

affichage_laby.o: affichage_laby.c affichage_laby.h
	$(CC) -c affichage_laby.c $(FLAGS)

clean:
	rm $(OBJ)