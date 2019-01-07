CC=g++
# add -Wall?
CFLAGS=-c -O3 -std=c++11 
# CFLAGS=-c -g -std=c++11
objects = main.o board.o tree_search.o value.o

# ultimate target
all: gomoku

gomoku: $(objects)
	$(CC) $(objects) -lncursesw -O3 -o gomoku.out

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

board.o: board.cpp
	$(CC) $(CFLAGS) board.cpp

tree_search.o: tree_search.cpp
	$(CC) $(CFLAGS) tree_search.cpp

value.o: value.cpp
	$(CC) $(CFLAGS) value.cpp

clean:
	rm *.o *.gch *.out gomoku
