/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int fonction_min(int a, int b) {
  return (a < b) ? a : b;
}

#define macro_min(a, b) ((a) < (b)) ? (a) : (b)

int main() {
  int v, a, b;
  v = fonction_min(a = getchar() - '0', b = getchar() - '0');
  printf("fonction_min(%d, %d) = %d\n", a, b, v);
  v = macro_min(a = getchar() - '0', b = getchar() - '0');
  printf("macro_min(%d, %d) = %d\n", a, b, v);
  exit(EXIT_SUCCESS);
}