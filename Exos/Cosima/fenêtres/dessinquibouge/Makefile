CC=gcc
FLAGS=-Wall -Wextra -g
OBJ=dessin.o
SDL= -lSDL2
MATHS= -lm

prog: dessin.o
	$(CC) -o prog $(OBJ) $(FLAGS) $(SDL) $(MATHS)

dessin.o:dessin.c
	$(CC) -c dessin.c $(FLAGS) $(SDL) $(MATHS)
clean:
	rm $(OBJ)