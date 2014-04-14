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
    
    
    //Choix du parcour
    switch(choix){
        
    /*****************************************************************************************
     ****************************** NEAREAST NEIGHBOUR ***************************************
     *****************************************************************************************/
            
        case 1 :
            printf("Test Nearest Neighbour:\n");
 
            ListePoint = nearestNeighbour(m);
    
            //ON RECUPERE LE TABLEAU DE POINTS EN SORTIE
            matrice matriceOut = creerMatriceDesPoints(ListePoint, nbPoint);
    
            //AFFICHAGE DU PARCOURS
            afficherMatrice(matriceOut);
            //creerTOUR("Testfichier", matriceOut, ListePoint);

            printf("\nDistance totale: %d\n", overallDistanceVerbose(matriceOut, ListePoint));
        
            detruireMatrice(matriceOut);
            break;
         
    
    /*****************************************************************************************
     *********************************** PRIM ************************************************
     *****************************************************************************************/
        case 2 :
            printf("Test prim:\n");
            point *tabPrim = malloc(sizeof(point)*nbPoint);
    
            int dist = prim(m,tabPrim);
            
            //matrice matricePrimOut = creerMatriceDesPoints(tabPrim, nbPoint);
            afficherListeDesPoints(tabPrim, nbPoint);
        
            printf("\nDistance totale  prim : %d\n",dist);
            //detruireMatrice(matricePrimOut);
            free(tabPrim);
            break;
            
    /*****************************************************************************************
     *********************************** BRUTE FORCE *****************************************
     *****************************************************************************************/
        case 3:
            printf("Test brute force:\n");
            printf("(Attention: il prend qqs secondes)\n");
            ListePoint = bruteForce(m);

            printf("Points en sortie: \n");
            afficherListeDesPoints(ListePoint, nbPoint);
            printf("Overall distance: %d\n", overallDistanceVerbose(m, ListePoint));
            break;

    /*****************************************************************************************
     *********************************** BRANCH & BOUND **************************************
     *****************************************************************************************/
        case 4:
            printf("Test branch & bound:\n");
            ListePoint = branchBound(m);

            printf("Points en sortie: \n");
            afficherListeDesPoints(ListePoint, getDimensionMatrice(m));
            printf("Overall distance: %d\n", overallDistanceVerbose(m, ListePoint));
            break;
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

