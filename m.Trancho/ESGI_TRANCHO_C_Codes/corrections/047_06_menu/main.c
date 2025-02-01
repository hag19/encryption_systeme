/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 47.
 */

#include <stdio.h>
#include <stdlib.h>

int menu() {
  /* À vous de jouer */
  int choix;
  do {
    printf("Menu : \n   1 - un truc\n   2 - un autre\n   3 - quitter\n---\nVotre choix : ");
    scanf("%d", &choix);
  } while (choix < 1 || choix > 3);
  return choix;
}

int main() {
  printf("%d, bien reçu.\n", menu());
  exit(EXIT_SUCCESS);
}