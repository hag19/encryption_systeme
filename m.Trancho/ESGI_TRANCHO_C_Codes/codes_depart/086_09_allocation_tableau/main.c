#include <stdio.h>
#include <stdlib.h>

int main() {
  double * tableau = NULL;
  int taille;
  printf("Combien d'éléments ? ");
  scanf("%d", &taille);
  /* allouer 'tableau' initialisé par des valeurs à 0 de 'taille' donnée */
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
  exit(EXIT_SUCCESS);
}