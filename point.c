# include <stdlib.h>
# include <assert.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>


# include "point.h"

struct Point
{
  signed int x;
  signed int y;
  bool visited;
};
typedef struct Point *point;


//constructeurs
point creerPoint(signed int x, signed int y)
{
  point p = malloc(sizeof(struct Point));
  assert(p != NULL);
  p->x = x;
  p->y = y;
  p->visited = false;
  return p;
}

void detruirePoint(point p)
{
  assert(p != NULL);
  free(p);
}

// accesseurs
signed int getX(point p)
{
  return p->x;
}

signed int getY(point p)
{
  return p->y;
}

bool isVisited(point p)
{
  return p->visited;
}

void setX(point p, signed int x)
{
  assert(p != NULL);
  p->x = x;
}

void setY(point p, signed int y)
{
  assert(p != NULL);
  p->y = y;
}

void markVisited(point p)
{
  p->visited = true;
}

//misc.
void afficherPoint(point p)
{
  assert(p != NULL);
  printf("(%d, %d) (visitée? %s)\n", getX(p), getY(p), isVisited(p)? "True" : "False");
}


double distanceEntreDeuxPoints(point p1, point p2)
{
  double x1 = getX(p1);
  double x2 = getX(p2);
  double y1 = getY(p1);
  double y2 = getY(p2);

  return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));	
}
