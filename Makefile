CC = clang++
CFLAGS = -Weverything -Wno-padded -Wno-weak-vtables -g 

#CC = g++
#CFLAGS = -Wold-style-cast -g
CLIBS = -lSDL -lGL

Solver.exe : main.o Board.o Timer.o GLNumbers.o GUI.o 
	$(CC) $(CFLAGS) -o $@ main.o Board.o Timer.o GLNumbers.o GUI.o $(CLIBS)

main.o : main.cpp Board.hpp Timer.hpp Primitives.hpp GLNumbers.hpp GUI.hpp
	$(CC) $(CFLAGS) -c main.cpp

Board.o : Board.cpp Primitives.hpp
	$(CC) $(CFLAGS) -c Board.cpp

Timer.o: Timer.cpp
	$(CC) $(CFLAGS) -c Timer.cpp

GLNumbers.o: GLNumbers.cpp
	$(CC) $(CFLAGS) -c GLNumbers.cpp

GUI.o: GUI.cpp
	$(CC) $(CFLAGS) -c GUI.cpp
