/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

double moyenne(int nombre, ...) {
  double somme = 0;
  int i;
  va_list ap;
  va_start(ap, nombre);
  for(i = 0; i < nombre; ++i) {
    somme += va_arg(ap, double);
  }
  va_end(ap);
  if(nombre)
    somme /= nombre;
  return somme;
}

int main() {
  printf("%g\n", moyenne(3, 10., 11., 13.));
  exit(EXIT_SUCCESS);
}