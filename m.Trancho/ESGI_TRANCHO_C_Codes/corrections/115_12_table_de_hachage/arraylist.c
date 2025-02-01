/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 115.
 */

#include "arraylist.h"

#include <stdlib.h>

struct ArrayList {
  int * data;
  int taille;
  int capacite;
};

ArrayList * ArrayList_creer(int capacite) {
  ArrayList * res = NULL;
  if((res = (ArrayList *)malloc(sizeof(ArrayList))) == NULL) {
    return NULL;
  }
  if(capacite > 0) {
    if((res->data = (int *)malloc(capacite * sizeof(int))) 
        == NULL) {
      free(res);
      return NULL;
    }
  }
  res->capacite = capacite;
  res->taille = 0;
  return res;
}

void ArrayList_free(ArrayList ** arraylist) {
  if(arraylist == NULL || *arraylist == NULL) {
    return;
  }
  if((*arraylist)->data != NULL) {
    free((*arraylist)->data);
  }
  free(*arraylist);
  *arraylist = NULL;
}

static int ArrayList_update_capacity(ArrayList * liste) {
  if(liste->taille < liste->capacite) {
    return 1;
  }
  int * tmp = NULL;
  int newCap = liste->capacite * 2 + 10;
  if((tmp = (int *)realloc(liste->data, newCap * sizeof(int))) == NULL) {
    return 0;
  }
  liste->data = tmp;
  liste->capacite = newCap;
  return 1;
}

int ArrayList_ajouter(ArrayList * liste, int valeur) {
  if(! ArrayList_update_capacity(liste)) {
    return 0;
  }
  liste->data[liste->taille] = valeur;
  ++(liste->taille);
  return 1;
}

void ArrayList_afficher(FILE * flow, const ArrayList * liste) {
  int i;
  fprintf(flow, "ArrayList<int> : [");
  for(i = 0; i < liste->taille; ++i) {
    if(i) fprintf(flow, ", ");
    fprintf(flow, "%d", liste->data[i]);
  }
  fprintf(flow, "]\n");
}

int ArrayList_compter(const ArrayList * liste, int valeur) {
  int count = 0;
  int i;
  for(i = 0; i < liste->taille; ++i) {
    if(liste->data[i] == valeur)
      ++count;
  }
  return count;
}