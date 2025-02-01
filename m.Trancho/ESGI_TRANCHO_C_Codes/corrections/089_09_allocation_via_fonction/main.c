/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 89.
 */

#include <stdio.h>
#include <stdlib.h>

int alloc_tab(float *** tableau, int taille_first, int taille_second) {
  float * valeurs = NULL;
  int i, j;
  if((*tableau = (float **)malloc(taille_first * sizeof(float *))) == NULL) {
    return 0;
  }
  if((valeurs = (float *)malloc(taille_first * taille_second * sizeof(float))) == NULL) {
    free(*tableau);
    return 0;
  }
  for(i = 0; i < taille_first; ++i) {
    (*tableau)[i] = valeurs + (i * taille_second);
  }
  for(i = 0; i < taille_first; ++i) {
    for(j = 0; j < taille_second; ++j) {
      (*tableau)[i][j] = (float)(i + 1) / (j + 1);
    }
  }
  return 1;
}

void free_tab(float *** tableau) {
  if(tableau == NULL || *tableau == NULL) {
    return;
  }
  free(**tableau);
  free(*tableau);
  *tableau = NULL;
}

int main() {
  float ** tableau = NULL;
  int taille_first = 6, taille_second = 4;
  int i, j;
  if(! alloc_tab(&tableau, taille_first, taille_second)) {
    printf("Erreur allocation tableau : arrêt.\n");
    exit(EXIT_FAILURE);
  }
  for(i = 0; i < taille_first; ++i) {
    for(j = 0; j < taille_second; ++j) {
      if(j) printf(" ");
      printf("%.5f", tableau[i][j]);
    }
    printf("\n");
  }
  free_tab(&tableau);
  exit(EXIT_SUCCESS);
}