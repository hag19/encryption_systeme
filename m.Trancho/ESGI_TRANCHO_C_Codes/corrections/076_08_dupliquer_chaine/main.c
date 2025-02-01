/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 76.
 */

#include <stdio.h>
#include <stdlib.h>

void chaine_double(char * chaine) {
  char * aux;
  for(aux = chaine; *aux != '\0'; ++aux)
    ;
  char * end = aux;
  for(; chaine != aux; ++chaine, ++end) {
    ;
    *end = *chaine;
  }
  *end = '\0';
}

int main() {
  char chaine[40] = "Hello ! ";
  printf("x 1 : %s\n", chaine);
  chaine_double(chaine);
  printf("x 2 : %s\n", chaine);
  chaine_double(chaine);
  printf("x 4 : %s\n", chaine);
  exit(EXIT_SUCCESS);
}