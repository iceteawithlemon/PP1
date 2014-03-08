#include "point.h"
#include "Liste.h"


point PointLePlusProche(point p,list liste){
    point pointTmp = creerPoint(0,0);
    double distance = 0;
    double tmp = 0;
    distance = distanceEntreDeuxPoints(p,valeur(liste));
    
    while (!finListe(liste)) {
        tmp = distanceEntreDeuxPoints(p,valeur(liste));
        if (tmp<distance) {
            pointTmp = valeur(liste);
        }
    }
    return pointTmp;
}