#Makefile


CC = gcc
CFLAGS = -g -W -Wall
LDLIBS = -lm
INCS = -I"https://github.com/iceteawithlemon/PP1" 

OUTFILES= testN test-point

all: $(OUTFILES)


testN: NN.o 
	${CC} NN.o -o testN $(LDLIBS) $(INCS)

NN.o: NN.c ArbresBinaires.h nearest_neighbour.h point.h
	$(CC) -c -std=c99 $(CFLAGS) NN.c $(LDLIBS) $(INCS)



test-point: test-point.o point.o
	${CC} test-point.o point.o -o test-point $(LDLIBS)

test-point.o: test-point.c
	$(CC) -c -std=c99 $(CFLAGS) test-point.c $(LDLIBS)

point.o: point.c point.h
	$(CC) -c -std=c99 $(CFLAGS) point.c



dep:
	$(CC) -MM *.c

.PHONY: clean

clean:
	-rm -f *.o *~ $(OUTFILES)