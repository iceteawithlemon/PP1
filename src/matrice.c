# include "point.h"
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <string.h>

# include "matrice.h"

//definition d'une structure matrice
struct Matrice
{
	int dimension;
	point *ref; //référence pour trouver l'indice correspondant à un point donnée
	float **tab; // matrice des valeurs
};
//typedef struct Matrice *matrice;


/********************************* primitives de modification ************************************/

/*retourne une matrice crée à partir d'une liste de points*/
matrice creerMatriceDesPoints(point liste[], int dimension) 
{
	matrice m = malloc(sizeof(struct Matrice));
	m->dimension = dimension ;
	m->ref = malloc(sizeof(point) * m->dimension);
	m->tab = malloc(sizeof(float*) * m->dimension);
    
	for(int i = 0; i < m->dimension; i++)
	{
		m->ref[i] = liste[i];
		m->tab[i] = malloc(sizeof(float) * m->dimension);
	}
	
	for(int i = 0; i < m->dimension; i++)
		for(int j = 0; j < m->dimension; j++)
			m->tab[i][j] = distanceManhattan(liste[i], liste[j]);
	return m;
}

/*fonction qui crée une matrice vide*/
matrice creerMatriceVide(int dimension) //à utiliser dans la lecture des fichiers tsp
{
	matrice m = malloc(sizeof(struct Matrice));
	m->dimension = dimension ;
	m->ref = malloc(sizeof(point) * m->dimension);
	m->tab = malloc(sizeof(float*) * m->dimension);
    
	for(int i = 0; i < m->dimension; i++)
	{
		m->tab[i] = malloc(sizeof(float) * m->dimension);
	}
    
	return m;
}

/*fonction qui détruit une matrice passée en paramètres*/
void detruireMatrice(matrice m)
{
	for(int i = 0; i < m->dimension; i++)
		free(m->tab[i]);
	free(m->tab);
	free(m->ref);
	free(m);
}

/*********************************** primitives d'accès **************************************/

/*retourne l'indice d'un point, ou -1 s'il n'existe pas*/
int getIndicePoint(matrice m, point p) 
{
	for(int i = 0; i < m->dimension; i++)
		if (equals(p, m->ref[i]))
			return i;
	return -1;
}

/*retourne un point à partir de son indice*/
point getPointIndice(matrice m, int indice) 
{
	return m->ref[indice];
}

/*retourne la distance entre deux points referencés par les deux indices données*/
float getDistanceIndice(matrice m, int ref1, int ref2) 
{
	return m->tab[ref1][ref2];
}

/*retourne la distance entre deux points*/
float getDistancePoint(matrice m, point p1, point p2) 
{
	return getDistanceIndice(m, getIndicePoint(m, p1), getIndicePoint(m, p2));
}

/*retourne la dimension d'une matrice passée en paramètre*/
int getDimensionMatrice(matrice m){
    return m->dimension;
}


/************************************* affichage *******************************************/

/*affiche la matrice passée en paramètre*/
void afficherMatrice(matrice m) 
{
	assert(m != NULL);
	printf("Dimension: %d\n", m->dimension);
	printf("Points: \n");
	for(int i = 0; i < m->dimension; i++)
	{
		printf("%d. ", i+1);
		afficherPoint(m->ref[i]);
	}
	printf("Matrice: \n");
	for(int i = 0; i < m->dimension; i++)
	{
		for(int j = 0; j < m->dimension; j++)
			printf("%0.1f\t", m->tab[i][j]);
		printf("\n");
	}
    
}


/* lecture de tsp*/
FILE *ouvrir_tsp(char *fnom, char *mode)
{
	FILE *fp = fopen(fnom, mode);
	if(fp == NULL)
	{
		printf("Erreur: lecture de fichier impossible.\n");
		exit(0);
	}
	return fp;
}

void fermer_tsp(FILE *fp)
{
	fclose(fp);
}

