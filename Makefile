#Makefile


CC = gcc
CFLAGS = -g -W -Wall 

INCS = -I"include" 

OUTFILES= testN

all: $(OUTFILES)


testN: main.o projetAlgo.o point.o matrice.o 
	$(CC) main.o  projetAlgo.o point.o matrice.o -o testN -lm $(INCS)
	
main.o: src/main.c include/point.h include/projetAlgo.h include/matrice.h 
	$(CC) -c -std=c99 $(CFLAGS) src/main.c -lm $(INCS)


projetAlgo.o: src/projetAlgo.c matrice.h point.h 
	$(CC) -c -std=c99 $(CFLAGS) projetAlgo.c -lm $(INCS)
	
point.o: src/point.c point.h
	$(CC) -c -std=c99 $(CFLAGS) point.c -lm $(INCS)

matrice.o: src/matrice.c matrice.h point.h
	$(CC) -c -std=c99 $(CFLAGS) matrice.c -lm $(INCS)


dep:
	$(CC) -MM *.c

.PHONY: clean

clean:
	-rm -f *.o *~ $(OUTFILES)
