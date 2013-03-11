CC = clang++
CFLAGS = -Weverything -o
CLIBS = -lSDL -lGL

Solver.exe : main.o Board.o Timer.o GLNumbers.o
	$(CC) $(CFLAGS) $@ main.o Board.o Timer.o GLNumbers.o $(CLIBS)

main.o : main.cpp Board.hpp Timer.hpp Primitives.hpp GLNumbers.hpp
	$(CC) -c main.cpp

Board.o : Board.cpp Primitives.hpp
	$(CC) -c Board.cpp

Timer.o: Timer.cpp
	$(CC) -c Timer.cpp

GLNumbers.o: GLNumbers.cpp
	$(CC) -c GLNumbers.cpp
