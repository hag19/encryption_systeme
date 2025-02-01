/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 83.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int arguments_count, char * arguments_values[]) {
  int i;
  for(i = 0; i < arguments_count; ++i) {
    printf("%d : %s\n", i, arguments_values[i]);
  }
  exit(EXIT_SUCCESS);
}