#ifndef ProjetPP1_projetAlgo_h
#define ProjetPP1_projetAlgo_h

#include "matrice.h"

int PointLePlusProche(int indicePointActuel,matrice m);
point *nearestNeighbour(matrice m);
int overallDistance(matrice m, point *points);
int overallDistanceVerbose(matrice m, point *points);
point *bruteForce(matrice m);
void copyList(point *pIn, point *pOut, int len);
void copyListIndice(point *pIn, point *pOut, int start, int end);
point *branchBound(matrice m);
int prim(matrice m, point* TabVisite);


#endif
