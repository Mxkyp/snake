CFLAGS=-g
CC=gcc

PROG=snake test
FILE1=main
FILE2=canvas
all: $(PROG)

LIBS= -lncurses -Wall -Wextra


main.o: main.c canvas.h
	$(CC) $(CFLAGS) -c main.c
canvas.o: canvas.c canvas.h
	$(CC) $(CFLAGS) -c canvas.c
worm.o: worm.c canvas.h
	$(CC) $(CFLAGS) -c worm.c
#=====================================================
snake: main.o canvas.o worm.o
	$(CC) $(CFLAGS) -o snake main.o canvas.o worm.o $(LIBS) && ./snake
test: test.c
	$(CC) $(CFLAGS) -o test test.c $(LIBS) && ./test

clean:
	rm -r *.o $(PROG)

backup: clean
	cd .. ; tar czvf dircache.tar.gz dir-cache @file
