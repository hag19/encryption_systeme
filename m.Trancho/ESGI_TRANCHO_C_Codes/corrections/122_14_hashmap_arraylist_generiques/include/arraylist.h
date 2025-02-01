/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 122.
 */

#ifndef DEF_HEADER_LISTE
#define DEF_HEADER_LISTE

#include <stdio.h>
#include "type_data.h"

typedef struct ArrayList ArrayList;
struct ArrayList;

ArrayList * ArrayList_creer(TypeData type, int capacite);

ArrayList * ArrayList_creer_depuis_valeurs(TypeData type, int capacite, ...);

void ArrayList_free(ArrayList ** arraylist);

int ArrayList_ajouter(ArrayList * liste, const void * valeur);

void ArrayList_afficher(FILE * flow, const ArrayList * liste);

int ArrayList_compter(const ArrayList * liste, const void * valeur);

TypeData TypeDataArrayList();

#endif