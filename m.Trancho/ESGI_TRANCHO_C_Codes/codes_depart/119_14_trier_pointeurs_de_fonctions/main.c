#include <stdio.h>
#include <stdlib.h>

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

int fcmp(float first(float x), float second(float x)) {
  return first(x) - second(x);
}

int main() {
  float fonctions(float x)[] = {
    carre,
    cube,
    inverse,
    oppose
  };
  float targets[] = {
    -2.f,
    -0.5f,
    0.5f,
    2.f
  };
  int i, j;
  for(i = 0; i < 4; ++i) {
    qsort(fonctions(targets[i]), sizeof(float f(float x)), 4, fcmp);
    printf("for %g :\n", targets[i]);
    for(j = 0; j < 4; ++j) {
      printf(" - %s(%g) = %g\n", fonctions(targets[i])[j].name, targets[i], fonctions(targets[i])[j]);
    }
  }
  exit(EXIT_SUCCESS);
}