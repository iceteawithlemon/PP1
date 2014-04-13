#include "point.h"
#include <stdlib.h>
#include "matrice.h"

/*
 * Description: Cherche dans la matrice quel est le point le plus proche du point indiqué par l'indice,
 * cette fonction utilise la fonction getDistanceIndice() permettant de connaitre la distance entre deux points.
 *
 * Parametres: 
 * - indicePointActuel correpond à l'indice du point actuel, permettant l'accès à ce point.
 * - m matrice contenant tous les points
 *
 * Retour: indice du point le plus proche du point actuel
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
    markVisited(getPointIndice(m, indicePoint));
    return indicePoint;
}


/*
 * Description: Parcour de la matrice, crée un ordre de parcour permettant d'effectuer une distance moindre,
 * recherche de point le plus proche.
 *
 * Parametres:
 * - m matrice d'entrée qui permet d'obtenir la liste des points que l'on souhaite parcourir.
 * - ordreDePassage[] tableau de sortie qui contiendra le nouveau parcour
 *
 */
void nearestNeighbour(matrice m,point ordreDePassage[]){
    
    int nombreDePoints = getDimensionMatrice(m);
        
    //Insertion du point d'origine
    ordreDePassage[0] = clone(getPointIndice(m, 0));
    //Marquage du point visité
    markVisited(getPointIndice(m, 0));
    
    //On defini un point qui sera l'intermédiaire
    int indicePointActuel = 0;
    
    //Indice du tableau d'ordre de passage
    int indice = 1;
    
    //Tant que l'on est pas à la fin de la matrice
    while(indice<=nombreDePoints-1){
        
        indicePointActuel = PointLePlusProche(indicePointActuel,m);
        
        //Le point le plus proche du pointActuel est inséré
        ordreDePassage[indice] = clone(getPointIndice(m, indicePointActuel));
        
        // On passe à l'indice suivant
        indice++;
    }
    
    //On retourne au point d'origine
    ordreDePassage[indice] = clone(ordreDePassage[0]);
    
}

/*fonction qui calcul la distance totale entre tous les points d'un liste */
int overallDistance(matrice m, point *points)
{
    float sum = 0;
    int n = getDimensionMatrice(m);
    for(int i = 0; i < n-1; i++)
    {

        sum += getDistancePoint(m, points[i], points[i+1]);
    }
    return (int)sum;
}


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

/*fonction qui copie une liste de points */
void copyList(point *pIn, point *pOut, int len)
{
    for(int i = 0; i < len; i++)
        pOut[i] = pIn[i];
}

/*fonction qui copie une liste de points à partir d'un indice */
void copyListIndice(point *pIn, point *pOut, int start, int end)
{
    int j = 0;
    for(int i = 0; i < end; i++)
        if(i >= start)
            pOut[j++] = pIn[i];
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

//wrapper pour bruteForceRough
void bruteForce(matrice m, point *pList)
{
    int n = getDimensionMatrice(m);
    point pOut[n];
    copyList(pList, pOut, n);
    int *min = malloc(sizeof(int));
    *min = overallDistance(m, pList);
    bruteForceRough(m, pList, 0, n, min, pOut);
    copyList(pOut, pList, n);
    free(min);
}
 
/*void branchBound(matrice m, point *in, int len, point *out)
{
    //printf("len: %d\n", len);
    point tmp_p = in[0];
    int n = getDimensionMatrice(m);

    if(len < n)
    {
        int i, j;
        int tmp_lb;
        int min_lb = 1000; //abitrary value
        for(int k = 0; k < (n - len); k++)
        {
            if(!isVisited(in[k]))
            {
                matrice tmp_m = cloneMatrice(m);
                //i = point duquel on part, j = point sur lequel on arrive
                i = getIndicePoint(m, in[k]);
                j = getIndicePoint(m, out[len]);
                //i = getIndicePoint(m, in[k]);
                markAsInfinite(tmp_m, i, j);
                tmp_lb = lowerBound(tmp_m);
                if(tmp_lb < min_lb)
                {
                    min_lb = tmp_lb;
                    tmp_p = in[k];
                }
            //afficherMatrice(tmp_m);
                detruireMatrice(tmp_m);

            }
        }
        printf("Best min: \n");
        afficherPoint(tmp_p);
        printf("Min: %d\n", min_lb);

        markVisited(tmp_p);
        out[len++] = tmp_p;
        
        deleteFromList(in, n-len+1, tmp_p);

        //printf("in list: \n");
        //afficherListeDesPoints(in, n-len);

         printf("In: \n");
        afficherListeDesPoints(in, n-len);

        printf("Out: \n");
        afficherListeDesPoints(out, len);

        branchBound(m, in, len, out);
    }

}*/

void prim(matrice m,point* TabVisite){
    
    int dim = getDimensionMatrice(m);
    int current = 0; //Indice du point courant
    
    //Initatiliser le marquage des points sur non visités
    for(int i = 1;i<dim;i++)
        markNoVisited(getPointIndice(m, i));
    
    //Point d'origine visité
    markVisited(getPointIndice(m, 0));
    TabVisite[0] = getPointIndice(m,0);
    int nbPointVisite = 1;
    int tmp = 0;
    int min = 32000;
    //Parcours
    while(nbPointVisite < dim){
        for(int i = 1;i<=nbPointVisite;i++){
            tmp = PointLePlusProche(current, m);
            if (min > getDistanceIndice(m, i, tmp)){
                min = getDistanceIndice(m, i, tmp);
                current = tmp;
            }
        }
        markVisited(getPointIndice(m, current));
        TabVisite[nbPointVisite] = getPointIndice(m,current);
        nbPointVisite++;
    }
    TabVisite[dim] = getPointIndice(m, 0);
    
}

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

    for(int i = 0; i < n-1; i++) // = "branching"
    {
        local_min = 1000;
        from = getIndicePoint(m, out[i]);

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