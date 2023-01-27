CC=gcc
FLAGS=-Wall -Wextra -g -lm -lSDL2_image -lSDL2_ttf
OBJ=main.o  texture.o 

FSDL=-lSDL2



prog:$(OBJ)
	$(CC) -o prog $(OBJ) $(FLAGS) $(FSDL)

main.o : main.c texture.h
	$(CC) -c main.c $(FLAGS) $(FSDL)

texture.o : texture.c texture.h
	$(CC) -c texture.c $(FlAGS) $(FSDL)

# monde_limite.o : .c .h
# 	$(CC) -c .c  $(FLAGS) $(FSDL)

# .o : .c .h
# 	$(CC) -c .c $(FLAGS) $(FSDL)

clean:
	rm $(OBJ)

