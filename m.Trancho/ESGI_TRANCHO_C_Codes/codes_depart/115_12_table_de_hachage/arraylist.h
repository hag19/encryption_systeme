#ifndef DEF_HEADER_LISTE
#define DEF_HEADER_LISTE

#include <stdio.h>

/* Liste sous forme d'un tableau de valeurs */
typedef struct ArrayList ArrayList;
struct ArrayList;

/* création d'une liste */
ArrayList * ArrayList_creer(int capacite);

/* libération d'une liste */
void ArrayList_free(ArrayList ** arraylist);

/* ajout d'un élément dans la liste */
int ArrayList_ajouter(ArrayList * liste, int valeur);

/* affiche la liste dans un flux flow */
void ArrayList_afficher(FILE * flow, const ArrayList * liste);

/* compte le nombre d'occurrences d'une valeur dans la liste */
int ArrayList_compter(const ArrayList * liste, int valeur);

#endif