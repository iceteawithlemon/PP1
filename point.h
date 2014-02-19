#ifndef _POINT_H
#define _POINT_H


typedef struct point * point;

point creerPoint(double,double);
void detruirePoint(Point);
signed double getX();
signed double getY();
double distanceEntreDeuxPoints(point,point);
extern 



#endif
