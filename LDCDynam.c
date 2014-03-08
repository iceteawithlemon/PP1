/* Listes doublement chaînées
   10/10/13 */

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>


typedef int car; //ou char, double, etc au lieu de 'int'
typedef struct cellule cellule;
typedef cellule *curseur;
typedef struct listeDC_car listeDC_car;

struct cellule
{
 	car valeurElement;
 	curseur pointeurPrecedent;
 	curseur pointeurSuivant;
};

struct listeDC_car
{
	curseur premier;
	curseur dernier;
	curseur cle;
};

//Primitives d'accès

bool estFinListe(listeDC_car L)
{
	return (L.cle==L.dernier);
}

bool estDebutListe(listeDC_car L)
{
	return (L.cle==L.premier);
}

void debutListe(listeDC_car *L) // *L car 'ref' dans le cours
{
	L->cle=L->premier;
}

void finListe(listeDC_car *L)
{
	L->cle=L->dernier;
}


bool listeVide(listeDC_car L) // L (sans *) car 'val' dans le cours
{
	return (L.premier==NULL);
}

void suivant(listeDC_car *L)
{
	if(!listeVide(*L) && !estFinListe(*L))
		L->cle=L->cle->pointeurSuivant;
}

void precedent(listeDC_car *L)
{
	if(!listeVide(*L) && !estDebutListe(*L))
		L->cle=L->cle->pointeurPrecedent;
}

car valeur(listeDC_car L)
{
	if (!listeVide(L))
		return L.cle->valeurElement; //j'utilise le 'if'/'else' et non un 'assert' car avec un assert cette fonction ne retourne rien, ce qui provoque un stackdump
	else
		return EXIT_FAILURE; //j'utilise exit_failure pour que ça marche n'importe le type de 'car', mais attention car il retourne "1" si car est un int, ce qui peut provoquer (et a provoqué) des confusions...
}

curseur getCleListe(listeDC_car L)
{
	return L.cle;
}

//Primitives de modification

void creer_liste(listeDC_car *L)
{
	//cellule *nouv = (cellule*)malloc(sizeof(cellule));
	L->premier=NULL;
	L->dernier=NULL;
	L->cle=L->premier;
}


//TD3 ex3.1

void insererEnTete(listeDC_car *L, car x)
{
	cellule *nouv = (cellule*)malloc(sizeof(cellule));
	if (!listeVide(*L)) //donc si la liste n'est pas vide
	{
		nouv->pointeurSuivant=L->premier; //
		L->premier->pointeurPrecedent=nouv;
	}
	else
	{
		L->dernier=nouv; //si la liste est vide alors la première cellule sera aussi la dernière
		nouv->pointeurSuivant= NULL;
		nouv->pointeurPrecedent=NULL;
	}
	nouv->valeurElement=x; //mais dans tous les cas on fait ceci
	L->premier=nouv;
}

void insererApres(listeDC_car *L, car x)
{
	if(!L->cle)
		insererEnTete(L, x);
	else
	{
		cellule *nouv = (cellule*)malloc(sizeof(cellule));
		if (L->cle->pointeurSuivant!=NULL)
		{
			nouv->pointeurSuivant=L->cle->pointeurSuivant;
			nouv->pointeurSuivant->pointeurPrecedent=nouv;
		}
		else
		{
			L->dernier=nouv;
			nouv->pointeurSuivant=NULL;
		} 
		nouv->valeurElement=x;
		L->cle->pointeurSuivant=nouv;
		nouv->pointeurPrecedent=L->cle;
	}
}


void supprimerApres(listeDC_car *L)
{
	if (L->cle->pointeurSuivant)
	{
		L->cle->pointeurSuivant=L->cle->pointeurSuivant->pointeurSuivant;
		L->cle->pointeurSuivant->pointeurPrecedent=L->cle;
	}
}

void supprimerEnTete(listeDC_car *L)
{
	if (L->cle==L->premier)
		suivant(L);
	if (L->cle->pointeurSuivant)
	{
		L->premier=L->premier->pointeurSuivant;
		L->premier->pointeurPrecedent=NULL;
	}
}
 
void detruireListe(listeDC_car *L)
{
	while (!listeVide(*L))
		supprimerEnTete(L);
}

void setCleListe(listeDC_car *L, curseur c)
{
	L->cle=c;
}

void printList(listeDC_car L)
{
	debutListe(&L);
	if(!listeVide(L))
	{
	while (!estFinListe(L))
	{
		printf("%d, ", L.cle->valeurElement);
		suivant(&L);
	}
	printf("%d.\n", L.cle->valeurElement);
	}
}

