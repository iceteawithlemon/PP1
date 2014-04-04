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
//typedef struct Point *point;


/******************************* constructeurs *************************************/

/*cr�ation d'un point de coordonn�es x et y */
point creerPoint(signed int x, signed int y)
{
  point p = malloc(sizeof(struct Point));
  assert(p != NULL);
  p->x = x;
  p->y = y;
  p->visited = false;
  return p;
}

/*fonction qui d�truit un point*/
void detruirePoint(point p)
{
  assert(p != NULL);
  free(p);
}

/*fonction qui test l'�galit� entre deux points*/
bool equals(point p1,point p2){
    return (getX(p1) == getX(p2) && getY(p1) == getY(p2))? true : false;
}

/*fonction qui retourne un clone du point pass� en param�tre*/
point clone(point p){
    return creerPoint(p->x, p->y);
}

/************************************ accesseurs *****************************************/

/*retourne l'abscisse du point*/
signed int getX(point p)
{
  return p->x;
}
/*retourne l'ordonn�e du point*/
signed int getY(point p)
{
  return p->y;
}
/*retourne vrai si le point � �t� visit�*/
bool isVisited(point p)
{
  return p->visited;
}
/*modifie l'abscisse du point*/
void setX(point p, signed int x)
{
  assert(p != NULL);
  p->x = x;
}
/*modifie l'ordonn�e du point*/
void setY(point p, signed int y)
{
  assert(p != NULL);
  p->y = y;
}
/*marque le point comme visit�*/
void markVisited(point p)
{
  p->visited = true;
}

/*affiche les coordonn�es du point*/
void afficherPoint(point p)
{
  assert(p != NULL);
  printf("(%d, %d)\n", getX(p), getY(p));
}

//affiche une liste de points
void afficherListeDesPoints(point *p, int len)
{
  for(int i = 0; i < len; i++)
    afficherPoint(p[i]);
}

/* calcul la distance manhattan x+y entre deux points*/
float distanceManhattan(point p1, point p2) 
{  
    return abs((getX(p2) - getX(p1))) + abs(getY(p2) - getY(p1));
}

/* calcul la distance R�(x�+y�) entre deux points*/
float distanceEntreDeuxPoints (point p1, point p2){ 

  return sqrt( pow( getX(p2) - getX(p1), 2 ) + pow( getY(p2) - getY(p1), 2) ) ;
	
}
