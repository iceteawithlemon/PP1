#ifndef FILES_H
#define FILES_H

#include <stdbool.h>

typedef int objet;

struct file;
typedef struct file *file;

void creerFile(file F, int taille);
objet valeur(file F);
bool fileVide(file F);
bool enfiler(file F, objet x);
void defiler(file F);

#endif