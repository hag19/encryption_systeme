/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 52.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long puissance(long a, long n) {
  long res = 1;
  long i;
  for(i = 0; i < n; ++i) {
    res *= a;
  }
  return res;
}

long puissance_rapide(long a, long n) {
  long res = 1;
  while(n > 0) {
    if(n % 2 == 1) {
      res = res * a;
    }
    a *= a;
    n /= 2;
  }
  return res;
}

unsigned long puissance_modulo(unsigned long a, unsigned long n, unsigned long p) {
  unsigned long res = 1;
  unsigned long i;
  for(i = 0; i < n; ++i) {
    res = (res * a) % p;
  }
  return res;
}

unsigned long puissance_rapide_modulo(unsigned long a, unsigned long n, unsigned long p) {
  unsigned long res = 1;
  while(n > 0) {
    if(n % 2 == 1) {
      res = (res * a) % p;
    }
    a = (a * a) % p;
    n /= 2;
  }
  return res;
}

int main() {
  printf("3 ** 5 = %ld\n", puissance(3, 5));
  printf("3 ** 5 = %ld\n", puissance_rapide(3, 5));
  printf("3 ** 5 = %ld\n", puissance_modulo(3, 6, 7));
  printf("3 ** 5 = %ld\n", puissance_rapide_modulo(3, 6, 7));
  clock_t start, end;
  unsigned long a = 42;
  unsigned long n = 2460320538;
  unsigned long p = 4285404239;
  unsigned long res;
  start = clock();
  res = puissance_modulo(a, n, p);
  end = clock();
  printf("puissance_modulo(%lu, %lu, %lu) = %lu, temps : %g s\n", a, n, p, res, (double)(end - start) / CLOCKS_PER_SEC);
  start = clock();
  res = puissance_rapide_modulo(a, n, p);
  end = clock();
  printf("puissance_rapide_modulo(%lu, %lu, %lu) = %lu, temps : %g s\n", a, n, p, res, (double)(end - start) / CLOCKS_PER_SEC);
  exit(EXIT_SUCCESS);
}