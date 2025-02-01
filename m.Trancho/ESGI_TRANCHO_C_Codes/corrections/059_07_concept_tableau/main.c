/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 59.
 */

#include <stdio.h>
#include <stdlib.h>

void afficher_tableau(int tableau[]) {
  int i;
  printf("[");
  for(i = 0; tableau[i] >= 0; ++i) {
    if(i) printf(", ");
    printf("%d", tableau[i]);
  }
  printf("]\n");
}

int main() {
  int tableau[] = {1, 2, 3, 4, 5, -1};
  int indice;
  int valeur;
  afficher_tableau(tableau);
  printf("Quel indice affecter ? ");
  scanf("%d", &indice);
  printf("Pour quelle valeur ? ");
  scanf("%d", &valeur);
  tableau[indice] = valeur;
  afficher_tableau(tableau);
  exit(EXIT_SUCCESS);
}