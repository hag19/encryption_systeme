/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 72.
 */

/* Optimisation et remplacement de code non pertinent : */
#include <stdio.h>
#include <stdlib.h>

int main() {
  const int ajouts = 1000000000;
  int * liste = malloc(sizeof(int));
  int taille = 0;
  int i;
  for(i = 0; i < ajouts; ++i) {
    liste[taille++] = i;
    if((liste = (int *)realloc(liste, sizeof(int) * (taille + 1))) == NULL) {
      printf("Erreur allocation.\n");
      exit(EXIT_FAILURE);
    }
  }
  /* L'affichage n'est plus pertinent ici. */
  /*printf("liste : [");
  for(i = 0; i < taille; ++i) {
    if(i) printf(", ");
    printf("%d", liste[i]);
  }
  printf("]\n");*/
  free(liste);
  exit(EXIT_SUCCESS);
}