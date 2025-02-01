/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 12.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  long double value;
  printf("Entrez un réel : ");
  scanf("%Lf", &value);
  printf("La partie entière de %Lg est environ %.0Lf\n", value, value);
  exit(EXIT_SUCCESS);
}