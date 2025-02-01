/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 60.
 */

#include <stdio.h>
#include <stdlib.h>

void afficher_tableau(int tableau[], int taille) {
  int i;
  printf("[");
  for(i = 0; i < taille; ++i) {
    if(i) printf(", ");
    printf("%d", tableau[i]);
  }
  printf("]\n");
}

int main() {
  const int taille = 5;
  int tableau[taille];
  int i;
  printf("Saisir %d valeurs : ", taille);
  for(i = 0; i < taille; ++i) {
    scanf("%d", &tableau[i]);
  }
  afficher_tableau(tableau, taille);
  exit(EXIT_SUCCESS);
}