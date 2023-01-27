CC=gcc
FLAGS=-Wall -Wextra -g 
OBJ=main.o 
FSDL=sdl2-config --cflags --libs
FSDL2=-lSDL2

prog:main.o 
	$(CC) -o prog $(OBJ) $(FLAGS) -lm $(FSDL2)


main.o: main.c 
	$(CC) -c main.c  $(FLAGS) -lm $(FSDL2)



clean:
	rm $(OBJ) prog