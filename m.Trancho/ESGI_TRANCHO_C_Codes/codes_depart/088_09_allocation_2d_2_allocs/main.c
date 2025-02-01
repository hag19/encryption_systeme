#include <stdio.h>
#include <stdlib.h>

int main() {
  float ** tableau = NULL;
  float * valeurs = NULL;
  int taille_first = 6, taille_second = 4;
  int i, j;
  /* TODO : allouer dynamiquement tableau[taille_first][taille_second] */
  /* TODO : allouer dynamiquement valeurs[taille_first * taille_second] */
  /* TODO : relier les deux tableaux */
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
  exit(EXIT_SUCCESS);
}