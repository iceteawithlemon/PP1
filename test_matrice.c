# include "point.h"

# include "matrice.h"
# include <stdio.h>


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

	char fnom[] = "exemple10.tsp";
	printf("Lecture du fichier tsp: %s\n", fnom);
	matrice m = creerMatriceTSP(fnom);
	
	afficherMatrice(m);
	creerTSPMatrice("test2", test);

	creerTOUR("test_tour", test, test_list);


	detruireMatrice(test);

	return 0;
}