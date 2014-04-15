#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "projetAlgo.h"
#include "matrice.h"
# include "tspIOtourO.h"

#define nombreDePoints 4

/**
 * \brief Fonction principale permettant de tester la fonction Brute force
 *
 * \return: EXIT_FAILURE si il y a un probleme, EXIT_SUCESS si tout ce passe bien
 */
int main()
{
   printf("Matrice d'entree depuis le fichier exemple10.tsp\n");
    //CREATION MATRICE DEPUIS EXEMPLE10.TSP
    matrice m = creerMatriceTSP("../test_cases/exemple10.tsp");
    
    //RECUPERATION DU NOMBRE DE POINTS
    int nbPoint = getDimensionMatrice(m);

    printf("Matrice en entrée :\n");
    afficherMatrice(m);
	
	printf("Test brute force:\n");
    printf("(Attention: il prend qqs secondes)\n");
    ListePoint = bruteForce(m);

    printf("Points en sortie: \n");
    afficherListeDesPoints(ListePoint, nbPoint);
    printf("Overall distance: %d\n", overallDistanceVerbose(m, ListePoint));

    return EXIT_SUCESS;
}

