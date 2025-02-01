/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 122.
 */

#ifndef DEF_HEADER_HASHMAP
#define DEF_HEADER_HASHMAP

#include <stdio.h>
#include "type_data.h"

typedef struct HashMap HashMap;
struct HashMap;

HashMap * HashMap_creer(TypeData keyType, TypeData valueType, int capacite);

void HashMap_free(HashMap ** hashmap);

int HashMap_ajouter(HashMap * hashmap, const void * key, const void * valeur);

void HashMap_afficher(FILE * flow, const HashMap * hashmap);

int HashMap_rechercher(const HashMap * hashmap, const void * valeur, void * res);

#endif