/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 7.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  unsigned long entier;
  printf("Entrez un entier : ");
  scanf("%lu", &entier);
  printf("%lu = 0x%016lX\n", entier, entier);
  exit(EXIT_SUCCESS);
}