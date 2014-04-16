#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "projetAlgo.h"
#include "matrice.h"
# include "tspIOtourO.h"

/**
 * \brief Fonction principale permettant de tester la fonction Prim
 *
 * \return: EXIT_FAILURE si il y a un probleme, EXIT_SUCESS si tout ce passe bien
 */
int main()
{
    printf("------------------------------------------------------------------\n");
    printf("|                         Test Prim                              |\n");
    printf("------------------------------------------------------------------\n");
    printf("Matrice d'entree depuis le fichier exemple10.tsp\n");
    //CREATION MATRICE DEPUIS EXEMPLE10.TSP
    matrice m = creerMatriceTSP("../test_cases/exemple10.tsp");
    
    //RECUPERATION DU NOMBRE DE POINTS
    int nbPoint = getDimensionMatrice(m);

    printf("Matrice en entree:\n\n");
    afficherMatrice(m);

    point* ListePoint = NULL;
    
    ListePoint = prim(m);
    
    //ON RECUPERE LE TABLEAU DE POINTS EN SORTIE
    matrice matricePrimOut = creerMatriceDesPoints(ListePoint, nbPoint);
    
    
    printf("------------------------------------------------------------------\n");
    printf("Matrice en sortie :\n");
    //AFFICHAGE DU PARCOURS
    afficherMatrice(matricePrimOut);
    
    printf("------------------------------------------------------------------\n");
    int distance = overallDistanceVerbose(matricePrimOut, ListePoint);
    printf("------------------------------------------------------------------\n");
    
    printf("\nDistance totale  prim : %d\n",distance);
    printf("Valeur attendue: 50 \n");
    if(distance == 50)
        printf("Test Reussi\n");
    else
        printf("Echec du test\n");
    
    
    detruireMatrice(matricePrimOut);
    for(int i = 0;i<nbPoint;i++)
        free(ListePoint[i]);
    
    free(ListePoint);
			
    return EXIT_SUCCESS;
}