#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "projetAlgo.h"
#include "matrice.h"
#include "tspIOtourO.h"

void erreurArguments();

int main(int argc, char** argv)
{
    
    if(argc !=2){
        printf("Nombre d'arguments incorrect :\n");
        erreurArguments();
        return 0;
    }
    int choix = atoi(argv[1]);
    
    if(choix > 4 || choix < 1){
        perror("Argument incorrect :\n");
        erreurArguments();
        return EXIT_FAILURE;
    }
    
    /*****************************************************************************************
     ****************************** INITIALISATION MATRICE ***********************************
     *****************************************************************************************/
    
    //AFFICHAGE MATRICE
    matrice m = creerMatriceTSP("../test_cases/exemple10.tsp");
    
    //RECUPERATION DU NOMBRE DE POINTS
    int nbPoint = getDimensionMatrice(m);

    printf("Matrice en entrée :\n");
    afficherMatrice(m);

    point* ListePoint = NULL;
    /*****************************************************************************************
     ****************************** NEAREAST NEIGHBOUR ***************************************
     *****************************************************************************************/
    
    if(choix == 1 ) {
            
        
    printf("Test Nearest Neighbour:\n");
 
    //ON APPLIQUE L'ALGORITHME NEAREST NEIGHBOUR DEPUIS LA MATRICE D'ENTREE, DANS UN TABLEAU
    ListePoint = nearestNeighbour(m);
    
    //ON RECUPERE LE TABLEAU DE POINTS EN SORTIE
    matrice matriceOut = creerMatriceDesPoints(ListePoint, nbPoint);
    
    //AFFICHAGE DU PARCOURS
    afficherMatrice(matriceOut);

    printf("\nDistance totale: %d\n", overallDistanceVerbose(matriceOut, ListePoint));
        
    detruireMatrice(matriceOut);
        
    }
    
    
    /*****************************************************************************************
     *********************************** PRIM ************************************************
     *****************************************************************************************/
    
    if(choix == 2) {
    printf("Test prim:\n");
    point tabPrim[nbPoint];
    int dist = prim(m,tabPrim);
    //matrice matricePrimOut = creerMatriceDesPoints(tabPrim, nbPoint);
    afficherListeDesPoints(tabPrim, nbPoint);
    
    printf("\nDistance totale  prim : %d\n",dist);
    //detruireMatrice(matricePrimOut);
    }
    
    
    /*****************************************************************************************
     *********************************** BRUTE FORCE *****************************************
     *****************************************************************************************/
    
    if(choix == 3) {
        
    printf("Test brute force:\n");
    printf("(Attention: il prend qqs secondes)\n");
    ListePoint = bruteForce(m);

    printf("Points en sortie: \n");
    afficherListeDesPoints(ListePoint, getDimensionMatrice(m));
    printf("Overall distance: %d\n", overallDistanceVerbose(m, ListePoint));

    }
    
    
    /*****************************************************************************************
     *********************************** BRANCH & BOUND **************************************
     *****************************************************************************************/
    
    if(choix == 4) {
    printf("Test branch & bound:\n");
    ListePoint = branchBound(m);

    printf("Points en sortie: \n");
    afficherListeDesPoints(ListePoint, getDimensionMatrice(m));
    printf("Overall distance: %d\n", overallDistanceVerbose(m, ListePoint));

    }
    

    
    /*****************************************************************************************
     ***************************** LIBERATION DE LA MEMOIRE **********************************
     *****************************************************************************************/

    detruireMatrice(m);
    free(ListePoint);
    
    return EXIT_SUCCESS;
}

void erreurArguments(){
    printf("1 - Nearest Neighbour\n");
    printf("2 - Prim\n");
    printf("3 - Brute Force\n");
    printf("4 - BRANCH & BOUND\n");
}

