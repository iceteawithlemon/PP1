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
    for(int i = start; i < end; i++)
        pOut[i] = pIn[i];
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
/*
void branchBound(matrice m, point *pList, int pas)
{
    int n = getDimensionMatrice(m);
    //printf("Dim: %d\n", n);
    int step = 0;
    int tmp;
    point pOutBranch[n];
    point pOutBrute[pas];
    pOutBranch[0] = pList[0];
    copyList(pList, pOutBrute, pas);
    //copyList(pList, pOut, n);
    int *min = malloc(sizeof(int));
    *min = overallDistance(m, pList);

    while(step < n)
    {
        //printf("Step: %d\n", step);
        //afficherPoint(pOutBranch[step]);
        tmp = (step + pas < n)? step + pas: n;
        bruteForceRough(m, pList, step, tmp, min, pOutBrute);
        step ++;
        pOutBranch[step] = pOutBrute[0];
        copyListIndice(pOutBranch, pList, 0, step);
        printf("Liste points: \n");
        afficherListeDesPoints(pOutBrute, pas);
        printf("\n");
    }
    free(min);
    copyList(pOutBranch, pList, n);
}*/

/*fonction brute force*/
void branchRough(matrice m, point *pIn, int i, int n, int *min, point *pOut)
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