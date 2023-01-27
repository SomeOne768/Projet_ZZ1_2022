CC=gcc
FLAGS=-Wall -Wextra -g -lm 
OBJ=main.o regles.o monde_limite.o monde_tore.o

FSDL=-lSDL2



prog:$(OBJ)
	$(CC) -o prog $(OBJ) $(FLAGS) $(FSDL)

main.o : main.c monde_limite.h regles.h
	$(CC) -c main.c $(FLAGS) $(FSDL)

regles.o : regles.c regles.h
	$(CC) -c regles.c $(FlAGS) $(FSDL)

monde_limite.o : monde_limite.c monde_limite.h
	$(CC) -c monde_limite.c  $(FLAGS) $(FSDL)

monde_tore.o : monde_tore.c monde_tore.h
	$(CC) -c monde_tore.c $(FLAGS) $(FSDL)

clean:
	rm $(OBJ)

