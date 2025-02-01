/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 122.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/arraylist.h"
#include "../include/hashmap.h"
#include "../include/types.h"

#define TEST
#undef TEST

#ifdef TEST
#define CAPACITY 5
#define ELEMENTS 20
#endif

#define ADD_TO_HASH(tab, size, type, id) \
  liste = ArrayList_creer(TypeData##type(), size); \
  for(i = 0; i < size; ++i) ArrayList_ajouter(liste, tab + i); \
  HashMap_ajouter(map, keys + id, &liste);

int main() {
#ifdef TEST
  HashMap * map = HashMap_creer(TypeDataInt(), TypeDataInt(), CAPACITY);
  int vals[5] = {1, 17, 3, 42, 5};
  ArrayList * liste = ArrayList_creer_depuis_valeurs(TypeDataInt(), 5, vals + 0, vals + 1, vals + 2, vals + 3, vals + 4);
  long seed = time(NULL);
  int value;
  int count;
  int tmp;
  long i;
  srand(seed);
  for(i = 0; i < ELEMENTS; ++i) {
    value = rand() % ELEMENTS;
    count = 0;
    HashMap_rechercher(map, &value, &count);
    ++count;
    HashMap_ajouter(map, &value, &count);
  }
  HashMap_afficher(stdout, map);
  printf("\n");
  ArrayList_afficher(stdout, liste);
  printf("\n");
  HashMap_free(&map);
  ArrayList_free(&liste);
#else
  HashMap * map = HashMap_creer(TypeDataString(), TypeDataArrayList(), 100);
  float fvals[7] = {4.5, 13.37, 1.2, 8.1, 99.9, 4.2, 1.2};
  char * svals[2] = {"Hello", "ESGI"};
  int ivals[5] = {1, 17, 3, 42, 5};
  long lvals[3] = {5000000000, 30000000000, -42000000000};
  char cvals[4] = {'E', 'S', 'G', 'I'};
  char * keys[5] = {"a virgule", "texte", "entiers", "grands", "caracteres"};
  int i;
  ArrayList * liste = NULL;
  ADD_TO_HASH(fvals, 7, Float, 0);
  ADD_TO_HASH(svals, 2, String, 1);
  ADD_TO_HASH(ivals, 5, Int, 2);
  ADD_TO_HASH(lvals, 3, Long, 3);
  ADD_TO_HASH(cvals, 4, Char, 4);
  HashMap_afficher(stdout, map);
  printf("\n");
#endif
  exit(EXIT_SUCCESS);
}