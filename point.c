# include <stdbool.h>
# include <stdlib.h>
# include <assert.h>

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

