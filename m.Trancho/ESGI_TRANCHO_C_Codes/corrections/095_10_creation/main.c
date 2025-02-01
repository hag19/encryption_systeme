/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 95.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  const char * chemin = "test.txt";
  FILE * fichier = NULL;
  if((fichier = fopen(chemin, "w")) == NULL) {
    fprintf(stderr, "Erreur creation \"%s\" : arrêt.\n", chemin);
    exit(EXIT_SUCCESS);
  }
  fprintf(fichier, "Test.\n");
  fclose(fichier);
  fichier = NULL;
  exit(EXIT_SUCCESS);
}