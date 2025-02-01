/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 38.
 */

/* Seconde proposition (tout traité dans la boucle) : */
#include <stdio.h>
#include <stdlib.h>

int main() {
  int nombre;
  int i;
  /* Nous demandons la saisie d'un entier à l'utilisateur : */
  printf("Entrez un entier : ");
  scanf("%d", &nombre);
  printf("Liste des diviseurs de %d :\n", nombre);
  
  for(i = 1; i <= nombre; ++i) {
    if(nombre % i == 0) {
      if(i > 1) {
        printf(", ");
      }
      printf("%d", i);
    }
  }
  printf("\n");
  
  exit(EXIT_SUCCESS);
}