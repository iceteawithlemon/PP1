#Makefile


CC = gcc
CFLAGS = -g -W -Wall
LDLIBS = -lm
INCS = -I"C:\Users\Manon\Desktop\L2 info\test\test devc++" 

OUTFILES= testN test-point

all: $(OUTFILES)


testN: main.o 
	${CC} main.o -o testN $(LDLIBS) $(INCS)
main.o: main.c  point.h projetAlgo.h Liste.h
	$(CC) -c -std=c99 $(CFLAGS) main.c $(LDLIBS) $(INCS)

	
LDCtest: LDCtest.o
	${CC} LDCtest.o -o LDCtest $(LDLIBS) $(INCS)
LDCtest.o: LDCtest.c LDCDynam.h point.h
	$(CC) -c -std=c99 $(CFLAGS) LDCtest.c $(LDLIBS) $(INCS)

	
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