#Makefile


CC = gcc
CFLAGS = -c -std=c99 -g -W -Wall 
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
INCS = 
DEP = $(SRC:.c=.d)
#OBJ= main.o  projetAlgo.o point.o matrice.o 



OUTFILES= testN

all: $(OUTFILES)

-include $(DEP)

testN: $(OBJ)
	$(CC) $(OBJ) -o $@ -lm

# main.o: main.c point.h projetAlgo.h matrice.h 

# projetAlgo.o: projetAlgo.c matrice.h point.h 

# point.o: point.c point.h

# matrice.o: matrice.c matrice.h point.h

%.o: %.c
	$(CC) -c $(CFLAGS) $*.c -o $*.o
	$(CC) -MM $(CFLAGS) $*.c > $*.d

.PHONY: clean
valgrind:
       VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)
clean:
	-rm -f $(OBJ) $(DEP) *~ \#*\# $(OUTFILES)
