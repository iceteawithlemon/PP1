#ifndef ProjetPP1_projetAlgo_h
#define ProjetPP1_projetAlgo_h

#include "matrice.h"

int PointLePlusProche(int indicePointActuel,matrice m);
void nearestNeighbour(matrice m,point ordreDePassage[]);
int overallDistance(matrice m, point *points);
void bruteForce(matrice m, point *pList);
void copyList(point *pIn, point *pOut, int len);
void copyListIndice(point *pIn, point *pOut, int start, int end);
void branchBound(matrice m, point *pList, int pas);

#endif
