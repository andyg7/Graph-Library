OBJS = 8puzzle.o
CC = g++
OGL= -lGL -lGLU -lglut -lSOIL -Wno-write-strings

8puzzle: $(OBJS)
	$(CC) 8puzzle.o -o 8puzzle $(OGL)

8puzzle.o: 8puzzle.cpp 8puzzle.h
	$(CC) -c 8puzzle.cpp $(OGL)


clean:
	\rm *.o *~ 8puzzle



