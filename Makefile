all: prog

prog: main.o Scaner.o
	g++ main.o Scaner.o -o prog

main.o: main.cpp
	g++ -c main.cpp

Scaner.o: Scaner.cpp
	g++ -c Scaner.cpp


run: prog
