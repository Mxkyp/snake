CFLAGS=-g
CC=gcc

PROG=snake test
FILE1=main
FILE2=
all: $(PROG)


LIBS= -lncurses -Wall -Wextra
SRC=./src/


main.o: $(SRC)main.c display.h
	$(CC) $(CFLAGS) -c $(SRC)main.c

display.o: $(SRC)display.c display.h
	$(CC) $(CFLAGS) -c $(SRC)display.c

fruit.o: $(SRC)fruit.c fruit.h snake.h
	$(CC) $(CFLAGS) -c $(SRC)fruit.c

snake.o: $(SRC)snake.c snake.h fruit.h main.h
	$(CC) $(CFLAGS) -c $(SRC)snake.c

#=====================================================

snake: main.o fruit.o snake.o display.o
	$(CC) $(CFLAGS) -o snake main.o fruit.o snake.o display.o $(LIBS) && ./snake

test: test.c
	$(CC) $(CFLAGS) -o test test.c $(LIBS) && ./test

clean:
	rm -r *.o $(PROG)

backup: clean
	cd .. ; tar czvf dircache.tar.gz dir-cache @file
