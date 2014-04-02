#ifndef TSPIOTOURO_H
#define TSPIOTOURO_H

# include <stdio.h>
# include "matrice.h"
# include "point.h"

extern matrice creerMatriceTSP(char *fnom);
extern void creerTSPMatrice(char *fnom, matrice m);
extern void creerTOUR(char *fnom, matrice m, point liste[]);

#endif