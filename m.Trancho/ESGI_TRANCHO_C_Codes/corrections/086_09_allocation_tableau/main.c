/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 86.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  double * tableau = NULL;
  int taille;
  printf("Combien d'éléments ? ");
  scanf("%d", &taille);
  if((tableau = (double *)calloc(taille, sizeof(double))) == NULL) {
    printf("Erreur d'allocation de %d éléments : arrêt.\n", taille);
    exit(EXIT_FAILURE);
  }
  int i;
  printf("Entrez leurs valeurs : ");
  for(i = 0; i < taille; ++i) {
    scanf("%lf", tableau + i);
  }
  printf("Bien vos éléments sont notés : [");
  for(i = 0; i < taille; ++i) {
    if(i) printf(", ");
    printf("%g", tableau[i]);
  }
  printf("]\n");
  free(tableau);
  tableau = NULL;
  exit(EXIT_SUCCESS);
}