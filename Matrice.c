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

// lecture de tsp
/*FILE *ouvrir_tsp(char *fnom)
{
	FILE *fp = fopen(fnom, "r");
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

void lecture_tsp(FILE *fp)
{
	char str[100];
	char *test = "EDGE_WEIGHT_SECTION";
/*	while(fgets(str, 100, fp))
	{	
		if(strcmp(str, test) == 0)
		{

			printf("%s\n", str);
		}
	}
} */

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

	printf("Lecture tsp: \n");
	char fnom[] = "exemple10.tsp";
	FILE *fp = ouvrir_tsp(fnom);
	lecture_tsp(fp);
	fermer_tsp(fp);

	detruireMatrice(test);

	return 0;
}