/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

void test() {
  variableDeMain = 10;
}

int main() {
  int variableDeMain = 42;
  printf("%d\n", variableDeMain);
  test();
  printf("%d\n", variableDeMain);
  exit(EXIT_SUCCESS);
}