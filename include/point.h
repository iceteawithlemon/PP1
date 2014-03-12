#ifndef _POINT_H
#define _POINT_H

# include <stdbool.h>

typedef struct Point *point;

point creerPoint(signed int x, signed int y);
void detruirePoint(point p);

bool equals(point p1,point p2);
point clone(point p);
signed int getX(point p);
signed int getY(point p);
bool isVisited(point p);

void setX(point p, signed int x);
void setY(point p, signed int y);
void markVisited(point p);

void afficherPoint(point p);
double distanceEntreDeuxPoints(point p1, point p2);



#endif

