CC = g++
CFLAGS = -Wall
EXEC = huff

all: $(EXEC)

huff: Arbre.o main.o Huffman.o
	$(CC) $(CFLAGS) -o program main.o Arbre.o Huffman.o

Huffman.o: Huffman.cpp Huffman.hpp
	$(CC) $(CFLAGS) -o Huffman.o -c Huffman.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -o main.o -c main.cpp

Arbre.o: Arbre.cpp Arbre.hpp
	$(CC) $(CFLAGS) -o Arbre.o -c Arbre.cpp

clean:
	rm -rf *.o

mrproper: clean
	rm -rf huff
