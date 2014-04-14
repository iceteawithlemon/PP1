#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "projetAlgo.h"
#include "matrice.h"
#include "tspIOtourO.h"



int main(int argc, char** argv)
{
    
    if(argc !=2){
        printf("Nombre d'arguments incorrect :\n");
        printf("1 - Nearest Neighbour\n");
        printf("2 - Prim\n");
        printf("3 - Brute Force\n");
        printf("4 - BRANCH & BOUND\n");
        
        return 0;
    }
    int choix = atoi(argv[1]);
    
    /*****************************************************************************************
     ****************************** INITIALISATION MATRICE ***********************************
     *****************************************************************************************/
    
    //AFFICHAGE MATRICE
    matrice m = creerMatriceTSP("../test_cases/exemple10.tsp");

    afficherMatrice(m);
     
    //RECUPERATION DU NOMBRE DE POINTS
    int nbPoint = getDimensionMatrice(m);

    
    
    /*****************************************************************************************
     ****************************** NEAREAST NEIGHBOUR ***************************************
     *****************************************************************************************/
    
    if(choix == 1 ) {
            
        
    printf("Test Nearest Neighbour:\n");
    //CREATION D'UN TABLEAU DE POINT
    point ordreDePassage[nbPoint];
    
    //ON APPLIQUE L'ALGORITHME NEARESTNEIGHBOUR DEPUIS LA MATRICE D'ENTREE, DANS UN TABLEAU
    nearestNeighbour(m,ordreDePassage);
    
    //ON RECUPERE LE TABLEAU DE POINTS EN SORTIE
    matrice matriceOut = creerMatriceDesPoints(ordreDePassage, nbPoint);
    
    //AFFICHAGE DU PARCOURS
    afficherMatrice(matriceOut);

    printf("\nDistance totale: %d\n", overallDistanceVerbose(matriceOut, ordreDePassage));
        
    detruireMatrice(matriceOut);
        
    }
    
    
    /*****************************************************************************************
     *********************************** PRIM ************************************************
     *****************************************************************************************/
    
    if(choix == 2) {
    printf("Test prim:\n");
    point tabPrim[nbPoint];
    int dist = prim(m,tabPrim);
    matrice matricePrimOut = creerMatriceDesPoints(tabPrim, nbPoint);
    afficherListeDesPoints(tabPrim, nbPoint);
    
    printf("\nDistance totale  prim : %d\n",dist);
        
    detruireMatrice(matricePrimOut);
    }
    
    
    /*****************************************************************************************
     *********************************** BRUTE FORCE *****************************************
     *****************************************************************************************/
    
    if(choix == 3) {
    printf("Test brute force:\n");
    

    printf("Points en entrée: \n");
    afficherListeDesPoints(getTableauPointsMatrice(m), getDimensionMatrice(m));
    
    printf("(Attention: il prend qqs secondes)\n");
    point *tabTest = bruteForce(m);

    printf("Points en sortie: \n");
    afficherListeDesPoints(tabTest, getDimensionMatrice(m));
    printf("Overall distance: %d\n", overallDistanceVerbose(m, tabTest));

    free(tabTest);
    }
    
    
    /*****************************************************************************************
     *********************************** BRANCH & BOUND **************************************
     *****************************************************************************************/
    
    if(choix == 4) {
    printf("Test branch & bound:\n");

    printf("Points en entrée: \n");
    afficherListeDesPoints(getTableauPointsMatrice(m), getDimensionMatrice(m));

    point *tabTestOut = branchBound(m);

    printf("Points en sortie: \n");
    afficherListeDesPoints(tabTestOut, getDimensionMatrice(m));
    printf("Overall distance: %d\n", overallDistanceVerbose(m, tabTestOut));

    free(tabTestOut);
    }
    
    
    /*****************************************************************************************
     ***************************** LIBERATION DE LA MEMOIRE **********************************
     *****************************************************************************************/

    detruireMatrice(m);
    return EXIT_SUCCESS;

    return 0;
}

