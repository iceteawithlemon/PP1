#include "point.h"
#include "Liste.h"
# include <stdlib.h>



point PointLePlusProche(point p,list liste){
    point pointTmp = creerPoint(0,0);
    double distance = 0;
    double tmp = 0;
    
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