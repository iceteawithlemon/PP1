#ifndef LDCDYNAM_C
#define LDCDYNAM_C

# include "point.h"
# include <stdbool.h>

typedef point point; //ou char, double, etc au lieu de 'int'
typedef struct cellule *cellule;
typedef struct liste *liste;

//primitives de création et délétion
liste creerListe();
void detruireListe(liste L);

//primitives d'accès	
bool estFinListe(liste L);
bool estDebutListe(liste L);
void debutListe(liste L);
void finListe(liste L);
bool listeVide(liste L);
void suivant(liste L);
void precedent(liste L);
point valeur(liste L);
cellule getCleListe(liste L);

//primitives de modification
bool estFinListe(liste L);
void insererApres(liste L, point x);
void insererEnTete(liste L, point x);
void supprimerApres(liste L);
void supprimerEnTete(liste L);
void setCleListe(liste L, cellule c);

//autre
void printList(liste L); //affiche le contenu d'un liste
bool appartient(liste L, point x);
void ajouter(liste E, point x);
void supprimer(liste E, point x);
void insererIci(liste E, point x);
liste populate(point t[], int len);


#endif