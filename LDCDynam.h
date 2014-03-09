#ifndef LDCDYNAM_C
#define LDCDYNAM_C

# include <stdbool.h>

typedef int car;
typedef struct cellule cellule;
typedef cellule *curseur;
typedef struct listeDC_car listeDC_car;

//primitives d'accès	
bool estFinListe(listeDC_car L);
bool estDebutListe(listeDC_car L);
void debutListe(listeDC_car *L);
void finListe(listeDC_car *L);
bool listeVide(listeDC_car L);
void suivant(listeDC_car *L);
void precedent(listeDC_car *L);
car valeur(listeDC_car L);
curseur getCleListe(listeDC_car L);

//primitives de modification
void creer_liste(listeDC_car *L)
bool estFinListe(listeDC_car L);
void insererApres(listeDC_car *L, car x);
void insererEnTete(listeDC_car *L, car x);
void supprimerApres(listeDC_car *L);
void supprimerEnTete(listeDC_car *L);
void detruireListe(listeDC_car *L);
void setCleListe(listeDC_car *L, curseur c);

//autre
void printList(listeDC_car L); //affiche le contenu d'un liste

#endif