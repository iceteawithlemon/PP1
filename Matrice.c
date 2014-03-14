# include "point.h"
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <string.h>


struct Matrice
{
	int dimension;
	point *ref; //référence pour trouver l'indice correspondant à un point donnée
	float **tab; // matrice des valeurs
};
typedef struct Matrice *matrice;


//primitives de modification

matrice creerMatriceDesPoints(point liste[], int dimension) //retourne une matrice crée à partir d'une liste de points
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


void detruireMatrice(matrice m)
{
	for(int i = 0; i < m->dimension; i++)
		free(m->tab[i]);
	free(m->tab);
	free(m->ref);
	free(m);
}

//primitives d'accès

int getIndicePoint(matrice m, point p)
{
	for(int i = 0; i < m->dimension; i++)
		if (equals(p, m->ref[i]))
			return i;
	return -1;	
}

point getPointIndice(matrice m, int indice)
{
	return m->ref[indice];
}

double getDistanceIndice(matrice m, int ref1, int ref2)
{
	return m->tab[ref1][ref2];
}

double getDistancePoint(matrice m, point p1, point p2)
{
	return getDistanceIndice(m, getIndicePoint(m, p1), getIndicePoint(m, p2));
}


// affichage

void afficherMatrice(matrice m)
{
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


// lecture de tsp
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
/*
void lecture_tsp(FILE *fp)
{
	char str[1000];
	char tmp[1000];
	char *tok;
	int x = 0;
	int y = 0;
	int i = 0;
	int j = 0;
	int dim;
	matrice m;
	char *delim = ": ";
	while(fgets(str, 1000, fp))
	{	
		//printf("{%s}", str);
		strcpy(tmp, str);
		tok = strtok(tmp, ":");
		while(tok != NULL && x == 0)
		{
			if(!strcmp(tok, "DIMENSION"))
			{
				dim = atoi(strtok(NULL, delim));
				m = creerMatriceVide(dim);
			}
			if(!strcmp(tok, "EDGE_WEIGHT_FORMAT") && strcmp(strtok(NULL, ": "), "FULL_MATRIX"))
				exit(0);
			if (!strcmp(tok, "EDGE_WEIGHT_SECTION\n"))
				x=1;
			printf("(%s)\n", tok);
			tok = strtok(NULL, delim);
		}

		if(x == 1)
		{
			delim = " ";
			j = 0;
			strcpy(tmp, str);
			tok = strtok(tmp, delim);
			//printf("tok: %s\n", tok);
			//i++;
			while(tok != NULL && y == 0)
			{
				
				if(!strcmp(tok, "DISPLAY_DATA_SECTION\n"))
					y=1;
				tok = strtok(NULL, delim);
				j++;
				if(tok && !strcmp(tok, "\n"))
					i++;
				if(j >= dim)
						j = 0;
				if(tok && i < dim && j< dim)
				{
					printf("i, j: %d, %d\n", i, j);
					printf("[%d]\n", atoi(tok));
				}
				

			}
		}
	}

} */

void ecrireMatriceTSP(char *fnom, matrice m)
{
	char tmp[strlen(fnom)];
	memcpy(tmp, fnom, strlen(fnom)-4);
	FILE *fp = ouvrir_tsp(fnom, "w");
	assert(fp != NULL);
	fprintf(fp, "NAME: %s\nTYPE: TSP\nDIMENSION: %d\n", tmp, m->dimension);
	fprintf(fp, "EDGE_WEIGHT_TYPE: EXPLICIT\nEDGE_WEIGHT_FORMAT: FULL_MATRIX\nDISPLAY_DATA_TYPE: TWOD_DISPLAY\nEDGE_WEIGHT_SECTION\n");
	for(int i = 0; i < m->dimension; i++)
	{
		for(int j = 0; j < m->dimension; j++)
			fprintf(fp, "%f ", getDistanceIndice(m, i, j));
		fprintf(fp, "\n");
	}
	fprintf(fp, "DISPLAY_DATA_SECTION\n");
	for(int i = 0; i < m->dimension; i++)
		fprintf(fp, "\t%d\t%f\t%f\n", i+1, (double)getX(getPointIndice(m, i)), (double)getY(getPointIndice(m, i)));
	fprintf(fp, "EOF\n");
	fermer_tsp(fp);
}


int main()
{
	point a = creerPoint(0, 0);
	point b = creerPoint(-4, 4);
	point c = creerPoint(10, 10);
	point d = creerPoint(1, -2);
	point test_list[] = {a, b, c, d};


	matrice test = creerMatriceDesPoints(test_list, 4);
	afficherMatrice(test);

	afficherPoint(a);
	printf("Ref de a: %d\n", getIndicePoint(test, a));
	afficherPoint(getPointIndice(test, 0));
	printf("%f\n", getDistanceIndice(test, 0, 2));
	printf("%f\n", getDistancePoint(test, a, c));

	//printf("Lecture tsp: \n");
	//char fnom[] = "exemple10.tsp";
	//FILE *fp = ouvrir_tsp(fnom, "r");
	//lecture_tsp(fp);
	//fermer_tsp(fp);

	char tsp_test[] = "test.tsp";
	ecrireMatriceTSP(tsp_test, test);

	detruireMatrice(test);

	return 0;
}