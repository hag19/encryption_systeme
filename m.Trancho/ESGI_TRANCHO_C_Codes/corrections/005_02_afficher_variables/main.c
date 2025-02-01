/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 5.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  float reel = 13.37;
  char caractere = 'Z';
  long entier = 42000000000;
  
  printf("reel : %g\n", reel);
  printf("caractere : \'%c\'\n", caractere);
  printf("caractere : %d\n", caractere);
  printf("entier : %ld\n", entier);
  printf("entier : %lx\n", entier);
  exit(EXIT_SUCCESS);
}