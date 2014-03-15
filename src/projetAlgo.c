#include "point.h"
#include "Liste.h"
# include <stdlib.h>



point PointLePlusProche(point p,list liste){
    point pointTmp = creerPoint(0,0);
    float distance = 0;
    float tmp = 0;
    
    //Distance entre p et le prochain point de la liste
    distance = distanceEntreDeuxPoints(p,valeur(liste));
    
    //Stockage du point suceptible d'etre le plus proche
    pointTmp = clone(valeur(liste));
    
    //Copie de la liste afin d'avancer
    list listeTmp = liste;
    
    
    //Tant que l'on est pas à la fin de la liste
    while (!finListe(listeTmp)) {
        
        //On passe au prochain point de la liste
        listeTmp = suivant(listeTmp);
        
        //Distance entre p et le point d'après
        tmp = distanceEntreDeuxPoints(p,valeur(listeTmp));
        
        //Si le point d'après est plus près
        if (tmp<distance) {
            
            //On garde le point le plus proche
            pointTmp = clone(valeur(listeTmp));
            
            //On garde la distance entre p et le point le plus proche comme référence distance
            distance = tmp;
        }
    }
    return pointTmp;
}




point* nearestNeighbour(int nombreDePoints,point tab[],point ordreDePassage[]){
    //Initialisation d'une liste chainée
    list liste = NULL;
    
    //Insertion du premier point dans la liste (après le point d'origine)
    liste = ajouterEnTete(liste, tab[1]);
    
    //Insertion des points dans la liste
    for(int i = 2; i<nombreDePoints;i++){
        liste = ajouterEnFin(liste, tab[i]);
    }
    
    //Point d'origine inséré dans le tableau
    ordreDePassage[0] = clone(tab[0]);
    
    //On defini un point qui sera l'intermédiaire
    point pointActuel = clone(tab[0]);
    
    //Indice du tableau d'ordre de passage
    int indice = 1;
    
    //Tant que l'on est pas à la fin de la liste
    while(indice<nombreDePoints){
        
        // On stocke le point le plus proche dans le point intermédiaire
        pointActuel = clone(PointLePlusProche(pointActuel, liste));
        
        // On supprime le point trouvé de la liste
        liste = supprimerElement(liste, pointActuel);
        
        
        // On implémente le point le plus proche du précedent dans le tableau
        ordreDePassage[indice] = clone(pointActuel);
        
        // On passe à l'indice suivant
        indice++;
    }
    // On ajoute le point de départ au tableau d'ordre de passage
    ordreDePassage[indice] = clone(tab[0]);
    
    // On libere la mémoire de la liste
    effacerListe(liste);
    
    return ordreDePassage;
}

