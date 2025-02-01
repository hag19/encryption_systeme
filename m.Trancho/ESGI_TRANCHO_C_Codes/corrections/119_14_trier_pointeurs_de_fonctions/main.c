/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 119.
 */

#include <stdio.h>
#include <stdlib.h>

#define ADDF(f) {f, #f}

typedef struct FName FName;
struct FName {
  float (*f)(float);
  char * name;
};

float carre(float x) {
  return x * x;
}

float cube(float x) {
  return x * x * x;
}

float inverse(float x) {
  return 1.f / x;
}

float oppose(float x) {
  return -x;
}

int fcmp(FName * first, FName * second, float * target) {
  float d = first->f(*target) - second->f(*target);
  if(d < 0) return -1;
  else if(d > 0) return 1;
  return 0;
}

int main() {
  FName fonctions[] = {
    ADDF(carre),
    ADDF(cube),
    ADDF(inverse),
    ADDF(oppose),
    ADDF(NULL)
  };
  float targets[] = {
    -2.f,
    -0.5f,
    0.5f,
    2.f
  };
  int i, j;
  for(i = 0; i < 4; ++i) {
    qsort_r(fonctions, 4, sizeof(FName), fcmp, targets + i);
    printf("for %g :\n", targets[i]);
    for(j = 0; j < 4; ++j) {
      printf(" - %s(%g) = %g\n", fonctions[j].name, targets[i], fonctions[j].f(targets[i]));
    }
  }
  exit(EXIT_SUCCESS);
}