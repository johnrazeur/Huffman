CC = g++
CFLAGS = -Wall
EXEC = huff
INCLUDE = inc/

all: $(EXEC)

huff: $(INCLUDE)Arbre.o main.o $(INCLUDE)Huffman.o
	$(CC) $(CFLAGS) -o huff main.o $(INCLUDE)Arbre.o $(INCLUDE)Huffman.o

$(INCLUDE)Huffman.o: $(INCLUDE)Huffman.cpp $(INCLUDE)Huffman.hpp
	$(CC) $(CFLAGS) -o $(INCLUDE)Huffman.o -c $(INCLUDE)Huffman.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -o main.o -c main.cpp

$(INCLUDE)Arbre.o: $(INCLUDE)Arbre.cpp $(INCLUDE)Arbre.hpp
	$(CC) $(CFLAGS) -o $(INCLUDE)Arbre.o -c $(INCLUDE)Arbre.cpp

clean:
	rm -rf *.o
	rm -rf $(INCLUDE)*.o

mrproper: clean
	rm -rf huff
