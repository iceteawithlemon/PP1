#ifndef MATRICE_H
#define MATRICE_H

# include "point.h"

typedef struct Matrice *matrice;

matrice creerMatriceDesPoints(point liste[], int dimension);
matrice creerMatriceVide(int dimension);
void detruireMatrice(matrice m);

int getIndicePoint(matrice m, point p);
point getPointIndice(matrice m, int indice);
float getDistanceIndice(matrice m, int ref1, int ref2);
float getDistancePoint(matrice m, point p1, point p2);

void afficherMatrice(matrice m);

matrice creerMatriceTSP(char *fnom);

void creerTSPMatrice(char *fnom, matrice m);
void creerTOUR(char *fnom, matrice m, point liste[]);


#endif