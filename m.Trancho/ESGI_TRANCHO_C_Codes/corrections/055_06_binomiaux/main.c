/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 55.
 */

#include <stdio.h>
#include <stdlib.h>

int binom(int n, int k) {
  if(k < 0 || k > n) return 0;
  if(k == 0 || k == n) return 1;
  return binom(n - 1, k - 1) + binom(n - 1, k);
}

int binom_fast(int n, int k) {
  if(k < 0 || k > n) return 0;
  if(k == 0 || k == n) return 1;
  int res = n;
  int i;
  for(i = 1; i < k; ++i) {
    res *= n - i;
    res /= (i + 1);
  }
  return res;
}

int main() {
  int n;
  printf("Entrez l'entier n : ");
  scanf("%d", &n);
  int i, k;
  for(i = 0; i <= n; ++i) {
    printf("%2d :", i);
    for(k = 0; k <= i; ++k) {
      printf(" %3d", binom_fast(i, k));
    }
    printf("\n");
  }
  exit(EXIT_SUCCESS);
}