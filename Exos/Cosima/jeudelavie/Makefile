CC=gcc
FLAGS=-Wall -Wextra -g
OBJ=main.o delimite.o regles.o tore.o
SDL= -lSDL2

prog: main.o delimite.o regles.o tore.o
	$(CC) -o prog $(OBJ) $(FLAGS) $(SDL) 

main.o:main.c
	$(CC) -c main.c $(FLAGS) $(SDL)

delimite.o:delimite.c
	$(CC) -c delimite.c $(FLAGS) $(SDL)

tore.o:tore.c
	$(CC) -c tore.c $(FLAGS) $(SDL)

regles.o:regles.c
	$(CC) -c regles.c $(FLAGS)

clean:
	rm $(OBJ)