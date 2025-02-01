/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 8.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  char car;
  /* créer un entier ent */
  int ent;
  /* mettre '4' dans car */
  car = '4';
  /* mettre 2 dans ent */
  ent = 2;
  /* afficher le caractère car et entier */
  printf("%c%d\n", car, ent);
  /* afficher l'entier correspondant à car */
  printf("%d\n", car);
  exit(EXIT_SUCCESS);
}