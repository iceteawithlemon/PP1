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
     point tab[nombreDePoints]={p4 ,p2, p1, p3};
     
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
    int nbPointIn = getDimensionMatrice(matriceIN);
    int nbPointOut = nbPointIn+1;
    
    //CREATION D'UN TABLEAU DE POINT
    point ordreDePassage[nbPointOut];
    
    //ON APPLIQUE L'ALGORITHME NEARESTNEIGHBOUR DEPUIS LA MATRICE D'ENTREE, DANS UN TABLEAU
    nearestNeighbour(matriceIN,ordreDePassage);
    
    //ON RECUPERE LE TABLEAU DE POINTS EN SORTIE
    matrice matriceOut = creerMatriceDesPoints(ordreDePassage, nbPointOut);
    
    //AFFICHAGE DU PARCOURS
    afficherMatrice(matriceOut);

    printf("\nDistance totale: %d\n", overallDistance(matriceIN, ordreDePassage));

    return 0;
}

