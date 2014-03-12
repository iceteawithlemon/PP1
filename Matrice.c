# include "point.h"
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>


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

void lecture_tsp(FILE *fp)
{
	assert(fp != NULL);
	while(fscanf(fp, "%s", str)!= "EOF")
	{
		fscanf(fp, "%s: %s")
	}
} */

//primitives de modification


matrice creerMatriceDesPoints(point liste[], int dimension)
{
	matrice m = malloc(sizeof(struct Matrice));
	m->dimension = dimension ;
	m->ref = malloc(sizeof(point) * m->dimension);
	m->tab = malloc(sizeof(float*) * m->dimension);

	for(int i = 0; i < m->dimension; i++)
	{
		m->ref[i] = liste[i];
	}
	
	for(int i = 0; i < m->dimension; i++)
	{
		m->tab[i] = malloc(sizeof(float) * m->dimension);
		for(int j = 0; j < m->dimension; j++)
		{
			printf("i, j: %d, %d\n", i, j);
			afficherPoint(m->ref[i]);
			afficherPoint(m->ref[j]);
			m->tab[i][j] = m->tab[j][i] = distanceManhattan(liste[i], liste[j]);
			printf("%d\n", m->tab[i][j]);
		}
	}
	return m;
}

void detruireMatrice(matrice m)
{
	free(m->tab);
	free(m->ref);
	free(m);
}

void afficherMatrice(matrice m)
{
	printf("Dimension: %d\n", m->dimension);
	printf("Points: \n");
	for(int i = 0; i < m->dimension; i++)
	{
		printf("%d. ", i);
		afficherPoint(m->ref[i]);
	}
	printf("\n");
	printf("Matrice: \n");
	for(int i = 0; i < m->dimension; i++)
	{
		for(int j = 0; j < m->dimension; j++)
			printf("%f ", m->tab[i][j]);
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
	afficherPoint(a);
	matrice test = creerMatriceDesPoints(test_list, 4);
	afficherPoint(b);
	afficherMatrice(test);

	//detruireMatrice(test);

	return 0;
}