#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "projetAlgo.h"
#include "matrice.h"
# include "tspIOtourO.h"

#define nombreDePoints 4
int main()
{
    
    //Creation de Points (a remplacer par une lecture de matrice)
     point p1 = creerPoint(0,0);
     point p2 = creerPoint(1,1);
     point p3 = creerPoint(2,2);
     point p4 = creerPoint(3,3);
     
    
     //Tableau comprenant les points
     point tab[nombreDePoints]={p4 ,p2, p1,p3};
     
     printf("Points en entrée : \n");
     for(int i =0;i<nombreDePoints;i++)
        afficherPoint(tab[i]);
     
    
    
    //CREATION MATRICE ENTREE
    matrice matriceIN;
    matriceIN = creerMatriceDesPoints(tab, nombreDePoints);
    
    //AFFICHAGE MATRICE
    matrice m = creerMatriceTSP("../test_cases/exemple10.tsp");

    afficherMatrice(m);
     
    //RECUPERATION DU NOMBRE DE POINTS
    int nbPointIn = getDimensionMatrice(m);
    int nbPointOut = nbPointIn+1;
    
    
    //CREATION D'UN TABLEAU DE POINT
    point ordreDePassage[nbPointOut];
    
    //ON APPLIQUE L'ALGORITHME NEARESTNEIGHBOUR DEPUIS LA MATRICE D'ENTREE, DANS UN TABLEAU
    nearestNeighbour(m,ordreDePassage);
    
    //ON RECUPERE LE TABLEAU DE POINTS EN SORTIE
    matrice matriceOut = creerMatriceDesPoints(ordreDePassage, nbPointOut);
    
    //AFFICHAGE DU PARCOURS
    afficherMatrice(matriceOut);

    printf("\nDistance totale: %d\n", overallDistance(matriceOut, ordreDePassage));

    
    
    
    //PRIM -> Segmentation Fault :(
    printf("Test prim:\n");
    point tabPrim[nbPointOut];
    int dist = prim(m,tabPrim);
    matrice matricePrimOut = creerMatriceDesPoints(tabPrim, nbPointOut);
    afficherListeDesPoints(tabPrim, nbPointOut);
    
    printf("\nDistance totale REELLE !!! prim : %d\n",dist);
    printf("\nDistance totale: %d\n", overallDistance(matricePrimOut, tabPrim));
    
    
    
   
    //BRUTE FORCE
    printf("Test brute force:\n");
    
    point tabTest[getDimensionMatrice(m)];


    copyList(getTableauPointsMatrice(m), tabTest, getDimensionMatrice(m));
    printf("Points en entrée: \n");
    afficherListeDesPoints(tabTest, getDimensionMatrice(m));
    
    printf("(Attention: il prend qqs secondes)\n");
    bruteForce(m, tabTest);

    printf("Points en sortie: \n");
    afficherListeDesPoints(tabTest, getDimensionMatrice(m));
    printf("Overall distance: %d\n", overallDistance(m, tabTest));



    //BRANCH & BOUND
    printf("Test branch & bound:\n");

    printf("Points en entrée: \n");
    afficherListeDesPoints(getTableauPointsMatrice(m), getDimensionMatrice(m));

    point *tabTestOut = branchBound(m);

    printf("Points en sortie: \n");
    afficherListeDesPoints(tabTestOut, getDimensionMatrice(m));
    printf("Overall distance: %d\n", overallDistance(m, tabTestOut));
    

    return 0;
}

