CC=gcc
FLAGS=-Wall -Wextra -g
OBJ=main.o jeu.o regle.o
FSDL= -lSDL2
FTTF= -lSDL2_ttf

prog: $(OBJ)
	$(CC) -o prog $(OBJ) $(FLAGS) $(FSDL) $(FTTF)

main.o: main.c jeu.h regle.h
	$(CC) -c main.c $(FLAGS) $(FSDL) $(FTTF)

jeu.o: jeu.c jeu.h
	$(CC) -c jeu.c $(FLAGS)

regle.o: regle.c regle.h
	$(CC) -c regle.c $(FLAGS)


testo.exe: jeu.o testo.o regle.o
	$(CC) -o testo.exe testo.o jeu.o regle.o $(FLAGS) $(FSDL)

testo.o: testo.c jeu.h regle.h
	$(CC) -c testo.c $(FLAGS) $(FSDL)

clean:
	rm $(OBJ)

clean_sauv:
	rm sauvegarde.txt
