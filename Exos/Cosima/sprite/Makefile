CC=gcc
FLAGS=-Wall -Wextra -g
OBJ=texture.o main.o
SDL= -lSDL2 -lSDL2_image -lm -lSDL2_ttf

prog: texture.o main.o
	$(CC) -o prog $(OBJ) $(FLAGS) $(SDL) 

main.o:main.c
	$(CC) -c main.c $(FLAGS) $(SDL)

texture.o:texture.c
	$(CC) -c texture.c $(FLAGS) $(SDL)

clean:
	rm $(OBJ)