#ifndef MATRICE_H
#define MATRICE_H

# include "point.h"
# include <stdio.h>

typedef struct Matrice *matrice;

matrice creerMatriceDesPoints(point liste[], int dimension);
matrice creerMatriceVide(int dimension);
void detruireMatrice(matrice m);

matrice cloneMatrice(matrice m);

int getIndicePoint(matrice m, point p);
point getPointIndice(matrice m, int indice);
float getDistanceIndice(matrice m, int ref1, int ref2);
float getDistancePoint(matrice m, point p1, point p2);

point *getTableauPointsMatrice(matrice m);

void setDistanceIndice(matrice m, int ref1, int ref2, float distance);
void setPointIndice(matrice m, int i, point p);

int getDimensionMatrice(matrice m);

void afficherMatrice(matrice m);

void markAsInfinite(matrice m, int i, int j);

int getLowerBoundInclude(matrice m, point from, point to);
int getLowerBoundExclude(matrice m, point from, point to);
int lowerBound(matrice m);


#endif