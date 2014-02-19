# include <stdlib.h>
# include <assert.h>
# include <maths.h>

# include "point.h"

typedef struct Point
{
  signed double x;
  signed double y;
} *point;

point creerPoint(signed double x, signed double y)
{
  point p = malloc(sizeof(struct Point));
  assert(p != NULL);
  p->x = x;
  p->y = y;
  return p;
}

void detruirePoint(point p)
{
  assert(point != NULL);
  free(p);
}



signed double getX(point p)
{
  return p->x;
}

signed double getY(point p)
{
  return p->y;
}

double distace(point p1, point p2)
{
  double x1 = getX(p1);
  double x2 = getX(p2);
  double y1 = getY(p1);
  double y2 = getY(p2);
  double tmp =  (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1);
  return sqrt(tmp);
}
