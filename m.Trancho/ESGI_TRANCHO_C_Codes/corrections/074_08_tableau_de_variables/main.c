/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 74.
 */

#include <stdio.h>
#include <stdlib.h>

void print_values(int ** variables) {
  printf("values : [\n");
  for(; *variables; ++variables) {
    printf("\t0x%p : %d\n", *variables, **variables);
  }
  printf("]\n");
}

int main() {
  int a = 1;
  int b = 2;
  int c = 3;
  int i = 0;
  int * variables[] = {
    &i,
    &a,
    &b,
    &c,
    NULL
  };
  print_values(variables);
  a = 42;
  for(i = 0; variables[i] != NULL; ++i) {
    ++(*(variables[i]));
  }
  print_values(variables);
  /* Pourquoi a vaut 42 ? */
  /* Lors du parcours de boucle, l'adresse de i a été          */ 
  /* incrémentée par ++(*(variables[i])), ceci a fait sauter   */
  /* le cas i = 1.                                             */
  exit(EXIT_SUCCESS);
}