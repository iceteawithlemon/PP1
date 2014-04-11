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

/*retourne une matrice crée à partir d'une liste de points*/
matrice creerMatriceDesPoints(point liste[], int dimension) 
{
	matrice m = creerMatriceVide(dimension);
	
	for(int i = 0; i < m->dimension; i++)
	{
		m->ref[i] = liste[i];
		for(int j = 0; j < m->dimension; j++)
			m->tab[i][j] = distanceManhattan(liste[i], liste[j]);
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

matrice cloneMatrice(matrice m)
{
	return creerMatriceDesPoints(getTableauPointsMatrice(m), getDimensionMatrice(m));
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

/* à utiliser uniquement par la fonction de lecture de fichier tsp*/
void setDistanceIndice(matrice m, int ref1, int ref2, float distance)
{
	m->tab[ref1][ref2] = distance;
}


/* à utiliser uniquement par la fonction de lecture de fichier tsp*/
void setPointIndice(matrice m, int i, point p)
{
	m->ref[i] = p;
}

point *getTableauPointsMatrice(matrice m)
{
	return m->ref; //possible car utilisation de malloc ds création des matrices
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

/* retourne la valeur minimum d'un liste de floats*/
int findMin(float *list, int len, int k)
{
    int min = 1000; //valeur abitraire
    for(int i = 0; i < len; i++)
        if(list[i] < min && i != k && list[i] != -1)
            min = list[i];   
    if(min >= 1000 || min < 0)
    	return 0;
    //printf("min: %d\n", min);
    return min;
}


/* réduit une matrice et retourne son lower bound */
int lowerBound(matrice m)
{
    int n = getDimensionMatrice(m);
    int lowerBound = 0;
    int min;
    for(int i = 0; i < n; i++)
    {
        min = findMin(m->tab[i], n, i);

        lowerBound += min;
        for(int j = 0; j < n; j++)
        	if (m->tab[i][j] != 0)
            	m->tab[i][j] -= min;
    }
    for(int j = 0; j < n; j++)
    {
        float tmp[n];
        for(int i = 0; i < n; i++)
            tmp[i] = m->tab[i][j];
        min = findMin(tmp, n, j);
        lowerBound += min;
        if(min != 0)
        {
        	for(int i = 0; i < n; i++)
        		if (m->tab[i][j] != 0)
        			m->tab[i][j] -= min;
        }
    }
    return lowerBound;
}



