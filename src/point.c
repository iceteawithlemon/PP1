# include <stdlib.h>
# include <assert.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>


# include <point.h>

struct Point
{
  signed int x;
  signed int y;
  bool visited;
};
//typedef struct Point *point;


/******************************* constructeurs *************************************/

/*création d'un point de coordonnées x et y */
point creerPoint(signed int x, signed int y)
{
  point p = malloc(sizeof(struct Point));
  assert(p != NULL);
  p->x = x;
  p->y = y;
  p->visited = false;
  return p;
}

/*fonction qui détruit un point*/
void detruirePoint(point p)
{
  assert(p != NULL);
  free(p);
}

/*fonction qui test l'égalité entre deux points*/
bool equals(point p1,point p2){
    return (getX(p1) == getX(p2) && getY(p1) == getY(p2))? true : false;
}

/*fonction qui retourne un clone du point passé en paramètre*/
point clone(point p){
    return creerPoint(p->x, p->y);
}

/************************************ accesseurs *****************************************/

/*retourne l'abscisse du point*/
signed int getX(point p)
{
  return p->x;
}
/*retourne l'ordonnée du point*/
signed int getY(point p)
{
  return p->y;
}
/*retourne vrai si le point à été visité*/
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
/*modifie l'ordonnée du point*/
void setY(point p, signed int y)
{
  assert(p != NULL);
  p->y = y;
}
/*marque le point comme visité*/
void markVisited(point p)
{
  p->visited = true;
}

/*affiche les coordonnées du point*/
void afficherPoint(point p)
{
  assert(p != NULL);
  printf("(%d, %d)\n", getX(p), getY(p));
}

/* calcul la distance euclidienne x+y entre deux points*/
float distanceEntreDeuxPoints(point p1, point p2) 
{
  float x1 = getX(p1);
  float x2 = getX(p2);
  float y1 = getY(p1);
  float y2 = getY(p2);
    
    float a =(x2 - x1);
    if(a<0)
        a=-a;
    float b =(y2 - y1);
    if(b<0)
        b=-b;
    
    float tmp = a+b;
    
    return tmp;
}

/* calcul la distance Manhattan R²(x²+y²) entre deux points*/
float distanceManhattan (point p1, point p2){ 

  float x1 = getX(p1);
  float x2 = getX(p2);
  float y1 = getY(p1);
  float y2 = getY(p2);

  float a =(x2 - x1);
  float b =(y2 - y1);
 
  float tmp = sqrt((a*a)+(b*b));
    
  return tmp;
	

}
