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
  struct {
    float x;
    float y;
  };
};

int main() {
  union Scalaire nombre;
  nombre.x = 42;
  nombre.y = 1337;
  printf("sizeof(Scalaire) : %lu\n", sizeof(union Scalaire));
  printf("entier :           %d\n", nombre.entier);
  printf("flottant :         %g\n", nombre.flottant);
  printf("flottantPrecis :   %g\n", nombre.flottantPrecis);
  printf("(x, y) :           (%g, %g)\n", nombre.x, nombre.y);
  exit(EXIT_SUCCESS);
}