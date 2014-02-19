CC = gcc
CFLAGS = -g -W -Wall


OUTFILES= test-point

all: $(OUTFILES)

test-point: test-point.o point.o
	${CC} test-point.o -o test-point



point.o: point.c point.h
	$(CC) -c -std=c99 $(CFLAGS) point.c


dep:
	$(CC) -MM *.c

.PHONY: clean
clean:
	-rm -f *.o  $(OUTFILES)
