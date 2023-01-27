CC=gcc
FLAGS=-Wall -Wextra -g -lm
OBJ= main.o gestion_SDL.o
FSDL= -lSDL2 -lSDL2_image


prog: $(OBJ)
	$(CC) -o prog $(OBJ) $(FLAGS) $(FSDL) 

main.o: main.c gestion_SDL.h
	$(CC) -c main.c $(FLAGS) $(FSDL)

gestion_SDL.o: gestion_SDL.c gestion_SDL.h
	$(CC) -c gestion_SDL.c $(FLAGS) $(FSDL) 

clean:
	rm $(OBJ)

clean_exe:
	rm prog
