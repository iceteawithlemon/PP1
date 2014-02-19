# include <stdlib.h>
# include <assert.h>
# include <maths.h>

# include "point.h"

typedef struct Point
{
  signed int x;
  signed int y;
} *point;

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
  assert(point != NULL);
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

int distaceEntreDeuxPoints(point p1, point p2)
{
  double x1 = getX(p1);
  double x2 = getX(p2);
  double y1 = getY(p1);
  double y2 = getY(p2);
  double tmp =  (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1);
  return sqrt(tmp);
}
