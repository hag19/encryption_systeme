/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 115.
 */

#ifndef DEF_HEADER_LISTE
#define DEF_HEADER_LISTE

#include <stdio.h>

typedef struct ArrayList ArrayList;
struct ArrayList;

ArrayList * ArrayList_creer(int capacite);

void ArrayList_free(ArrayList ** arraylist);

int ArrayList_ajouter(ArrayList * liste, int valeur);

void ArrayList_afficher(FILE * flow, const ArrayList * liste);

int ArrayList_compter(const ArrayList * liste, int valeur);

#endif