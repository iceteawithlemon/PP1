#include <stdio.h>
#include <stdlib.h>

#include <point.h>
#include <projetAlgo.h>
#include <matrice.h>

#define nombreDePoints 4
int main(int argc, const char * argv[])
{
    
    //Creation de Points (a remplacer par une lecture de matrice)
     point p1 = creerPoint(0,0);
     point p2 = creerPoint(1,6);
     point p3 = creerPoint(2,0);
     point p4 = creerPoint(3,0);
     
     
     
     //Tableau comprenant les points
     point tab[nombreDePoints]={p1,p2,p3,p4};
     
     printf("Points en entrée : \n");
     for(int i =0;i<nombreDePoints;i++){
     afficherPoint(tab[i]);
     }
     

    
    char *fileN = "test_cases/exemple10.tsp";
    
    matrice matriceIN;
    //Lecture du fichier
    matriceIN = creerMatriceTSP(fileN); //ne pas utiliser lecture_TSP, mais plutôt son wrapper creerMatriceTSP
    
    afficherMatrice(matriceIN);
    
    int nbPoint = getDimensionMatrice(matriceIN);
    point ordreDePassage[nbPoint+1];
    nearestNeighbour(matriceIN,ordreDePassage);

    return 0;
}

