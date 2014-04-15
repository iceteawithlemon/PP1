#include "point.h"
#include <stdlib.h>
#include "matrice.h"

/**
 * \brief Cherche dans la matrice quel est le point non visité le plus proche  du point indiqué par l'indice,
 * cette fonction utilise la fonction getDistanceIndice() permettant de connaitre la distance entre deux points.
 *
 * \param indicePointActuel correspond à l'indice du point actuel, permettant l'accès à ce point.
 * \param m matrice contenant tous les points
 *
 * \return: indice du point le plus proche du point actuel
 */
int PointLePlusProche(int indicePointActuel,matrice m){
    
    float distance = 0;
    float tmp = 0;
    int TailleTab = getDimensionMatrice(m);
    
    int indice = 0;
    
    while(isVisited(getPointIndice(m,indice))){
        indice++;
    }
    
    
    //Distance entre le point actuel et le prochain point de la liste
    distance = getDistanceIndice(m,indicePointActuel, indice);
    
    //Sauvegarde de l'indice du point
    int indicePoint = indice;
    
    //Tant que l'on est pas à la fin du tableau
    while (indice != TailleTab-1) {
        
        //On passe au prochain point
        indice++;
        
        if(!isVisited(getPointIndice(m, indice))){
            
            //Distance entre le point actuel et le point d'après
            tmp = getDistanceIndice(m,indicePointActuel, indice);
            
            //Si le point d'après est plus près
            if (tmp<distance) {
                
                //On sauvegarde l'indice du point le plus proche
                indicePoint = indice;
                
                //On garde la distance entre p et le point le plus proche comme référence distance
                distance = tmp;
            }
        }
    }

    return indicePoint;
}


/**
 * \brief Parcour de la matrice, crée un ordre de parcours permettant d'effectuer une distance moindre,
 * recherche de point le plus proche.
 *
 * \param m matrice d'entrée qui permet d'obtenir la liste des points que l'on souhaite parcourir.
 * \return ordreDePassage[] tableau de sortie qui contiendra le nouveau parcours
 */
point *nearestNeighbour(matrice mIn){
    
    matrice m = cloneMatrice(mIn);
    int nombreDePoints = getDimensionMatrice(m);
    point *ordreDePassage = malloc(sizeof(point)*nombreDePoints);
        
    //Insertion du point d'origine
    ordreDePassage[0] = clone(getPointIndice(m, 0));
    markVisited(getPointIndice(m, 0));

    int indicePointActuel = 0;
    
    //Indice du tableau d'ordre de passage
    int indice = 1;
    
    //Tant que l'on est pas à la fin de la matrice
    while(indice<=nombreDePoints-1){
        
        indicePointActuel = PointLePlusProche(indicePointActuel,m);
        
        markVisited(getPointIndice(m, indicePointActuel));
        //Le point le plus proche du pointActuel est inséré
        ordreDePassage[indice] = clone(getPointIndice(m, indicePointActuel));
        
        // On passe à l'indice suivant
        indice++;
    }
    
    //On retourne au point d'origine
    //ordreDePassage[indice] = clone(ordreDePassage[0]);
    detruireMatrice(m);
    
    return ordreDePassage;
}


/**
 * \brief Fonction qui calcul la distance totale entre tous les points d'une liste
 *
 * \param m matrice d'entrée qui permet d'obtenir la liste des points que l'on souhaite parcourir.
 * \param points tableau contenants les points
 *
 * \return: la distance totale
 */
int overallDistance(matrice m, point *points)
{
    float sum = 0;
    int n = getDimensionMatrice(m);
    for(int i = 0; i < n; i++)
    {
        sum += getDistancePoint(m, points[i], points[(i+1)%n]);
    }
    //sum += getDistancePoint(m, points[n-1], points[0]);
    return (int)sum;
}

int overallDistanceVerbose(matrice m, point *points)
{
    float sum = 0;
    float tmp;
    int n = getDimensionMatrice(m);
    for(int i = 0; i < n; i++)
    {
        printf("Distance between :\n");
        afficherPoint(points[i]);
        afficherPoint(points[(i+1)%n]);
        tmp = getDistancePoint(m, points[i], points[(i+1)%n]);
        printf("= %f\n", tmp);
        sum += tmp;
    }
    //sum += getDistancePoint(m, points[n-1], points[0]);
    return (int)sum;
}



/**
 * \brief Fonction qui echange deux points passés en paramètres
 *
 * \param plist liste contenant les points
 * \param i premier point
 * \param j deuxième point
 */
/*fonction qui echange deux points passés en paramètres*/
void swap(point *plist, int i, int j)
{
    if(i != j)
    {
        point tmp;
        tmp = plist[i];
        plist[i] = plist[j];
        plist[j] = tmp;
    }
}
/**
 * \brief Fonction qui copie une liste de points 
 *
 * \param pIn tableau 1 de points
 * \param pOut tableau 2 de points
 * \param len taille 
 */
void copyList(point *pIn, point *pOut, int len)
{
    for(int i = 0; i < len; i++)
        pOut[i] = pIn[i];
}


/**
 * \brief Fonction qui copie une liste de points à partir d'un indice  
 *
 * \param pIn tableau 1 de points
 * \param pOut tableau 2 de points
 * \param start indice de début
 * \param end indice de fin
 */
