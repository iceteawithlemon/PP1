#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "projetAlgo.h"
#include "matrice.h"
#include "tspIOtourO.h"

void erreurArguments();


/// \file
/// \brief Point d'entrée de l'application

/// \mainpage
///
/// Cette application a pour vocation de calculer des solutions au problème du voyageur de commerce

/**
 * \brief Fonction principale permettant à l'utilisateur de choisir une solution de parcours depuis un fichier tsp
 *
 * \param argc contient le nombre d'argument passé en parametre
 * \param argv contient les arguments de l'appel sous forme de chaine de caractere
 *
 * \return: EXIT_FAILURE si il y a un probleme, EXIT_SUCESS si tout ce passe bien
 */

int main(int argc, char** argv)
{
    
    if(argc !=3){
        printf("Nombre d'arguments incorrect :\n");
        erreurArguments();
        return 0;
    }
    
    //char * Directory = "../test_cases/exemple10.tsp";
    char * Directory = argv[1];
    int choix = atoi(argv[2]);
    if(choix > 4 || choix < 1){
        perror("Argument incorrect :\n");
        erreurArguments();
        return EXIT_FAILURE;
    }
    
    /*****************************************************************************************
     ****************************** INITIALISATION MATRICE ***********************************
     *****************************************************************************************/
    
    //AFFICHAGE MATRICE
    matrice m = creerMatriceTSP(Directory);
    
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
            printf("Nearest Neighbour:\n");
 
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
            printf("Prim:\n");
    
            ListePoint = prim(m);
            
            printf("Points en sortie: \n");
            afficherListeDesPoints(ListePoint, nbPoint);
            
            matrice matricePrimOut = creerMatriceDesPoints(ListePoint, nbPoint);
        
            printf("\nDistance totale  prim : %d\n",overallDistanceVerbose(matricePrimOut, ListePoint));
            
            detruireMatrice(matricePrimOut);
            break;
            
    /*****************************************************************************************
     *********************************** BRUTE FORCE *****************************************
     *****************************************************************************************/
        case 3:
            printf("Brute force:\n");
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
            printf("Branch & bound:\n");
            ListePoint = branchBound(m);

            printf("Points en sortie: \n");
            afficherListeDesPoints(ListePoint, nbPoint);
            printf("Overall distance: %d\n", overallDistanceVerbose(m, ListePoint));
            break;
    }
    
    /*****************************************************************************************
     ***************************** LIBERATION DE LA MEMOIRE **********************************
     *****************************************************************************************/

    detruireMatrice(m);
    for(int i=0;i<nbPoint;i++){
        free(ListePoint[i]);
    }
    free(ListePoint);
    
    return EXIT_SUCCESS;
}

void erreurArguments(){
    printf("Premier parametre : Fichier tsp\nDeuxieme parametre selectionné le parcours:\n");
    printf("1 - Nearest Neighbour\n");
    printf("2 - Prim\n");
    printf("3 - Brute Force\n");
    printf("4 - BRANCH & BOUND\n");
}

