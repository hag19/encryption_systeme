/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

union Scalaire {
  int entier;
  float flottant;
  double flottantPrecis;
};

int main() {
  union Scalaire nombre;
  nombre.entier = 42;
  printf("sizeof(Scalaire) : %lu\n", sizeof(union Scalaire));
  printf("entier :           %d\n", nombre.entier);
  printf("flottant :         %g\n", nombre.flottant);
  printf("flottantPrecis :   %g\n", nombre.flottantPrecis);
  nombre.flottant = 42;
  printf("entier :           %d\n", nombre.entier);
  printf("flottant :         %g\n", nombre.flottant);
  printf("flottantPrecis :   %g\n", nombre.flottantPrecis);
  nombre.flottantPrecis = 42;
  printf("entier :           %d\n", nombre.entier);
  printf("flottant :         %g\n", nombre.flottant);
  printf("flottantPrecis :   %g\n", nombre.flottantPrecis);
  exit(EXIT_SUCCESS);
}