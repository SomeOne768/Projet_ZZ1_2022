CC=gcc
FLAGS=-Wall -Wextra -g -lm
OBJ=main.o dessin.o

FSDL=-lSDL2



prog:$(OBJ)
	$(CC) -o prog $(OBJ) $(FLAGS) $(FSDL)

main.o : main.c dessin.h
	$(CC) -c main.c $(FLAGS) $(FSDL)


dessin.o : dessin.c dessin.h
	$(CC) -c dessin.c  $(FLAGS) $(FSDL)


clean:
	rm $(OBJ)

