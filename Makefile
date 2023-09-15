CC = g++
CFLAGS=-std=c++11

nqueens: nqueens.o
	$(CC) -g $(CFLAGS) -o nqueens nqueens.o

nqueens.o: nqueens.cpp
	$(CC) -g $(CFLAGS) -c nqueens.cpp

clean:
	rm -f *.o
	rm nqueens