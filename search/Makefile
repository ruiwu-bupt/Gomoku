CC=g++
# add -Wall?
# CFLAGS=-I/usr/include/python3.5m -c -std=c++11
CFLAGS=-c -v -std=c++11
# CFLAGS=-c -g -std=c++11
objects = board.o predictor.o mcts.o selfplay.o

# ultimate target
all: gomoku

# 搞了好久才编译出来
# gomoku: $(objects)
# 	$(CC) $(objects) -lpython3.5m -lpthread -ldl  -lutil -lm -O2 -o test.out

gomoku: $(objects)
	$(CC) $(objects) -lncursesw -O2 -o gomoku.out

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

py_init.o: py_init.cpp
	$(CC) $(CFLAGS) py_init.cpp

board.o: board.cpp
	$(CC) $(CFLAGS) board.cpp

predictor.o: predictor.cpp
	$(CC) $(CFLAGS) predictor.cpp

selfplay.o: selfplay.cpp
	$(CC) $(CFLAGS) selfplay.cpp

mcts.o: MCTS.cpp
	$(CC) $(CFLAGS) mcts.cpp


clean:
	rm *.o *.gch *.out gomoku
