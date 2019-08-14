CC=g++
# add -Wall?
CFLAGS=-I/usr/include/python3.5m -c -std=c++11
# CFLAGS=-c -g -std=c++11
objects = main.o py_init.o

# ultimate target
all: gomoku

# 搞了好久才编译出来
gomoku: $(objects)
	$(CC) $(objects) -lpython3.5m -lpthread -ldl  -lutil -lm -O2 -o test.out

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

py_init.o: py_init.cpp
	$(CC) $(CFLAGS) py_init.cpp
board.o: board.cpp
	$(CC) $(CFLAGS) board.cpp

tree_search.o: tree_search.cpp
	$(CC) $(CFLAGS) tree_search.cpp

value.o: value.cpp
	$(CC) $(CFLAGS) value.cpp

clean:
	rm *.o *.gch *.out gomoku
