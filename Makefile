Solver.exe : main.o Board.o
	clang++ -o Solver.exe main.o Board.o -lSDL -lGL

main.o : main.cpp Board.hpp
	clang++ -c main.cpp

Board.o : Board.cpp Primitives.hpp
	clang++ -c Board.cpp -std=c++0x

