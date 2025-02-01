#include <stdio.h>
#include <stdlib.h>

void echanger(/* TODO : arguments à échanger */) {
  /* TODO : code pour échanger valeurs */
}

int main() {
  /* interdiction d'accéder à un élément par tableau[indice] */
  /* interdiction d'accéder à une adresse par &tableau[indice] */
  /* TODO : utiliser la version pointeur : */
  int tableau[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int indice_first = 2;
  int indice_second = 4;
  echanger(/* tableau à indice_first */, /* tableau à indice_second */);
  int i;
  printf("tableau : [");
  for(i = 0; i < 10; ++i) {
    if(i) printf(", ");
    printf("%d", /* tableau à i */);
  }
  printf("]\n");
  exit(EXIT_SUCCESS);
}