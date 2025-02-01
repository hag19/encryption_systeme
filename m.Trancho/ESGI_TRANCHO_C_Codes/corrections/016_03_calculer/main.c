/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 16.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  float first, second;
  printf("Entrez deux réels : ");
  scanf("%f %f", &first, &second);

  printf("%g + %g = %g\n", first, second, first + second);
  printf("%g - %g = %g\n", first, second, first - second);
  printf("%g * %g = %g\n", first, second, first * second);
  
  exit(EXIT_SUCCESS);
}