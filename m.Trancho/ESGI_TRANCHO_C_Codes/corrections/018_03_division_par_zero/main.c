/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 18.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  int x = 0;
  /* Alice avait un problème de parenthèses : */
  /* la multiplication est prioritaire, */
  /* ceci ne calculait pas (x - 1) ^ 2 / (x + 1) */
  int y = (x - 1) * (x - 1) / (x + 1);
  printf("f(%d) = %d\n", x, y);
  x = 1;
  y = (x - 1) * (x - 1) / (x + 1);
  printf("f(%d) = %d\n", x, y);
  x = 3;
  y = (x - 1) * (x - 1) / (x + 1);
  printf("f(%d) = %d\n", x, y);
  exit(EXIT_SUCCESS);
}