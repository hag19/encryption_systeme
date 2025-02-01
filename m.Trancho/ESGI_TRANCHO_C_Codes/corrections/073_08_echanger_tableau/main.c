/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 73.
 */

#include <stdio.h>
#include <stdlib.h>

void echanger(int * first, int * second) {
  int tmp = *first;
  *first = *second;
  *second = tmp;
}

int main() {
  int tableau[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int indice_first = 2;
  int indice_second = 4;
  echanger(tableau + indice_first, tableau + indice_second);
  int i;
  printf("tableau : [");
  for(i = 0; i < 10; ++i) {
    if(i) printf(", ");
    printf("%d", *(tableau + i));
  }
  printf("]\n");
  exit(EXIT_SUCCESS);
}