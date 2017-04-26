OBJS = 8puzzle.o board.o
CC = g++
OGL= -lGL -lGLU -lglut -lSOIL

8puzzle: $(OBJS)
	$(CC) 8puzzle.o board.o -o 8puzzle $(OGL)

8puzzle.o: 8puzzle.cpp 8puzzle.h board.h
	$(CC) -c 8puzzle.cpp $(OGL)

board.o: board.cpp board.h
	$(CC) -c board.cpp $(OGL)

clean:
	\rm *.o *~ 8puzzle



