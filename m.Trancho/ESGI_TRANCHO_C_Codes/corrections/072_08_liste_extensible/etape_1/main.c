/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 72.
 */

/* Correction des fuites de mémoire : */
#include <stdio.h>
#include <stdlib.h>

int main() {
  const int ajouts = 10000;
  int * liste = malloc(sizeof(int));
  int * nouvelle_liste = NULL;
  int taille = 0;
  int i;
  int j;
  for(i = 0; i < ajouts; ++i) {
    liste[taille++] = i;
    nouvelle_liste = malloc(sizeof(int) * (taille + 1));
    for(j = 0; j < taille; ++j) {
      nouvelle_liste[j] = liste[j];
    }
    /* L'affectation de liste ne libère pas la plage           */
    /* précédemment référencée.                                */
    free(liste);
    liste = nouvelle_liste;
  }
  printf("liste : [");
  for(i = 0; i < taille; ++i) {
    if(i) printf(", ");
    printf("%d", liste[i]);
  }
  printf("]\n");
  free(liste);
  exit(EXIT_SUCCESS);
}