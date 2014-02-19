# include "point.h"

# include <stdlib.h>
# include <stdio.h>



int main()
{
  point p = creerPoint(0, 0);
  point q = creerPoint(0, 4);
  printf("p = (%d, %d)\n", getX(p), getY(p));
  printf("Distance entre p et q: %.2f\n", distanceEntreDeuxPoints(p, q));
  return 0;
}
