CFLAGS=-g
CC=gcc

PROG=snake test
FILE1=main
FILE2=canvas
all: $(PROG)

LIBS= -lncurses -Wall -Wextra
SRC=./src/

main.o: $(SRC)main.c canvas.h
	$(CC) $(CFLAGS) -c $(SRC)main.c
canvas.o: $(SRC)canvas.c canvas.h
	$(CC) $(CFLAGS) -c $(SRC)canvas.c
worm.o: $(SRC)worm.c canvas.h
	$(CC) $(CFLAGS) -c $(SRC)worm.c
#=====================================================
snake: main.o canvas.o worm.o
	$(CC) $(CFLAGS) -o snake main.o canvas.o worm.o $(LIBS) && ./snake
test: test.c
	$(CC) $(CFLAGS) -o test test.c $(LIBS) && ./test

clean:
	rm -r *.o $(PROG)

backup: clean
	cd .. ; tar czvf dircache.tar.gz dir-cache @file
