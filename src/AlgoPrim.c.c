#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "projetAlgo.h"
#include "matrice.h"

void prim(matrice m){

/* prend point au hasard(A)
on calcul toutes les distance avec les autres points
on prend le chemin le plus court (B)
on refait la meme chose avec le point (B) 
*/

int nombreDePoints = getDimensionMatrice(m);

int alea = rand()%getDimensionMatrice; // g�n�ration d'un nombre al�atoire pour le choix du premier point

ordreDePassage[0] = clone(getPointIndice(m,alea)); //insertion du point d'origine
markVisited(getPointIndice(m, alea)); // marquage du point visit�

  //On defini un point qui sera l'interm�diaire
int indicePointActuel = alea;
    
    //Indice du tableau d'ordre de passage
int indice = 1;

//Tant que l'on est pas � la fin de la matrice
    while(indice<=nombreDePoints-1){
        
        indicePointActuel = PointLePlusProche(indicePointActuel,m);
        
        //Le point le plus proche du pointActuel est ins�r�
        ordreDePassage[indice] = clone(getPointIndice(m, indicePointActuel));
        
        // On passe � l'indice suivant
        indice++;
    }
    
    //On retourne au point d'origine
    ordreDePassage[indice] = clone(ordreDePassage[0]);
    
}
    
