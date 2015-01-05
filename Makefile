CC = g++
CFLAGS = -Wall
EXEC = program.exe

all: $(EXEC)

program.exe: Arbre.o main.o
	$(CC) $(CFLAGS) -o program main.o Arbre.o

main.o: main.cpp
	$(CC) $(CFLAGS) -o main.o -c main.cpp

Arbre.o: Arbre.cpp Arbre.hpp
	$(CC) $(CFLAGS) -o Arbre.o -c Arbre.cpp

clean:
	rm -rf *.o
