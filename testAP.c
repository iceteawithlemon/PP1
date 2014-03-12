# include "ArbresPlanaires.h"



int main()
{

	point a = creerPoint(0, 0);
	point b = creerPoint(-4, 4);
	point c = creerPoint(10, 10);
	point d = creerPoint(1, -2);

	sommet A = creerArbrePlanaire(a);
	ajouterFils(A, b);
	ajouterFils(A, c);
	ajouterFils(A, d);

	afficherPoint(getPoint(A));
	afficherPoint(getPoint(premierFils(A)));
	return 0;
}

