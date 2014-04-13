#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "projetAlgo.h"
#include "matrice.h"
# include "tspIOtourO.h"

int main()
{
    printf("Matrice d'entree depuis le fichier exemple10.tsp\n");
    //CREATION MATRICE DEPUIS EXEMPLE10.TSP
    matrice m = creerMatriceTSP("../test_cases/exemple10.tsp");
    
    //AFFICHAGE MATRICE
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
    
    
    printf("\n Lancement du test Nearest Neighbour\n");
    //AFFICHAGE DU PARCOURS
    afficherMatrice(matriceOut);
    

    printf("\nDistance totale: %d\n", overallDistance(m, ordreDePassage));
    printf("Distance fausse ! a modifier!");

    return 0;
}

