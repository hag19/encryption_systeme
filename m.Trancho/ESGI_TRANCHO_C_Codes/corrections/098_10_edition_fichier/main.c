/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 98.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  const char * path = "exemple.txt";
  FILE * fichier = NULL;
  int car;
  if((fichier = fopen(path, "r+")) == NULL) {
    fprintf(stderr, "Erreur ouverture %s\n", path);
    exit(EXIT_FAILURE);
  }
  while((car = fgetc(fichier)) != EOF) {
    if(car >= 'a' && car <= 'z') {
      fseek(fichier, -1, SEEK_CUR);
      fputc(car - 'a' + 'A', fichier);
    }
  }
  fclose(fichier);
  fichier = NULL;
  exit(EXIT_SUCCESS);
}