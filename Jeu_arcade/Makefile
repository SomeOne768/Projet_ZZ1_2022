CC = gcc
FLAGS = -g -Wall -Wextra -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lSDL2_ttf
OBJ = main.o markov.o animation.o ecriture.o

prog: $(OBJ)
	$(CC) -o prog $(OBJ) $(FLAGS)

main.o: main.c markov.h
	$(CC) -c main.c $(FLAGS)

animation.o: animation.c
	$(CC) -c animation.c $(FLAGS)

testo.exe:
	gcc -o testo.exe testo.c gestion_SDL.c animation.h -Wall -Wextra -lSDL2 -lm -lSDL2_image 

markov.o: markov.c markov.h
	$(CC) -c markov.c $(FLAGS)

ecriture.o: ecriture.c ecriture.h
	$(CC) -c ecriture.c $(FLAGS)

clean:
	rm $(OBJ)