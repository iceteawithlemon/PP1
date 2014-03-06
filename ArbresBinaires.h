#ifndef ArbresBinaires_H
#define ArbresBinaires_H

# include <stdbool.h>

typedef struct cellule cellule;
typedef cellule *sommet;
typedef struct file *file;

extern file creerFile(int taille);
extern void detruireFile(file f);
extern void* valeur(file f);
extern bool fileVide(file f);
extern void enfiler(file f, void* x);
extern void defiler(file f);

extern int getValeur(sommet s);
extern sommet filsGauche(sommet s);
extern sommet filsDroit(sommet s);
extern sommet pere(sommet s);
extern bool estFeuille(sommet s);

extern sommet creerArbreBinaire(int racine);
extern void ajouterFilsGauche(sommet S, int x);
extern void ajouterFilsDroit(sommet S, int x);
extern void supprimerFilsGauche(sommet S);
extern void supprimerFilsDroit(sommet S);
extern void detruireArbreBinaire(sommet s);

extern sommet remplirTableauArbre(int tab[], int len);
extern void afficherArbre(sommet A, int mode);
extern int arbre2Tableau(sommet A, int *tab, int i);
extern int hauteurArbreBinaire(sommet s);
extern int tailleArbreBinaire(sommet A);
extern bool estComplet(sommet A);


#endif

