# include "point.h"
# include "ArbresBinaires.h"
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>



# define GLOBAL_MAX_DIST 100

point findNearestNeighbour(point p, point list[], int length_list) //retourne le point le plus proche
{
	int indice = 0;
	int local_max_distance = GLOBAL_MAX_DIST;
	int tmp_distance;
	for(int i = 0; i < length_list; i++)
	{
		tmp_distance = distanceEntreDeuxPoints(p, list[i]);
		if(tmp_distance < local_max_distance && !isVisited(list[i]) &&tmp_distance > 0) //dernier condition pour ne pas retourner le même point
		{
			indice = i;
			local_max_distance = tmp_distance;
		}
	}
	return list[indice];
}



int main()
{
	point a = creerPoint(0, 0);
	point b = creerPoint(-4, 4);
	point c = creerPoint(10, 10);
	point d = creerPoint(1, -2);
	point test_list[] = {a, b, c, d};

	afficherPoint(findNearestNeighbour(a, test_list, 4));

	for(int i = 0; i < 4; i++)
		detruirePoint(test_list[i]);

	return 0;
}