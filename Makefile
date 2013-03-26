CC = clang++
CFLAGS = -Weverything -Wno-padded -Wno-weak-vtables -g -std=c++0x

#CC = g++
#CFLAGS = -Wold-style-cast -g
CLIBS = -lSDL -lGL

Solver.exe : main.o Board.o Timer.o GLNumbers.o GUI.o Solver.o 
	$(CC) $(CFLAGS) -o $@ main.o Board.o Timer.o GLNumbers.o GUI.o Solver.o $(CLIBS)

main.o : main.cpp Board.hpp Timer.hpp Primitives.hpp GLNumbers.hpp GUI.hpp
	$(CC) $(CFLAGS) -c main.cpp

Solver.o : Solver.cpp Board.hpp
	$(CC) $(CFLAGS) -c Solver.cpp

Board.o : Board.cpp Primitives.hpp
	$(CC) $(CFLAGS) -c Board.cpp

Timer.o: Timer.cpp
	$(CC) $(CFLAGS) -c Timer.cpp

GLNumbers.o: GLNumbers.cpp
	$(CC) $(CFLAGS) -c GLNumbers.cpp

OpenSet.o: OpenSet.cpp
	$(CC) $(CFLAGS) -c OpenSet.cpp

GUI.o: GUI.cpp
	$(CC) $(CFLAGS) -c GUI.cpp
