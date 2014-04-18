//FilesTableau.c
//Implementation des files avec un tableau
//21/10/13

# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>

# include "Files.h"

typedef int objet;

struct file
{
	int taille;
	int premier;
	int dernier;
	bool plein;
	objet *tableau;
};
typedef struct file *file;

void creerFile(file F, int taille)
{
	F->taille = taille;
	F->premier = F->dernier = -1; //0?
	F->plein = false;
	F->tableau = malloc(taille*sizeof(objet));
}

objet valeur(file F)
{
	return(F->tableau[F->premier]);
}

bool fileVide(file F)
{
	return(F->premier==F->dernier && !F->plein);
}

bool enfiler(file F, objet x)
{
	if (F->plein)
		return false;
	else
	{
		F->tableau[F->dernier]=x;
		F->dernier=(F->dernier+1)%F->taille;
		F->plein=(F->dernier==F->premier);
		return true;
	}
}

void defiler(file F)
{
	F->premier=(F->premier+1)%F->taille;
	F->plein=false;
}


int compteFile(file F)
{
	int v, compt;
	compt =0;
	enfiler(F, 0);
	while(valeur(F)!=0)
	{
		compt++;
		v=valeur(F);
		defiler(F);
		enfiler(F, v);
	}
	defiler(F);
	return compt;
}
