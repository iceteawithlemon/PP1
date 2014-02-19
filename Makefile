CC = gcc
CFLAGS = -g -W -Wall
LDLIBS = -lm


OUTFILES= test-point

all: $(OUTFILES)

test-point: test-point.o point.o
	${CC} test-point.o point.o -o test-point $(LDFLAGS)

test-point.o: test-point.c
	$(CC) -c -std=c99 $(CFLAGS) test-point.c $(LDFLAGS)

point.o: point.c point.h
	$(CC) -c -std=c99 $(CFLAGS) point.c


dep:
	$(CC) -MM *.c

.PHONY: clean
clean:
	-rm -f *.o *~ $(OUTFILES)
