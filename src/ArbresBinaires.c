# include <stdio.h>
# include <assert.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

# include "ArbresBinaires.h"

typedef struct cellule cellule;
typedef cellule *sommet;
struct cellule
{
	void *info;
	sommet gauche;
	sommet droit;
	sommet pere;
};

struct file
{
	int taille;
	int premier;
	int dernier;
	bool plein;
	sommet *fileT;
};

typedef struct file *file;

file creerFile(int taille)
{
	file F = malloc(sizeof(struct file));
	F->taille = taille;
	F->premier = 0;
	F->dernier = -1;
	F->plein = false;
	F->fileT = malloc(sizeof(sommet) * F->taille);
	return F;
}

void detruireFile(file F)
{
	free(F->fileT);
	free(F);
}

void *valeur(file F)
{
	return F->fileT[F->premier];
}

bool fileVide(file F)
{
	return ((F->premier == F->dernier) && (!F->plein));
}


void enfiler(file F, void* x)
{
	if (F->plein)
	{
		F->taille += 10;
		sommet *new = realloc(F->fileT, sizeof(struct file) * F->taille);
		F->fileT = new;
	}
	F->dernier = (F->dernier+1)%F->taille;
	F->fileT[F->dernier]=x;
	F->plein=(F->dernier == F->premier);
}


void defiler(file F)
{
	F->premier=((F->premier+1)%(F->taille));
	F->plein=false;
}

// accès

void *getValeur(sommet s)
{
	return s->info;
}

sommet filsGauche(sommet s)
{
	return s->gauche;
}

sommet filsDroit(sommet s)
{
	return s->droit;
}

sommet pere(sommet s)
{
	return s->pere;
}

bool estFeuille(sommet s)
{
	return ((filsGauche(s)==NULL) && (filsDroit(s)==NULL));
}

//modification

sommet creerArbreBinaire(void *racine)
{
	cellule *cell = (cellule*)malloc(sizeof(cellule));
	assert(cell != NULL);
	sommet tmp = cell;
	tmp->info = racine;
	tmp->gauche=NULL;
	tmp->droit=NULL;
	tmp->pere=NULL;
	return tmp;
}

void ajouterFilsGauche(sommet S, void *x)
{
	cellule *temp = (cellule*)malloc(sizeof(cellule));
	assert(temp != NULL);
	temp->info=x;
	temp->gauche=NULL;
	temp->droit=NULL;
	temp->pere=S;
	S->gauche=temp;
}

void ajouterFilsDroit(sommet S, void *x)
{
	cellule *temp = (cellule*)malloc(sizeof(cellule));
	assert(temp != NULL);
	temp->info=x;
	temp->gauche=NULL;
	temp->droit=NULL;
	temp->pere=S;
	S->droit=temp;
}

void supprimerFilsGauche(sommet S)
{
	free(S->gauche);
	S->gauche=NULL;
}

void supprimerFilsDroit(sommet S)
{
	free(S->droit);
	S->droit=NULL;
}

void detruireArbreBinaire(sommet s) //does not free the sommet that is passed in parameter
{
	sommet A = s;
	//parcours suffixe
	if (estFeuille(A))
	{
		free(A);
	}
	else
	{
		if (filsGauche(A) != NULL)
			detruireArbreBinaire(filsGauche(A));
		if (filsDroit(A) != NULL)
			detruireArbreBinaire(filsDroit(A));
		if(A != s) //because the original sommet is passed as val and not ref
			free(A);
	}
}

sommet remplirTableauArbre(void *tab[], int len)
{
	sommet A = creerArbreBinaire(tab[0]);
	file F;
	sommet s;
	F = creerFile(len);
	enfiler(F, A);
	int c = 1; //place in list
	while(c<(len-1))
	{
		s=valeur(F);
		defiler(F);
		ajouterFilsGauche(s, tab[c]);
		enfiler(F, filsGauche(s));
		ajouterFilsDroit(s, tab[c+1]);
		enfiler(F, filsDroit(s));
		c+=2;
	}
	//if there's one value in the list left
	if (c == (len - 1))
	{
		s=valeur(F);
		defiler(F);
		ajouterFilsGauche(s, tab[c]);
	}
	return A;
}

/*void afficherArbre(sommet A, int mode) 
{
	if (estFeuille(A))
		printf("%d ", getValeur(A));
	else
	{
		if (mode == 1)
			printf("%d ", getValeur(A));
		if(filsGauche(A) != NULL)
			afficherArbre(filsGauche(A), mode);
		if(mode == 2)
			printf("%d ", getValeur(A));
		if(filsDroit(A) != NULL)
			afficherArbre(filsDroit(A), mode);
		if(mode == 3)
			printf("%d ", getValeur(A));
	}

}*/

/*int arbre2Tableau(sommet A, void **tab, int i)
{
	i+=1;
	tab[i]=getValeur(A);
	
	if (!estFeuille(A))
	{
		if(filsGauche(A) != NULL)
		{
			i = arbre2Tableau(filsGauche(A), tab, i);
		}
		if(filsDroit(A) != NULL)
		{
			i = arbre2Tableau(filsDroit(A), tab, i);
		}
	}
	return i;
}*/

int hauteurArbreBinaire(sommet s)
{
	
	if(estFeuille(s))
		return 0;
	else
	{
		int tmp1, tmp2;
		tmp1 = tmp2 = 0;

		if(filsGauche(s) != NULL)
			tmp1 = hauteurArbreBinaire(filsGauche(s));
		if(filsDroit(s) != NULL)
			tmp2 = hauteurArbreBinaire(filsDroit(s));
		if (tmp1>tmp2)
			return tmp1+1;
		else
			return tmp2+1;
	}
}

int tailleArbreBinaire(sommet A) //si A est un arbre binaire complet
{
	if(estFeuille(A))
		return 1;
	else
		return(1 + tailleArbreBinaire(filsGauche(A)) + tailleArbreBinaire(filsDroit(A)));
}


// 19/11/2013

bool estComplet(sommet A)
{
	if (estFeuille(A))
		return true;
	else
	{
		if(filsGauche(A) != NULL && filsDroit(A) != NULL)
			return estComplet(filsGauche(A)) && estComplet(filsDroit(A));
		else
			return false;
	}
}

