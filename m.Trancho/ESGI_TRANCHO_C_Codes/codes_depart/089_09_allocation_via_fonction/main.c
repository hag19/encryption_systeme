#include <stdio.h>
#include <stdlib.h>

int alloc_tab(float *** tableau, int taille_first, int taille_second) {
  /* TODO : allouer tableau et initialiser ses valeurs à (float)(i + 1) / (j + 1) */
  return 1;
}

void free_tab(float *** tableau) {
  /* TODO : libérer tableau (sans fournir ses dimensions) */
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