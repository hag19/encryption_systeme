/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 54.
 */

#include <stdio.h>
#include <stdlib.h>
#ifdef COMPARE
#include <math.h>
#endif
#include <time.h>

double equation(double x, double target) {
  return x * x - target;
}

double dicho_sqrt(double x) {
  if(((x > 0) ? x : -x) < 1e-30) {
    return 0.;
  }
  double start = 0;
  double end = (x > 1) ? x : 1;
  double mid;
  int i;
  for(i = 0; i < 256; ++i) {
    mid = 0.5 * (start + end);
    if(equation(start, x) * equation(mid, x) < 0) {
      end = mid;
    } else if(equation(end, x) * equation(mid, x) < 0) {
      start = mid;
    } else {
      return mid;
    }
  }
  return mid;
}

int main() {
  clock_t start, end;
  double x;
  double target;
  printf("Entrez un réel : ");
  scanf("%lf", &target);
  start = clock();
  x = dicho_sqrt(target);
  end = clock();
  printf("La racine carré de %g est %.16f (en %.6f s)\n", target, x, (double)(end - start) / CLOCKS_PER_SEC);
#ifdef COMPARE
  start = clock();
  x = sqrt(target);
  end = clock();
  printf("La racine carré de %g est %.16f (en %.6f s) (d'après math)\n", target, x, (double)(end - start) / CLOCKS_PER_SEC);
#endif
  exit(EXIT_SUCCESS);
}