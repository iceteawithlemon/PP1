// Implementation des arbres planaires
// 11/11/13

# include <stdio.h>
# include <assert.h>
# include <stdlib.h>
# include <stdbool.h>
# include "point.h"



typedef struct cellule *cellule;
typedef cellule sommet;
struct cellule
{
	point info;
	sommet premierFils;
	sommet frere;
	sommet pere;
	point racine;
};

// accès 

point getValeur(sommet s)
{
	return s->info;
}

sommet premierFils(sommet s)
{
	return s->premierFils;
}

sommet frere(sommet s)
{
	return s->frere;
}

sommet pere(sommet s)
{
	return s->pere;
}

// modification

sommet creerArbrePlanaire(point racine)
{
	cellule cell = malloc(sizeof(struct cellule));
	assert(cell != NULL);
	sommet tmp = cell;
	tmp->info = racine;
	tmp->premierFils = NULL;
	tmp->frere = NULL;
	tmp->pere = NULL;
	tmp->racine = tmp;
	return tmp;
}

void ajouterFils(point racine, sommet s, point x)
{
	cellule cell = malloc(sizeof(struct cellule));
	assert(cell != NULL);
	sommet tmp = cell;
	tmp->info = x;
	tmp->frere = NULL;
	tmp->pere = s;
	tmp->racine = racine;
	if(s->premierFils == NULL)
		s->premierFils = tmp;
	else
	{
		sommet r = premierFils(s);
		while(frere(r) != NULL)
			r = frere(r);
		r->frere = tmp;
	}
}

void supprimerSommet(sommet s) //s doit être une feuille
{
	cellule p, r;
	r = premierFils(pere(s));
	if (r == s)
	{
		p = pere(s);
		p->premierFils = s->frere;
	}
	else
	{
		while(frere(r) != s)
			r = frere(r);
		r->frere = s->frere;
	}
	free(s);
	s = NULL;
}

void detruireArbrePlanaire(sommet s) // ne remet pas la valeur de s à NULL
{
	sommet f = premierFils(s);
	while(f->premierFils != NULL)
	{
		detruireArbrePlanaire(f);
		f = frere(f);
	}
	supprimerSommet(f);
	free(s);
}

void afficherArbrePlanaire(sommet s, int mode) // mode = 1 -> prefixe, mode = 2 -> suffixe
{
	sommet f;
	f = premierFils(s);
	while( f != NULL)
	{
		if(mode == 1)
			afficherPoint(getValeur(s));
		afficherArbrePlanaire(s, mode);
		if(mode == 2)
			afficherPoint(getValeur(s));
		f = frere(f);
		printf("f =  %s\n", f==NULL? "NULL": "not NULL");
	}
	if(mode == 2)
		afficherPoint(getValeur(s));

}

void parcoursHierarchique(sommet A, sommet tab[], int i)
{
	//tab[i] = A;
	sommet f = premierFils(A);
	while(f != NULL)
	{
		while(f != NULL)
		{
			tab[i] = f;
			printf("%d\n", getValeur(f));
			i++;
			f = frere(f);
		}
		f = frere(pere(f));
	}
	parcoursHierarchique(premierFils(A), tab, i);
}

