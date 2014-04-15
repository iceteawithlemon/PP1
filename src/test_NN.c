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
    
    //RECUPERATION DU NOMBRE DE POINTS
    int nbPoint = getDimensionMatrice(m);

    printf("Matrice en entrée :\n");
    afficherMatrice(m);

    point* ListePoint = NULL;
    
	ListePoint = nearestNeighbour(m);
    
    //ON RECUPERE LE TABLEAU DE POINTS EN SORTIE
    matrice matriceOut = creerMatriceDesPoints(ListePoint, nbPoint);
    
    //AFFICHAGE DU PARCOURS
    afficherMatrice(matriceOut);
    
	//creerTOUR("Testfichier", matriceOut, ListePoint);

    printf("\nDistance totale: %d\n", overallDistanceVerbose(matriceOut, ListePoint));
        
    detruireMatrice(matriceOut);

    return EXIT_SUCCESS;
}

