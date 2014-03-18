#include "point.h"
#include "Liste.h"
#include <stdlib.h>
#include "matrice.h"

//Version tableau matrice qui renvoi l'indice du point le plus proche
int PointLePlusProche(int indicePointActuel,matrice m){
    
    float distance = 0;
    float tmp = 0;
    int TailleTab = getDimensionMatrice(m);
    
    int indice = 0;
    
    while(getPointisVisited(m, indice)){
        indice++;
    }
    
    
    //Distance entre le point actuel et le prochain point de la liste
    distance = getDistanceIndice(m,indicePointActuel, indice);
    
    //Sauvegarde de l'indice du point
    int indicePoint = indice;
    
    //Tant que l'on est pas à la fin du tableau
    while (indice != TailleTab-1) {
        
        //On passe au prochain point
        indice++;
        
        if(!getPointisVisited(m, indice)){
            
            //Distance entre le point actuel et le point d'après
            tmp = getDistanceIndice(m,indicePointActuel, indice);
            
            //Si le point d'après est plus près
            if (tmp<distance) {
                
                //On sauvegarde l'indice du point le plus proche
                indicePoint = indice;
                
                //On garde la distance entre p et le point le plus proche comme référence distance
                distance = tmp;
            }
        }
    }
    setMatricePointMarkVisited(m, indicePoint);
    return indicePoint;
}

matrice nearestNeighbour(matrice m,point tab[],point ordreDePassage[]){
    
    int nombreDePoints = getDimensionMatrice(m);
    point tabPoint[nombreDePoints];
    
    //Creation d'une matrice de sortie
    matrice mOut = creerMatriceDesPoints(tabPoint,nombreDePoints+1);
    
    
    //Point d'origine inséré dans la nouvelle matrice
    setMatricePoint(mOut,clone(getPointIndice(m,0)),0);
    setMatricePointMarkVisited(m,0);
    
    //On defini un point qui sera l'intermédiaire
    int indicePointActuel = 0;
    
    //Indice du tableau d'ordre de passage
    int indice = 1;
    
    //Tant que l'on est pas à la fin de la matrice
    while(indice<=nombreDePoints-1){
        
        indicePointActuel = PointLePlusProche(indicePointActuel,m);
        
        // On implémente le point le plus proche du précedent dans la matrice de sortie
        setMatricePoint(mOut,getPointIndice(m,indicePointActuel),indice);
        
        // On passe à l'indice suivant
        indice++;
    }
    
    // On ajoute le point de départ au tableau d'ordre de passage
    setMatricePoint(mOut,clone(getPointIndice(m,0)),indice);
    
    return mOut;
}