/*void check(listeDC_car L)
{
	printf("\nListe vide? %s\n", listeVide(L)? "yes": "no");
	printf("estDebutListe? %s\n", (L.premier==L.cle)? "yes": "no");
	printf("estFinListe? %s\n", estFinListe(L)? "yes": "no");
	if (!listeVide(L))
		printf("Valeur element = %d\n\n", valeur(L));
}*/

//TD3 ex3.2 (ensembles)

typedef listeDC_car ensemble;

int cardinalite(ensemble E)
{
	int i = 0;
	debutListe(&E);
	if(!listeVide(E))
	{
		while (!estFinListe(E))
		{
			i++;
			suivant(&E);
		}
		i++;
	}
	return i;
}

bool appartient(ensemble E, car x)
{
	debutListe(&E);
	while(!estFinListe(E) && valeur(E)!= x)
	{
		suivant(&E);
	}
	return valeur(E)==x;
}

void ajouter(ensemble *E, car x)
{
	if (!appartient(*E, x))
		insererApres(E, x);
}

void supprimer(ensemble *E, car x)
{
	curseur p = getCleListe(*E);
	while(!estFinListe(*E) && valeur(*E)!= x)
	{
		suivant(E);
	}
	if(valeur(*E)==x)
	{
		if(estDebutListe(*E))
			supprimerEnTete(E);
		else
			precedent(E);
			supprimerApres(E);
	}
	setCleListe(E, p);
}

void insererIci(ensemble *E, car x)
{
	if(estDebutListe(*E))
		insererEnTete(E, x);
	else
	{
		precedent(E);
		insererApres(E, x);
	}
}

ensemble convertir(listeDC_car L)
{
	debutListe(&L);
	ensemble E;
	creer_liste(&E);
	while(!estFinListe(L))
	{
		if (!listeVide(E))
		if(valeur(L)==valeur(E))
		{
			suivant(&L);
			debutListe(&E);
		}
		if(valeur(L)<valeur(E) || estFinListe(E) || listeVide(E))
		{
			if(!valeur(L)<valeur(E) && estFinListe(E) && !listeVide(E))
				insererApres(&E, valeur(L));
			else
				insererIci(&E, valeur(L));
			suivant(&L);
			debutListe(&E);
		}
		if(valeur(L)>valeur(E))
			suivant(&E);
	}
	debutListe(&E);
	return E;
}

ensemble reunion(ensemble E1, ensemble E2)
{
	ensemble E;
	creer_liste(&E);
	debutListe(&E1);
	debutListe(&E2);
	while(!estFinListe(E1))
	{
		insererApres(&E, valeur(E1));
		suivant(&E1);
	}
	while(!estFinListe(E2))
	{
		insererApres(&E, valeur(E2));
		suivant(&E2);
	}
	return convertir(E);
}


ensemble intersection(ensemble E1, ensemble E2)
{
	ensemble E;
	creer_liste(&E);
	debutListe(&E1);
	debutListe(&E2);
	while(!estFinListe(E1))
	{
		if (valeur(E1)==valeur(E2))
		{
			insererApres(&E, valeur(E1));
			suivant(&E2);
			suivant(&E1);
		}
		else
		{
			suivant(&E2);
		}
		if (estFinListe(E2))
		{
			debutListe(&E2);
			suivant(&E1);
		}
	}
	return convertir(E);
}

ensemble populate(car t[], int len)
{
	ensemble E;
	creer_liste(&E);
	debutListe(&E);
	for(int i=0; i<len; i++)
		insererApres(&E, t[i]);
	return E;
}


int main()
{
	listeDC_car L1;
	creer_liste(&L1);
	insererEnTete(&L1, 10);
	debutListe(&L1);
	insererApres(&L1, 2);
	insererApres(&L1, 3);
	insererApres(&L1, 4);
	insererApres(&L1, 2);
	insererApres(&L1, 5);
	ajouter(&L1, 1);
	ajouter(&L1, 6);
	insererApres(&L1, 2);
	insererEnTete(&L1, 6);
	ajouter(&L1, 7);
	supprimer(&L1, 7);
	printList(L1);
	printf("Cardinalité: %d\n", cardinalite(L1));
	printf("1 appartient à L1? %d\n", appartient(L1, 1)); 
	printf("7 appartient à L1? %d\n", appartient(L1, 7)); 
	ensemble E1;
	E1=convertir(L1);
	printList(E1);
	ensemble E2;
	creer_liste(&E2);
	car t[]= {1, 5, 7, 8, 6, 5, 6, 7, 2, 1, 10, 11, 11, 9};
	int len = (sizeof(t))/sizeof(t[0]);
	E2=populate(t, len);
	printList(E2);
	ensemble E3 = reunion(E1, E2);
	printList(E3);
	printf("\n");
	insererApres(&E1, 6);
	printList(E1);
	printList(E2);
	ensemble E4 = intersection(E1, E2);
	printList(E4);
	return 0;
}