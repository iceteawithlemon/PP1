#Makefile


CC = gcc
CFLAGS = -g -W -Wall 

INCS = -I"https://github.com/iceteawithlemon/PP1/include" 

OUTFILES= testN

all: $(OUTFILES)


testN: main.o Liste.o projetAlgo.o point.o
	${CC} main.o Liste.o projetAlgo.o point.o -o testN -lm $(INCS)
	
main.o: main.c  point.h projetAlgo.h Liste.h 
	$(CC) -c -std=c99 $(CFLAGS) main.c -lm $(INCS)


Liste.o: Liste.c point.h
	$(CC) -c -std=c99 $(CFLAGS) Liste.c -lm $(INCS)

projetAlgo.o: projetAlgo.c Liste.h point.h
	$(CC) -c -std=c99 $(CFLAGS) projetAlgo.c -lm $(INCS)
	
point.o: point.c point.h
	$(CC) -c -std=c99 $(CFLAGS) point.c



dep:
	$(CC) -MM *.c

.PHONY: clean

clean:
	-rm -f *.o *~ $(OUTFILES)