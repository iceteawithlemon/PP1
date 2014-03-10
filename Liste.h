
#ifndef Liste_h
#define Liste_h

#include <stdbool.h>
#include "point.h"


typedef struct element element;
typedef element* list;

list ajouterEnTete(list liste, point pValeur);
list ajouterEnFin(list liste, point pValeur);
list rechercherElement(list liste, point pValeur);
void afficherListe(list liste);
list supprimerElement(list liste, point pValeur);
bool estVide(list liste);
point valeur(list liste);
list effacerListe(list liste);
bool finListe(list liste);
list suivant(list liste);

#endif