/*crée un matrice à partir d'un fichier TSP de format 'FULL_MATRIX' 
-> !!! ne pas utiliser tout seul - il faut utiliser son wrapper "creerMatriceTSP"*/
matrice lecture_tsp(FILE *fp) 
{
	char str[1000];
	char *tok;
	int x = 0;
	int y = 0;
	int i = 0;
	int j = 0;
	int pi = 0;
	float px = 0;
	float py = 0;
	int k = 0;
	int dim_bool = 0;
	int dim;
	int skip = 1;
	matrice m;
	char *delim = ": ";
	while(!feof(fp))
	{
		if(y == 0)
			fscanf(fp, "%s\n", str);
		tok = strtok(str, ":");
		while(tok != NULL && x == 0)
		{
			//printf("tok: '%s'\n", tok);
			if(dim_bool)
			{
				dim = atoi(tok);
				//printf("dim: %d\n", dim);
				dim_bool = 0;
				m = creerMatriceVide(dim);
			}
			if(!strcmp(tok, "DIMENSION"))
				dim_bool = 1;
			if (!strcmp(tok, "EDGE_WEIGHT_SECTION"))
				x=1;
			tok = strtok(NULL, delim);
		}
		if(x == 1)
		{
			if(i >= dim)
				y = 1;
			delim = " ";
			tok = strtok(str, delim);
			while(tok != NULL && y == 0 && !skip && i < dim)
			{
				//printf("i, j: %d, %d = %.2f\n", i, j, atof(tok));
				m->tab[i][j] = atof(tok);
				j++;
				if(j >= dim)
				{
					j = 0;
					i++;
				}
				if(!strcmp(tok, "DISPLAY_DATA_SECTION"))
					y=1;
				tok = strtok(NULL, delim);
			}
			skip = 0;
		}
		if(y == 1 && k < dim)
		{
			fscanf(fp, "%d %f %f\n", &pi, &px, &py);
			m->ref[pi-1] = creerPoint(px, py);
			//printf("%d %f %f\n", pi, px, py);
			k++;
		}
		if(k >= dim)
			break;
	}
	return m;
    
}

/*wrapper for lecture_tsp*/
matrice creerMatriceTSP(char *fnom) 
{
	FILE *fp = ouvrir_tsp(fnom, "r");
	matrice m = lecture_tsp(fp);
	fclose(fp);
	return m;
}


void creerTSPMatrice(char *fnom, matrice m)
{
	char *tmp;
	asprintf(&tmp, "%s.tsp", fnom);
	FILE *fp = ouvrir_tsp(tmp, "w");
	assert(fp != NULL);
	int is_int = ( (int)m->tab[0][1] == m->tab[0][1] ) ;
	fprintf(fp, "NAME: %s\nTYPE: TSP\nDIMENSION: %d\n", fnom, m->dimension);
	fprintf(fp, "EDGE_WEIGHT_TYPE: EXPLICIT\nEDGE_WEIGHT_FORMAT: FULL_MATRIX\nDISPLAY_DATA_TYPE: TWOD_DISPLAY\nEDGE_WEIGHT_SECTION\n");
	for(int i = 0; i < m->dimension; i++)
	{
		for(int j = 0; j < m->dimension; j++)
			if(is_int)
				fprintf(fp, "%d ", (int)getDistanceIndice(m, i, j));
			else
				fprintf(fp, "%f ", getDistanceIndice(m, i, j));
		fprintf(fp, "\n");
	}
	fprintf(fp, "DISPLAY_DATA_SECTION\n");
	for(int i = 0; i < m->dimension; i++)
		if(is_int)
			fprintf(fp, "\t%d\t%d\t%d\n", i+1, (int)getX(getPointIndice(m, i)), (int)getY(getPointIndice(m, i)));
		else
			fprintf(fp, "\t%d\t%f\t%f\n", i+1, (float)getX(getPointIndice(m, i)), (float)getY(getPointIndice(m, i)));
	fprintf(fp, "EOF\n");
	fermer_tsp(fp);
}

/*la liste des points DOIT correspondre à la matrice donnée*/
void creerTOUR(char *fnom, matrice m, point liste[]) 
{
	char *tmp;
	asprintf(&tmp, "%s.opt.tour", fnom);
	FILE *fp = ouvrir_tsp(tmp, "w");
	assert(fp != NULL);
	fprintf(fp, "NAME : %s\n", tmp);
	fprintf(fp, "COMMENT : Optimum solution of %s\n", fnom);
	fprintf(fp, "DIMENSION : %d\n", m->dimension);
	fprintf(fp, "TOUR_SECTION\n");
	for(int i = 0; i < m->dimension; i++)
		fprintf(fp, "%d\n", getIndicePoint(m, liste[i]));
	fprintf(fp, "EOF\n");
	fclose(fp);
}


