CC = g++
CFLAGS = -std=c++11

all: othello

othello: player.o board.o game.o
	${CC} ${CFLAGS} -o ../othello othello.cpp player.o board.o game.o

game.o: game.h game.cpp player.o
	${CC} ${CFLAGS} -c game.cpp

board.o: board.h board.cpp
	${CC} ${CFLAGS} -c board.cpp

player.o: player.h player.cpp
	${CC} ${CFLAGS} -c player.cpp 

clean:
	rm ../othello *.o


