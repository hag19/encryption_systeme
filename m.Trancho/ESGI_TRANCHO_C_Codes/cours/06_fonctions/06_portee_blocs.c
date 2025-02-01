/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  int variable = 10;
  printf("%p : %d\n", &variable, variable);
  if(variable == 10) {
    int variable = 42;
    printf("%p : %d\n", &variable, variable);
  }
  printf("%p : %d\n", &variable, variable);
  {
    int variable = 1337;
    printf("%p : %d\n", &variable, variable);
  }
  printf("%p : %d\n", &variable, variable);
  exit(EXIT_SUCCESS);
}