void copyListIndice(point *pIn, point *pOut, int start, int end)
{
    int j = 0;
    for(int i = 0; i < end; i++)
        if(i >= start)
            pOut[j++] = pIn[i];
}


void deleteFromList(point *in, int length, point p)
{
    point tmp_list[length-1];
    int a = 0;
    int b = 0; 
    while(b < length-1)
    {
        if(!equals(in[a], p))
             tmp_list[b++] = in[a++];
        else
             a++;
    }
    copyList(tmp_list, in, length-1);
}

/*fonction brute force*/
void bruteForceRough(matrice m, point *pIn, int i, int n, int *min, point *pOut)
{
    int j;
    if(i == n)
    {
        int d = overallDistance(m, pIn);
        if( d < *min)
        {
            *min = d;
            copyList(pIn, pOut, n);
        }
    }
    else
    {
        for(j = i; j < n; j++)
        {
            swap(pIn, i, j);
            bruteForceRough(m, pIn, i+1, n, min, pOut);
            swap(pIn, i, j);
        }
    }

}

/**
 * \brief Fonction qui permet le calcul de la distance du Voyageur avec l'algorithme Brute Force
 *
 * \param m matrice d'entrée qui permet d'obtenir la liste des points que l'on souhaite parcourir.
 *
 * \return: la distance générale parcourue
 */

 //wrapper pour bruteForceRough
point *bruteForce(matrice m)
{
    int n = getDimensionMatrice(m);

    point pList[n];
    copyList(getTableauPointsMatrice(m), pList, n);

    point *pOut = malloc(sizeof(point) * n);
    //copyList(pList, pOut, n);

    int *min = malloc(sizeof(int));
    *min = overallDistance(m, pList);

    bruteForceRough(m, pList, 0, n, min, pOut);

    //copyList(pList, pOut, n);

    free(min);
    return pOut;
}
 
/**
 * \brief Fonction qui permet le calcul de la distance du Voyageur avec Prim
 *
 * \param mIn matrice d'entrée qui permet d'obtenir la liste des points que l'on souhaite parcourir.
 *
 * \return: TabVisite tableau qui contient les points ordonnés selon le parcours
 */

 point* prim(matrice mIn){
    
    
    matrice m = cloneMatrice(mIn);
    int dim = getDimensionMatrice(m);
    point* TabVisite = malloc(sizeof(point)*dim);
    int current = 0; //Indice du point courant
    int indicePointVisite[dim];
    int nbPointVisite = 1;
    int tmp = 0;
    int min = 32000;
    
    //Initatiliser le marquage des points sur non visités
    for(int i = 1;i<dim;i++)
        markNoVisited(getPointIndice(m, i));
    
    //Point d'origine visité
    markVisited(getPointIndice(m, 0));
    TabVisite[0] = getPointIndice(m,0);
    indicePointVisite[0] = 0;


    //Parcours
    //Tant qu'il reste des points à visité
    while(nbPointVisite < dim){
        
        //Pour tous les points visités
        //On cherche le point le plus proche de chaque point visité et on garde celui qui sera le plus economique (distance)
        for(int i = 0;i<nbPointVisite;i++){
            tmp = PointLePlusProche(indicePointVisite[i], m);
            if (min > getDistanceIndice(m, indicePointVisite[i], tmp)){
                min = getDistanceIndice(m, indicePointVisite[i], tmp);
                current = tmp;
            }
        }
        markVisited(getPointIndice(m, current));
        
        //Parcour stocke
        TabVisite[nbPointVisite] = getPointIndice(m,current);
       
        nbPointVisite++;
        indicePointVisite[nbPointVisite-1] = current;
        min = 32000; //Reinitialisation de min
        
    }
    //TabVisite[dim] = getPointIndice(m, 0);//Retour a l'origine
    detruireMatrice(m);
    return TabVisite;
}

/**
 * \brief Fonction qui permet le calcul de la distance du Voyageur par l'algorithme de Branch & Bound
 *
 * \param m matrice d'entrée qui permet d'obtenir la liste des points que l'on souhaite parcourir.
 *
 * \return: la distance générale parcourue
 */

point *branchBound(matrice m)
{
    point min_point;
    int n = getDimensionMatrice(m);
    int to, from, local_min, tmp_lb;
    matrice tmp_m;


    point in[n-1]; //liste des points qui restent
    copyListIndice(getTableauPointsMatrice(m), in, 1, n); 

    point *out = malloc(sizeof(point) * n); // parcours
    out[0] = getPointIndice(m, 0);

    for(int i = 0; i < n; i++) // = "branching"
    {
        local_min = 1000;
        from = getIndicePoint(m, out[i%n]);

        /*printf("Current list (in) : \n");
        afficherListeDesPoints(in, n-i); */

        for(int j = 0; j < n - i; j++) // = "bounding"
        {
            //from = point duquel on part, to = point sur lequel on arrive
            tmp_m = cloneMatrice(m);
            to = getIndicePoint(m, in[j]);
            markAsInfinite(tmp_m, to, from);
            tmp_lb = lowerBound(tmp_m);
            if(tmp_lb < local_min)
            {
                local_min = tmp_lb;
                min_point = in[j];
            }
            detruireMatrice(tmp_m);
        }

        out[i+1] = min_point; // on ajoute le point choisi à out
        deleteFromList(in, n - i, min_point); // et on le supprime de in
    }

    return out;

}
