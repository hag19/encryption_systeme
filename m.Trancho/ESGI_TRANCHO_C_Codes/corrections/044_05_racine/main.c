/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 44.
 */

#include <stdio.h>
#include <stdlib.h>
#ifdef COMPARE
#include <math.h>
#endif
#include <time.h>

int main() {
  clock_t start, end;
  double x;
  double target;
  printf("Entrez un réel : ");
  scanf("%lf", &target);
  start = clock();
  x = target / 2.;
  int i;
  for(i = 0; i < 200; ++i) {
    x = (x * x + target) / (2 * x);
  }
  end = clock();
  printf("La racine carré de %g est %.16f / %g (en %.6f s)\n", target, x, x, (double)(end - start) / CLOCKS_PER_SEC);
#ifdef COMPARE
  start = clock();
  x = sqrt(target);
  end = clock();
  printf("La racine carré de %g est %.16f / %g (en %.6f s) (d'après math)\n", target, x, x, (double)(end - start) / CLOCKS_PER_SEC);
#endif
  exit(EXIT_SUCCESS);
}