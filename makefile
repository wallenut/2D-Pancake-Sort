CC=gcc
CFLAGS= -std=c99 -pedantic -Wall -g3

HWK4= /c/cs223/Hwk4
HWK5= /c/cs223/Hwk5


pancake: pancake.o hash.o Queue.o
	${CC} ${CFLAGS} -o $@ $^ 

pancake.o: pancake.c Queue.h hash.h
	${CC} ${CFLAGS} -c pancake.c

hash.o: hash.h 

Queue.o: Queue.h
