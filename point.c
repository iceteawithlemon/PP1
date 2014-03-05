# include <stdlib.h>
# include <assert.h>
# include <math.h>

# include "point.h"

struct Point
{
  signed int x;
  signed int y;
};
typedef struct Point *point;

point creerPoint(signed int x, signed int y)
{
  point p = malloc(sizeof(struct Point));
  assert(p != NULL);
  p->x = x;
  p->y = y;
  return p;
}

void detruirePoint(point p)
{
  assert(p != NULL);
  free(p);
}



signed int getX(point p)
{
  return p->x;
}

signed int getY(point p)
{
  return p->y;
}

double distanceEntreDeuxPoints(point p1, point p2)
{
  double x1 = getX(p1);
  double x2 = getX(p2);
  double y1 = getY(p1);
  double y2 = getY(p2);

  double a =(x2 - x1);
  if(a<0)
     a=-a;		
  double b =(y2 - y1);
  if(b<0)
     b=-b;

  double tmp = a+b;
	
  return tmp;
}
