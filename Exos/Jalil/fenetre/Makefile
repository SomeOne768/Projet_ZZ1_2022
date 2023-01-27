CC=gcc
FLAGS=-Wall -Wextra -g 
OBJ=main.o gestionSDL2.o
FSDL=sdl2-config --cflags --libs
FSDL2=-lSDL2

prog:main.o gestionSDL2.o
	$(CC) -o prog $(OBJ) $(FLAGS) -lm $(FSDL2)


main.o: main.c gestionSDL2.h
	$(CC) -c main.c gestionSDL2.h $(FLAGS) -lm $(FSDL2)

gestionSDL2.o: gestionSDL2.c gestionSDL2.h
	$(CC) -c gestionSDL2.c $(FLAGS) -lm $(FSDL2)

testo.exe: testo.c
	gcc -o testo.exe testo.c -lm

clean:
	rm $(OBJ) prog