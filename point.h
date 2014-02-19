#ifndef _POINT_H
#define _POINT_H


typedef struct point * point;

point creerPoint(double,double);
void detruirePoint(point);
signed double getX(point);
signed double getY(point);
double distanceEntreDeuxPoints(point,point);
extern 



#endif
