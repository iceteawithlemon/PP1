//
//  main.c
//  ProjetPP1
//
//  Created by Benjamin Saint-Sever on 28/02/2014.
//  Copyright (c) 2014 Benjamin Saint-Sever. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "projetAlgo.h"
#include "Liste.h"

#define nombreDePoints 4

int main(int argc, const char * argv[])
{
    
 
/***********************************************************
 *                     Phase de Test                       *
 **********************************************************/
  
    /*
    // creation du tableau pour test de la fonction apres
	point p1 = creerPoint(0,0);
    
    
	point p2 = creerPoint(1,6);
	point p3 = creerPoint(2,0);
	point p4 = creerPoint(3,0);
    int n = 4;
    
	point t[4]={p1,p2,p3,p4}; //tableau comprenant les points crees precedement
	
    /////////////////////////////////
    //TEST POINT
    int pointTestX = 0;
    int pointTestY = 0;
    pointTestX = getX(p2);
    pointTestY = getY(p2);
    printf("P2 X : %d  P2 Y : %d\n",pointTestX,pointTestY);
    //////////////////////////////////
    //TEST TABLEAU DE POINT
    int pointTesttab = 0;
    pointTesttab = getX(t[2]);
    printf("P3 X : %d \n",pointTesttab);
    //////////////////////////////////
    //TEST distanceEntreDeuxPoints
    printf("Distance entre P2 et P4\n");
    printf("%f\n",distanceEntreDeuxPoints(p2,p4));
    //////////////////////////////////
    


    int distance = 0;
    int indice =0;
    distance = ProchainPoint(t, indice, n);
    printf("Indice du prochain point %d\n",distance+1);
    
    indice++;
    point tableauRanger[4]={p1,p3,p2,p4};
    distance = ProchainPoint(tableauRanger,indice ,n);
    printf("Indice du prochain point %d\n",distance+1);
    
 */
    
    
/***********************************************************
 *                     Algorithme                          *
 **********************************************************/
    
    printf("Test");
    point p1 = creerPoint(0,0);
	point p2 = creerPoint(1,6);
	point p3 = creerPoint(2,0);
	point p4 = creerPoint(3,0);
    //Tableau comprenant les points
	point tab[nombreDePoints]={p1,p2,p3,p4};
    
    //Initialisation d'un liste chainée
    list liste = NULL;
    
    //Insertion du premier point dans la liste
    liste = ajouterEnTete(liste, p1);
    
    //Insertion des points dans la liste
    for(int i = 1; i<nombreDePoints;i++){
        liste = ajouterEnFin(liste, tab[i]);
    }

    
    //Tableau comprenant l'ordre de passage
    point ordreDePassage[nombreDePoints];
    
    //Point d'origine inséré dans le tableau
    ordreDePassage[0] = clone(p1);
    
    //On defini un point qui sera l'intermédiaire
    point pointActuel = clone(p1);
    
    //Indice du tableau d'ordre de passage
    int indice = 0;
    
    //Tant que l'on est pas à la fin de la liste
    while(!finListe(liste)){
        
        // On stocke le point le plus proche dans le point intermédiaire
        pointActuel = clone(PointLePlusProche(pointActuel, liste));
        
        // On supprime le point trouvé de la liste
        liste = supprimerElement(liste, pointActuel);
        
        // On passe à l'indice suivant
        indice++;
        
        // On implémente le point le plus proche du précedent dans le tableau
        ordreDePassage[indice] = clone(pointActuel);
    }
    indice++;
    // On ajoute le point de départ au tableau d'ordre de passage
    ordreDePassage[indice] = clone(p1);
    
    // On libere la mémoire de la liste
    effacerListe(liste);
    
    printf("Test2");
    //Affichage de l'ordre de passage
    for(int i =0;i<nombreDePoints;i++){
        afficherPoint(ordreDePassage[i]);
    }
    
    return 0;
}

