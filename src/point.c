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

bool equals(point p1,point p2){
    return (getX(p1) == getX(p2) && getY(p1) == getY(p2))? true : false;
}

point clone(point p){
    return creerPoint(p->x, p->y);
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
  printf("(%d, %d)\n", getX(p), getY(p));
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
