#Makefile


CC = gcc
CFLAGS = -g -W -Wall 

INCS = -I"https://github.com/iceteawithlemon/PP1/include" 

OUTFILES= testN

all: $(OUTFILES)


testN: main.o projetAlgo.o point.o matrice.o 
	$(CC) main.o  projetAlgo.o point.o matrice.o -o testN -lm $(INCS)
	
main.o: main.c point.h projetAlgo.h matrice.h 
	$(CC) -c -std=c99 $(CFLAGS) main.c -lm $(INCS)


projetAlgo.o: projetAlgo.c matrice.h point.h 
	$(CC) -c -std=c99 $(CFLAGS) projetAlgo.c -lm $(INCS)
	
point.o: point.c point.h
	$(CC) -c -std=c99 $(CFLAGS) point.c -lm $(INCS)

matrice.o: matrice.c matrice.h point.h
	$(CC) -c -std=c99 $(CFLAGS) matrice.c -lm $(INCS)


dep:
	$(CC) -MM *.c

.PHONY: clean

clean:
	-rm -f *.o *~ $(OUTFILES)
