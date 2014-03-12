#Makefile


CC = gcc
CFLAGS = -g -W -Wall
LDLIBS = -lm
INCS = -I"https://github.com/iceteawithlemon/PP1" 

OUTFILES= testN

all: $(OUTFILES)


testN: main.o Liste.o projetAlgo.o point.o
	${CC} main.o Liste.o projetAlgo.o point.o -o testN $(LDLIBS) $(INCS)
	
main.o: main.c  point.h projetAlgo.h Liste.h 
	$(CC) -c -std=c99 $(CFLAGS) main.c $(LDLIBS) $(INCS)

#LDCtest: LDCtest.o
#	${CC} LDCtest.o -o LDCtest $(LDLIBS) $(INCS)
	
#LDCtest.o: LDCtest.c LDCDynam.h point.h
#	$(CC) -c -std=c99 $(CFLAGS) LDCtest.c $(LDLIBS) $(INCS)

Liste.o: Liste.c point.h
	$(CC) -c -std=c99 $(CFLAGS) Liste.c $(LDLIBS) $(INCS)

projetAlgo.o: projetAlgo.c Liste.h point.h
	$(CC) -c -std=c99 $(CFLAGS) projetAlgo.c $(LDLIBS) $(INCS)
	
point.o: point.c point.h
	$(CC) -c -std=c99 $(CFLAGS) point.c



dep:
	$(CC) -MM *.c

.PHONY: clean

clean:
	-rm -f *.o *~ $(OUTFILES)