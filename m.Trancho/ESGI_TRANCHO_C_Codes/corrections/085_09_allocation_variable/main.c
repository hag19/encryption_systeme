/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 85.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  int * variable = NULL;
  variable = (int *)malloc(sizeof(int));
  if(variable == NULL) {
    printf("Erreur allocation : arrêt.\n");
    exit(EXIT_FAILURE);
  }
  *variable = 42;
  printf("%d\n", *variable);
  free(variable);
  variable = NULL;
  exit(EXIT_SUCCESS);
}