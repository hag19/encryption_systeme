#include <stdio.h>
#include <stdlib.h>

void print_values(/* TODO : type */ variables) {
  printf("values : [\n");
  for(; *variables; ++variables) {
    printf("\t0x%p : %d\n",
    /* TODO : afficher les éléments de variables : */
    /* adresse et valeur */);
  }
  printf("]\n");
}

int main() {
  int a = 1;
  int b = 2;
  int c = 3;
  int i = 0;
  /* TODO : type */ variables[] = {
    &i, &a, &b, &c, NULL
  };
  print_values(variables);
  a = 42;
  for(i = 0; variables[i] != NULL; ++i) {
    /* TODO : ajouter 1 à l'adresse pointée par variables[i] */
  }
  print_values(variables);
  /* TODO : Pourquoi a vaut 42 ? */
  exit(EXIT_SUCCESS);
}