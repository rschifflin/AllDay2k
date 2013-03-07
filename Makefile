CC = clang++
CFLAGS = -o
CLIBS = -lSDL -lGL

Solver.exe : main.o Board.o Timer.o
	$(CC) $(CFLAGS) $@ main.o Board.o Timer.o $(CLIBS)

main.o : main.cpp Board.hpp Timer.hpp
	$(CC) -c main.cpp

Board.o : Board.cpp Primitives.hpp
	$(CC) -c Board.cpp

Timer.o: Timer.cpp
	$(CC) -c Timer.cpp
