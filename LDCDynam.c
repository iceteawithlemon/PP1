/* Listes doublement chaînées
   10/10/13 */

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "point.h"

typedef struct cellule *cellule;
typedef struct listeDC_point *liste;

struct cellule
{
 	point valeurElement;
 	cellule pointeurPrecedent;
 	cellule pointeurSuivant;
};

struct listeDC_point
{
	cellule premier;
	cellule dernier;
	cellule cle;
};

//Primitives de création et de délétion

liste creerListe()
{
	liste L = malloc(sizeof(struct listeDC_point));
	L->premier=NULL;
	L->dernier=NULL;
	L->cle=L->premier;
	return L;
}

cellule creerCellule(point p)
{
	cellule c = malloc(sizeof(struct cellule));
	c->valeurElement = p;
	c->pointeurSuivant = c->pointeurPrecedent = NULL;
	return c;
}

void debutListe(liste L);
bool estFinListe(liste L);

void detruireListe(liste L)
{
	debutListe(L);
	cellule tmp;
	while(!estFinListe(L))
	{
		tmp = L->cle->pointeurSuivant;
		free(L->cle);
		L->cle = tmp;
	}
	free(L);
}

//Primitives d'accès

bool estFinListe(liste L)
{
	return (L->cle == L->dernier);
}

bool estDebutListe(liste L)
{
	return (L->cle == L->premier);
}

void debutListe(liste L)
{
	L->cle = L->premier;
}

void finListe(liste L)
{
	L->cle = L->dernier;
}


bool listeVide(liste L)
{
	return L->premier == NULL;
}

void suivant(liste L)
{
	if(!listeVide(L) && !estFinListe(L))
		L->cle = L->cle->pointeurSuivant;
}

void precedent(liste L)
{
	if(!listeVide(L) && !estDebutListe(L))
		L->cle = L->cle->pointeurPrecedent;
}

point valeur(liste L)
{
	return L->cle->valeurElement;
}

cellule getCleListe(liste L)
{
	return L->cle;
}


//Primitives de modification
void insererEnTete(liste L, point x)
{
	cellule nouv = creerCellule(x);
	if (!listeVide(L)) //donc si la liste n'est pas vide
	{
		nouv->pointeurSuivant = L->premier; 
		L->premier->pointeurPrecedent = nouv;
	}
	else
	{
		L->dernier = nouv; //si la liste est vide alors la première cellule sera aussi la dernière
		nouv->pointeurSuivant = NULL;
		nouv->pointeurPrecedent = NULL;
	}
	nouv->valeurElement = x; 
	L->premier = nouv;
}

void insererApres(liste L, point x)
{
	cellule tmp = creerCellule(x);
	tmp->valeurElement = x;
	if(listeVide(L))
	{
		insererEnTete(L, x);
	}
	else
	{
		if(!estFinListe(L))
		{
			L->cle->pointeurSuivant->pointeurPrecedent = tmp;
			tmp->pointeurSuivant = L->cle->pointeurSuivant;
		}
		else
			tmp->pointeurSuivant = NULL;
		tmp->pointeurPrecedent = L->cle;
	}
}


void supprimerApres(liste L)
{
	if (L->cle->pointeurSuivant && L->cle->pointeurSuivant->pointeurSuivant)
	{
		cellule tmp = L->cle;
		L->cle->pointeurSuivant = L->cle->pointeurSuivant->pointeurSuivant;
		L->cle->pointeurSuivant->pointeurPrecedent = L->cle;
		free(tmp);
	}
}

void supprimerEnTete(liste L)
{
	cellule tmp = L->premier;
	if (L->cle == L->premier)
		suivant(L);

	if (L->cle->pointeurSuivant)
	{
		L->premier=L->premier->pointeurSuivant;
		L->premier->pointeurPrecedent=NULL;
	}
	free(tmp);
}
 

void setCleListe(liste L, cellule c)
{
	L->cle = c;
}

void printList(liste L)
{
	cellule tmp = L->cle;
	debutListe(L);
	while(!estFinListe(L))
	{
		afficherPoint(L->cle->valeurElement);
		suivant(L);
	}
	setCleListe(L, tmp);
}




bool appartient(liste E, point x)
{
	debutListe(E);
	while(!estFinListe(E) && valeur(E)!= x)
	{
		suivant(E);
	}
	return valeur(E) == x;
}

void ajouter(liste E, point x)
{
	if (!appartient(E, x))
		insererApres(E, x);
}

void supprimer(liste E, point x)
{
	cellule p = getCleListe(E);
	while(!estFinListe(E) && valeur(E)!= x)
	{
		suivant(E);
	}
	if(valeur(E)==x)
	{
		if(estDebutListe(E))
		{
			supprimerEnTete(E);
		}
		else
		{
			precedent(E);
			supprimerApres(E);
		}
	}
	setCleListe(E, p);
}

void insererIci(liste E, point x)
{
	if(estDebutListe(E))
		insererEnTete(E, x);
	else
	{
		precedent(E);
		insererApres(E, x);
	}
}

/*liste convertir(liste L)
{
	debutListe(L);
	liste E;
	creerListe(&E);
	while(!estFinListe(L))
	{
		if (!listeVide(E))
		if(valeur(L)==valeur(E))
		{
			suivant(L);
			debutListe(E);
		}
		if(valeur(L)<valeur(E) || estFinListe(E) || listeVide(E))
		{
			if(!valeur(L)<valeur(E) && estFinListe(E) && !listeVide(E))
				insererApres(E, valeur(L));
			else
				insererIci(E, valeur(L));
			suivant(L);
			debutListe(E);
		}
		if(valeur(L)>valeur(E))
			suivant(E);
	}
	debutListe(&E);
	return E;
}*/



liste populate(point t[], int len)
{
	liste E = creerListe();
	debutListe(E);
	cellule tmp = malloc(sizeof(struct cellule));
	tmp->valeurElement = t[0];
	E->cle = E->premier = E->dernier = tmp;
	for(int i = 1; i < len; i++)
		insererApres(E, t[i]);
	return E;
}
