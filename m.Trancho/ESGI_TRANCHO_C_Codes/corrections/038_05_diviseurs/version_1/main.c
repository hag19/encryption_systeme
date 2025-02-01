/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 38.
 */

/* Première proposition (traitement du premier hors boucle) : */
#include <stdio.h>
#include <stdlib.h>

int main() {
  int nombre;
  int i;
  /* Nous demandons la saisie d'un entier à l'utilisateur : */
  printf("Entrez un entier : ");
  scanf("%d", &nombre);
  printf("Liste des diviseurs de %d :\n", nombre);
  
  /* 1 divisera toujours notre nombre. */
  printf("1");
  /* On itère par l'entier i sur les entiers de 2 à nombre */
  for(i = 2; i <= nombre; ++i) {
    /* si i divise nombre, on l'affiche */
    if(nombre % i == 0) {
      printf(", %d", i);
    }
  }
  printf("\n");
  
  exit(EXIT_SUCCESS);
}