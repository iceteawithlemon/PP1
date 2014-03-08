//
//  Liste.c
//  ProjetPP1
//
//  Created by Benjamin Saint-Sever on 08/03/2014.
//  Copyright (c) 2014 Benjamin Saint-Sever. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "point.h"
#define ERROR -1

typedef struct element element;

struct element
{
    point valeur;
    struct element *pSuivant;
};

typedef element* list;



list ajouterEnTete(list liste, point pValeur)
{
    //Creation d'un élément
    element* nouvelElement = malloc(sizeof(element));
    
    //Initialisation Valeur
    nouvelElement->valeur = pValeur;
    
    //Adresse de l'element suivant
    nouvelElement->pSuivant = liste;

    //on retourne la liste pointant sur le premier élément
return nouvelElement;
}


list ajouterEnFin(list liste, point pValeur)
{
    //Creation d'un élément
    element* nouvelElement = malloc(sizeof(element));
    
    //Initialisation Valeur
    nouvelElement->valeur = pValeur;
    
    //l'élement suivant pointe sur NULL, c'est la fin
    nouvelElement->pSuivant = NULL;
    
    if(liste == NULL)
    {
        //Si la liste est vide on retourne le nouvel élément
        return nouvelElement;
    }
    else
    {
        //Sinon on parcourt la liste et on place l'élément créer en tant que dernier élément
        element* tmp=liste;
        while(tmp->pSuivant != NULL)
        {
            tmp = tmp->pSuivant;
        }
        tmp->pSuivant = nouvelElement;
        return liste;
    }
}

list rechercherElement(list liste, point pValeur)
{
    element *tmp=liste;
    //Tant que l'on est pas au dernier élément
    while(tmp != NULL)
    {
        if(tmp->valeur == pValeur)
        {
            //lorsque le point est trouvé en renvoi l'adresse de celui-ci
            return tmp;
        }
        tmp = tmp->pSuivant;
    }
    return NULL;
}

void afficherListe(list liste)
{
    element *tmp = liste;
    //Parcourt jusqu'a la fin de liste
    while(tmp != NULL)
    {
        
        afficherPoint(tmp->valeur);
        //on avance
        tmp = tmp->pSuivant;
    }
}


list supprimerElement(list liste, point pValeur)
{
    //Si la liste est vide est retourne NULL
    if(liste == NULL)
        return NULL;
    
    //Le Point est trouvé
    if(liste->valeur == pValeur)
    {
        //On garde l'adresse de l'élément suivant
        element* tmp = liste->pSuivant;
        
        //On supprime l'élément
        free(liste);
        
        //On retourne l'adresse de l'élement suivant
        return tmp;
    }//Le point n'est pas trouvé
    else 
    {
        //Par recursivité en cherche à l'élément suivant
        liste->pSuivant = supprimerElement(liste->pSuivant, pValeur);
        return liste;
    }
}

bool estVide(list liste)
{
    return (liste == NULL)? true : false;
}


point valeur(list liste)
{
    if(liste == NULL ){
        printf("Erreur de valeur\n");
    }
    return liste->valeur;
}

bool finListe(list liste){
    return (liste == NULL)? true : false;
}

//Fonction recursive
list effacerListe(list liste)
{
    if(liste == NULL)
        return NULL;
    else
    {
        //On efface l'élément et on retourne la suite de la liste
        element *tmp;
        tmp = liste->pSuivant;
        free(liste);
        return effacerListe(tmp);
    }
}
