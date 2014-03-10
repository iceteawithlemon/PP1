#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "projetAlgo.h"
#include "Liste.h"

#define nombreDePoints 4
int main(int argc, const char * argv[])
{

    //Creation de Points (a remplacer par une lecture de matrice)
    point p1 = creerPoint(0,0);
	point p2 = creerPoint(1,6);
	point p3 = creerPoint(2,0);
	point p4 = creerPoint(3,0);
    
    printf("Points en entrée : \n");
    for(int i =0;i<nombreDePoints+1;i++){
        afficherPoint(ordreDePassage[i]);
    }
    
    //Tableau comprenant les points
	point tab[nombreDePoints]={p1,p2,p3,p4};
    
   
    //Creation d'un tableau qui contiendra l'ordre de passage le plus court
    point ordreDePassage[nombreDePoints+1] ;
    
    //Appel à la fonction nearestNeighbour qui calcule le chemin le plus court
    nearestNeighbour(nombreDePoints,tab,ordreDePassage);
    
    
    printf("Points en sortie :  \n");
    //Affichage de l'ordre de passage
    for(int i =0;i<nombreDePoints+1;i++){
        afficherPoint(ordreDePassage[i]);
    }
    
    return 0;
}

