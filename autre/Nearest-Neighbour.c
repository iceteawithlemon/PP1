#include "point.h"
#include "ArbresBinaires.h"
#include "nearest_neighbour.h"

// En parametre le nombre de point

float nearestNeighbour (point t[],int n){

	file f = creerFile (n);	//file qui contiendra le chemin � parcourir

	enfiler (f,t[0]); 	//on met le premier point dans la file : ce sera notre point de d�part
	point c = t[0];		//servira de point de r�f�rence pour les tests suivants
	point h = t[0];		//on stock t[0] pour le calcul de la distance entre le dernier point visit� et le d�part
	
	int compt = 1;
	float a;
	int b=0;
	point t2[n];		//tableau qui regroupera les points visit�s
	int k=1;			//indice de t2
	t2[0]=t[0];			// on met t[0] comme point visit�


	do {

			

			if(!appartient(t2,t[b+1],n)){	//verifie si t[b+1] n'est pas un point visit�

				a= distanceEntreDeuxPoints(c,t[b+1]);			

				for(int j=b+1;j<n;j++){	//boucle qui sert � calculer la distance avec les autres points su tableau

					if(!appartient(t2,t[j],n)){	//verifie si t[j] est un point visit�

						if (a>=distanceEntreDeuxPoints(c,t[j])){	//test pour choisir la distance la plus courte

							a= distanceEntreDeuxPoints(c,t[j]);
							b= j;				//on stock l'indice du point le plus proche

						}

					}

				}

				enfiler(f,t[b]);		// on enfile le point le plus proche
				t2[k]=t[b];				//on met le point dans le tableau des points visit�s
				k++;
				echanger (c,t[b]);	//on met le nouveau point au d�but pour pouvoir refaire les tests pr�c�dents
				c=t[0];				// Probleme on risque de reprendre le point de depart !!??
				b=0;
			}
			compt ++;		

	}while(compt!=n);			// tant que l'on a pas pass� tous les points du tableau
	
	point t1[n+1];		//cr�ation d'un tableau de taille n+1 qui contiendra les points dans l'ordre qui nous donnerons le chemin � suivre
	enfiler(f,h);		// le retour au point de d�part

	for (int i=n+1;i>=0;i--){	//boucle pour remplir le tableau avec les points dans le bon ordre

		t1[i]= (valeur(f));
        defiler(f);
	}						//maintenant nous avons un tableau avec les points qui nous donnent le chemin � suivre

	float d=0;		//variable qui va nous servir pour le calcul de la distance du chemin

	for (int i=0; i<n; i++){	//calcul de la distance g�n�rale du chemin

		d += distanceEntreDeuxPoints(t1[i],t1[i+1]);
	}

	detruireFile(f);
	return d;		//on retourne le distance du chemin 

}



//Rajout de la longueur du tableau passe en parametre ( evite d'augmenter en complexite)

static bool appartient (point t[], point p, int longueurTableau){

	for(int i=0; i<longueurTableau ; i++){

		if (t[i]==p)

			return true;

	}

	return false;
}



static void echanger(point a, point b){
	point c;

	c=a;
	a=b;
	b=c;
}


int main (void){

point p1 = creerPoint(0,0);
point p2 = creerPoint(2,2);
point p3 = creerPoint(2,0);
point p4 = creerPoint(5,1);

point t[]={p1,p2,p3,p4}; //tableau comprenant les points crees precedement
int n=4;

nearestNeighbour (t, n);






}


