#ifndef _POINT_H
#define _POINT_H


typedef struct Point *point;

point creerPoint(signed int, signed int);
void detruirePoint(point);
signed int getX(point);
signed int getY(point);
float distanceEntreDeuxPoints(point,point);



#endif
