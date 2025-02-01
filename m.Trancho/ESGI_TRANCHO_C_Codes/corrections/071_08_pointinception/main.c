/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 71.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  int valeur = 42;
  int * ptr = &valeur;
  int ** pptr = &ptr;
  int *** ppptr = &pptr;
  printf("valeur via valeur : %d\n", valeur);
  printf("valeur via ptr : %d\n", *ptr);
  printf("valeur via pptr : %d\n", **pptr);
  printf("valeur via ppptr : %d\n", ***ppptr);
  exit(EXIT_SUCCESS);
}