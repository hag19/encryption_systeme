/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 20.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  double resultat = 1.;
  float ajout = 1e-9;
  printf("resultat = %.15f\n", resultat);
  printf("on ajoute %.15f\n", ajout);
  resultat += ajout;
  printf("resultat = %.15f\n", resultat);
  /* Pourquoi resultat ne change pas ?                         */
  /* L'ajout d'une valeur trop petite peut ne pas être pris en */
  /* compte à cause de l'approximation des nombres flottants.  */
  /* Une solution est de prendre un type plus précis : double. */
  exit(EXIT_SUCCESS);
}