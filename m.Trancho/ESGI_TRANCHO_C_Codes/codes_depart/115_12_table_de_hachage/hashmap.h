#ifndef DEF_HEADER_HASHMAP
#define DEF_HEADER_HASHMAP

#include <stdio.h>

/* Table de hachage */
typedef struct HashMap HashMap;
struct HashMap;

/* création d'une table de hachage */
HashMap * HashMap_creer(int capacite);

/* libération d'une table de hachage */
void HashMap_free(HashMap ** hashmap);

/* ajout de 1 à la valeur associée à key, affectation à 1 si non trouvée */
int HashMap_ajouter(HashMap * hashmap, int key);

/* affiche la table de hachage dans un flux flow */
void HashMap_afficher(FILE * flow, const HashMap * hashmap);

/* renvoie le nombre d'ajouts de la clé key (valeur associée) */
int HashMap_compter(const HashMap * hashmap, int key);

#endif