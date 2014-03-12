# include "LDCDynam.h"
# include "point.h"
# include <stdio.h>

int main()
{
	point a = creerPoint(0, 0);
	point b = creerPoint(-4, 4);
	point c = creerPoint(10, 10);
	point d = creerPoint(1, -2);

	liste test = creerListe();

	insererApres(test, a);
	printf("Hello!\n");
	printList(test);
	printf("Hi\n");
	insererApres(test, b);
	printf("fghj\n");
	printList(test);
	printf("b\n");
	insererApres(test, c);
	printf("c\n");

	printList(test);
	ajouter(test, d);
	printList(test);

	return 0;
}