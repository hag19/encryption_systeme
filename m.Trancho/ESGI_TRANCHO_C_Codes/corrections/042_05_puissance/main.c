/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 42.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
  int n;
  unsigned long value;
  unsigned long result = 1;
  printf("Entrez un entier : ");
  scanf("%lu", &value);
  printf("Entrez un exponsant : ");
  scanf("%d", &n);
  if(n * log(value) >= (8 * sizeof(long) - 0.1) * log(2)) {
    printf("Cette exponentiation n'est pas assez triviale pour ce programme (le résultat doit être sous 2 puissance 64)\n");
    exit(EXIT_FAILURE);
  } else if(n < 0) {
    result = 0;
  }
  printf("%lu puissance %d = ", value, n);
  for(; n > 0; --n) {
    result *= value;
  }
  printf("%lu\n", result);
  exit(EXIT_SUCCESS);
}