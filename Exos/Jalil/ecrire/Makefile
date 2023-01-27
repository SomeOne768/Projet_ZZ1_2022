CC=gcc
FLAGS=-Wall -Wextra -g -lm
OBJ= main.o 
FSDL= -lSDL2 -lSDL2_image -lSDL2_ttf


prog: $(OBJ)
	$(CC) -o prog $(OBJ) $(FLAGS) $(FSDL) 

main.o: main.c
	$(CC) -c main.c $(FLAGS) $(FSDL)


clean:
	rm $(OBJ)

clean_exe:
	rm prog
