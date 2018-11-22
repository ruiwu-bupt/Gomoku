CC=g++
# add -Wall?
CFLAGS=-c -std=c++11

objects = main.o board.o tree_search.o value.o

# ultimate target
all: gomoku

gomoku: $(objects)
	$(CC) $(objects) -lncursesw -o gomoku

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

board.o: board.cpp
	$(CC) $(CFLAGS) board.cpp

tree_search.o: tree_search.cpp value.cpp
	$(CC) $(CFLAGS) tree_search.cpp value.cpp

clean:
	rm *.o *.gch *.out gomoku