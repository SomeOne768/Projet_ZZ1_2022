CC=gcc
FLAGS=-Wall -Wextra -g
OBJ=fenetre.o
SDL= -lSDL2

prog: fenetre.o
	$(CC) -o prog $(OBJ) $(FLAGS) $(SDL)

fenetre.o:fenetre.c 
	$(CC) -c fenetre.c $(FLAGS) $(SDL)

clean:
	rm $(OBJ)