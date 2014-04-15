#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "projetAlgo.h"
#include "matrice.h"
# include "tspIOtourO.h"

#define nombreDePoints 4
int main()
{
     printf("Matrice d'entree depuis le fichier exemple10.tsp\n");
    //CREATION MATRICE DEPUIS EXEMPLE10.TSP
    matrice m = creerMatriceTSP("../test_cases/exemple10.tsp");
    
    //RECUPERATION DU NOMBRE DE POINTS
    int nbPoint = getDimensionMatrice(m);

    printf("Matrice en entrée :\n");
    afficherMatrice(m);

   	printf("Test prim:\n");
            point *tabPrim = malloc(sizeof(point)*nbPoint);
    
            int dist = prim(m,tabPrim);
            
            //matrice matricePrimOut = creerMatriceDesPoints(tabPrim, nbPoint);
            afficherListeDesPoints(tabPrim, nbPoint);
        
            printf("\nDistance totale  prim : %d\n",dist);
            //detruireMatrice(matricePrimOut);
            free(tabPrim);
			
    return EXIT_SUCCESS;
}

