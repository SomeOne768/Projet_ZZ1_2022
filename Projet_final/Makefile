CC=gcc
FLAGS = -g -Wall -Wextra -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lSDL2_ttf
OBJ= main.o affichageSDL.o apparition.o modelisation_temps.o ecriture.o apprentissage.o labyrinthe.o affichage_laby.o 

prog: $(OBJ)
	$(CC) -o prog $(OBJ)  $(FLAGS)

main.o: main.c affichageSDL.h modelisation_temps.h labyrinthe.h  affichage_laby.h 
	$(CC) -c main.c $(FLAGS)

affichageSDL.o: affichageSDL.c affichageSDL.h  modelisation.h
	$(CC) -c affichageSDL.c $(FLAGS)

apparition.o: apparition.c apparition.h
	$(CC) -c apparition.c $(FLAGS)

modelisation.o: modelisation.c modelisation.h apparition.h
	$(CC) -c modelisation.c $(FLAGS)

modelisation_temps.o: modelisation_temps.c modelisation_temps.h apparition.h
	$(CC) -c modelisation_temps.c $(FLAGS)

apprentissage.o: apprentissage.c apprentissage.h modelisation_temps.h apparition.h
	$(CC) -c apprentissage.c $(FLAGS)

ecriture.o: ecriture.c ecriture.h
	$(CC) -c ecriture.c $(FLAGS)

testo.exe: modelisation.h
	$(CC) -o testo.exe testo.c modelisation_temps.c apprentissage.c  apparition.c $(FLAGS)

testomain.exe:
	$(CC) -o testomain.exe testomain.c modelisation_temps.c apprentissage.c apparition.c affichageSDL.c ecriture.c $(FLAGS)

entrainement.exe: entrainement_laby.o labyrinthe.o
	$(CC) -o entrainement.exe entrainement_laby.o labyrinthe.o $(FLAGS)


entrainement_laby.o: entrainement_laby.c labyrinthe.h 
	$(CC) -c entrainement_laby.c $(FLAGS)

labyrinthe.o: labyrinthe.c labyrinthe.h modelisation_temps.h
	$(CC) -c labyrinthe.c $(FLAGS)

affichage_laby.o: affichage_laby.c affichage_laby.h modelisation_temps.h
	$(CC) -c affichage_laby.c $(FLAGS)


clean:
	rm $(OBJ) prog
