/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 72.
 */

/* Optimisation de l'allocation dynamique : */
#include <stdio.h>
#include <stdlib.h>

int main() {
  const int ajouts = 1000000000;
  int * liste = NULL;
  int capacite = 0;
  int taille = 0;
  int i;
  for(i = 0; i < ajouts; ++i) {
    if(taille >= capacite) {
      capacite = capacite * 2 + 10;
      if((liste = (int *)realloc(liste, sizeof(int) * capacite)) == NULL) {
        printf("Erreur allocation.\n");
        exit(EXIT_FAILURE);
      }
    }
    liste[taille++] = i;
  }
  
  /*printf("liste : [");
  for(i = 0; i < taille; ++i) {
    if(i) printf(", ");
    if(i == 5) {
    printf("... ");
    i = ajouts - 5;
    continue;
    }
    printf("%d", liste[i]);
  }
  printf("]\n");*/
  free(liste);
  liste = NULL;
  exit(EXIT_SUCCESS);
}