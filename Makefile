CC = clang++
CFLAGS = -Weverything -g 
CLIBS = -lSDL -lGL

Solver.exe : main.o Board.o Timer.o GLNumbers.o GUI.o 
	$(CC) $(CFLAGS) -o $@ main.o Board.o Timer.o GLNumbers.o GUI.o $(CLIBS)

main.o : main.cpp Board.hpp Timer.hpp Primitives.hpp GLNumbers.hpp GUI.hpp
	$(CC) -c main.cpp

Board.o : Board.cpp Primitives.hpp
	$(CC) -c Board.cpp

Timer.o: Timer.cpp
	$(CC) -c Timer.cpp

GLNumbers.o: GLNumbers.cpp
	$(CC) -c GLNumbers.cpp

GUI.o: GUI.cpp
	$(CC) -c GUI.cpp
