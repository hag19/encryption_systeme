/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 115.
 */

#ifndef DEF_HEADER_HASHMAP
#define DEF_HEADER_HASHMAP

#include <stdio.h>

typedef struct HashMap HashMap;
struct HashMap;

HashMap * HashMap_creer(int capacite);

void HashMap_free(HashMap ** hashmap);

int HashMap_ajouter(HashMap * hashmap, int valeur);

void HashMap_afficher(FILE * flow, const HashMap * hashmap);

int HashMap_compter(const HashMap * hashmap, int valeur);

#endif