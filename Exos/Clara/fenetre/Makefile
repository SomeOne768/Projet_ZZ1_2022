CC=gcc
FLAGS=-Wall -Wextra -g
OBJ=main.o

FSDL=-lSDL2



prog:$(OBJ)
	$(CC) -o prog $(OBJ) $(FLAGS) $(FSDL)

main.o : main.c
	$(CC) -c main.c $(FLAGS) $(FSDL)



clean:
	rm $(OBJ)

