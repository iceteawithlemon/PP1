#ifndef ARBRESPLANAIRES_H
#define ARBRESPLANAIRES_H

# include "point.h"

typedef struct cellule *cellule;
typedef cellule sommet;
struct cellule
{
	point info;
	sommet premierFils;
	sommet frere;
	sommet pere;
};

point getValeur(sommet s);
sommet premierFils(sommet s);
sommet frere(sommet s);
sommet pere(sommet s);

sommet creerArbrePlanaire(point racine);
void ajouterFils(sommet s, point x);
void supprimerSommet(sommet s);
void detruireArbrePlanaire(sommet s);

void afficherArbrePlanaire(sommet s, int mode);
void parcoursHierarchique(sommet A, sommet tab[], int i);

#endif