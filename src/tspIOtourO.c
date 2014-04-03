# define _GNU_SOURCE

# include <stdio.h>
# include <assert.h>
# include <stdlib.h>
# include <string.h>
# include "point.h"
# include "matrice.h"
# include "tspIOtourO.h"

matrice creerMatriceTSP(char *fileName)
{
	char arg1[100];
	char arg2[100];
	char dump[100];
	int i = 0;
	int j = 1;
	int dim;
	if (strstr(fileName, ".tsp") == NULL) //si le nom du fichier passée en paramètre ne contient pas ".tsp", l'ajouter
		asprintf(&fileName, "%s.tsp", fileName);
	//printf("%s\n", fileName);
	FILE *fp = fopen(fileName, "r");
	if(fp == NULL)
		exit(1);

	while(fscanf(fp, "%s %s\n", arg1, arg2) && strcmp(arg1, "EDGE_WEIGHT_SECTION") != 0)
	{	
		//printf("'%s' '%s'\n", arg1, arg2);
		if(strcmp(arg1, "DIMENSION:") == 0)
			dim = atoi(arg2);
	}
	matrice m = creerMatriceVide(dim);
	setDistanceIndice(m, 0, 0, 0);
	while(fscanf(fp, "%s ", arg1) && strcmp(arg1, "DISPLAY_DATA_SECTION") != 0)
	{
		if(j >= dim)
		{
			i++;
			j = 0;
		}
		setDistanceIndice(m, i, j, atof(arg1));
		//printf("i: %d j: %d = %s\n", i, j, arg1);
		j++;
	}
	i = 0;
	while(fscanf(fp, "%s %s %s", dump, arg1, arg2) && strcmp(dump, "EOF") != 0)
	{
		setPointIndice(m, i, creerPoint(atof(arg1), atof(arg2)));
		//printf("%d: %s %s\n", i, arg1, arg2);
		i++;
	}

 	return m;
}



extern void creerTSPMatrice(char *fileName, matrice m)
{
	if (strstr(fileName, ".tsp") == NULL) //si le nom du fichier passée en paramètre ne contient pas ".tsp", l'ajouter
		asprintf(&fileName, "%s.tsp", fileName);
	//printf("%s\n", fileName);
	FILE *fp = fopen(fileName, "w");
	int is_int = ( (int)getDistanceIndice(m, 0, 1) == getDistanceIndice(m, 0, 1) ) ;
	fprintf(fp, "NAME: %s\nTYPE: TSP\nDIMENSION: %d\n", fileName, getDimensionMatrice(m));
	fprintf(fp, "EDGE_WEIGHT_TYPE: EXPLICIT\nEDGE_WEIGHT_FORMAT: FULL_MATRIX\nDISPLAY_DATA_TYPE: TWOD_DISPLAY\nEDGE_WEIGHT_SECTION\n");
	for(int i = 0; i < getDimensionMatrice(m); i++)
	{
		for(int j = 0; j < getDimensionMatrice(m); j++)
			if(is_int)
				fprintf(fp, "%d ", (int)getDistanceIndice(m, i, j));
			else
				fprintf(fp, "%f ", getDistanceIndice(m, i, j));
		fprintf(fp, "\n");
	}
	fprintf(fp, "DISPLAY_DATA_SECTION\n");
	for(int i = 0; i < getDimensionMatrice(m); i++)
		if(is_int)
			fprintf(fp, "\t%d\t%d\t%d\n", i+1, (int)getX(getPointIndice(m, i)), (int)getY(getPointIndice(m, i)));
		else
			fprintf(fp, "\t%d\t%f\t%f\n", i+1, (float)getX(getPointIndice(m, i)), (float)getY(getPointIndice(m, i)));
	fprintf(fp, "EOF\n");
	fclose(fp);
}

/*la liste des points DOIT correspondre à la matrice donnée*/
extern void creerTOUR(char *fileName, matrice m, point liste[]) 
{
	if (strstr(fileName, ".opt.tour") == NULL) //si le nom du fichier passée en paramètre ne contient pas ".tsp", l'ajouter
		asprintf(&fileName, "%s.opt.tour", fileName);
	printf("%s\n", fileName);
	FILE *fp = fopen(fileName, "w");
	assert(fp != NULL);
	fprintf(fp, "NAME : %s\n", fileName);
	fprintf(fp, "COMMENT : Optimum solution of %s\n", fileName);
	fprintf(fp, "DIMENSION : %d\n", getDimensionMatrice(m));
	fprintf(fp, "TOUR_SECTION\n");
	for(int i = 0; i < getDimensionMatrice(m); i++)
		fprintf(fp, "%d\n", getIndicePoint(m, liste[i]));
	fprintf(fp, "EOF\n");
	fclose(fp);
}