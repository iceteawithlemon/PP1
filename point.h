#ifndef _POINT_H
#define _POINT_H


typedef struct point * point;

point creerPoint(signed int, signed int);
void detruirePoint(point);
signed int getX(point);
signed int getY(point);
int distanceEntreDeuxPoints(point,point);
extern 



#endif
