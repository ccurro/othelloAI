CC = g++
CFLAGS = -std=c++11

all: othello

othello:
	${CC} ${CFLAGS} -o othello othello.cpp

clean:
	rm othello


