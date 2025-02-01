/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 87.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  float ** tableau = NULL;
  int taille_first = 6, taille_second = 4;
  int i, j;
  if((tableau = (float **)malloc(taille_first * sizeof(float *))) == NULL) {
    printf("Erreur allocation première dimension : arrêt.\n");
    exit(EXIT_FAILURE);
  }
  for(i = 0; i < taille_first; ++i) {
    if((tableau[i] = (float *)malloc(taille_second * sizeof(float))) == NULL) {
      printf("Erreur allocation seconde dimension indice %d :"
        " arrêt.\n", i);
      for(--i; i >= 0; --i) {
        free(tableau[i]);
      }
      free(tableau);
      exit(EXIT_FAILURE);
    }
  }
  for(i = 0; i < taille_first; ++i) {
    for(j = 0; j < taille_second; ++j) {
      tableau[i][j] = (float)(i + 1) / (j + 1);
    }
  }
  for(i = 0; i < taille_first; ++i) {
    for(j = 0; j < taille_second; ++j) {
      if(j) printf(" ");
      printf("%.5f", tableau[i][j]);
    }
    printf("\n");
  }
  for(i = 0; i < taille_first; ++i) {
    free(tableau[i]);
  }
  free(tableau);
  tableau = NULL;
  exit(EXIT_SUCCESS);
}