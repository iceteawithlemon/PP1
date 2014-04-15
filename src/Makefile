#Makefile


CC = gcc
CFLAGS = -c -std=c99 -g -W -Wall 
SRC= $(wildcard *.c)
#OBJ= $(SRC:.c=.o)
OBJ=  projetAlgo.o point.o matrice.o tspIOtourO.o
DEP = $(SRC:.c=.d)


OUTFILES= Voyageur 

all: $(OUTFILES)

-include $(DEP)

Voyageur: $(OBJ) main.o
	$(CC) $(OBJ) main.o -o $@ -lm

# main.o: main.c point.h projetAlgo.h matrice.h 

# projetAlgo.o: projetAlgo.c matrice.h point.h 

# point.o: point.c point.h

# matrice.o: matrice.c matrice.h point.h

#tspIOtourO.o: tspIOtourO.c point.h matrice.h tspIOtourO.h

%.o: %.c
	$(CC) -c $(CFLAGS) $*.c -o $*.o
	$(CC) -MM $(CFLAGS) $*.c > $*.d

.PHONY: clean valgrind check
valgrind:
       VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

check:
	$(CC) -c  $(CFLAGS) test_NN.c 
	$(CC) $(OBJ) test_NN.o -o test_NN -lm
	
	$(CC) -c  $(CFLAGS) test_BF.c 
	$(CC) $(OBJ) test_BF.o -o test_BF -lm
	
	$(CC) -c  $(CFLAGS) test_Prim.c 
	$(CC) $(OBJ) test_Prim.o -o test_Prim -lm
	   
clean:
	-rm -f $(OBJ) main.o $(DEP) *~ \#*\# $(OUTFILES) test_NN test_BF test_Prim
	

