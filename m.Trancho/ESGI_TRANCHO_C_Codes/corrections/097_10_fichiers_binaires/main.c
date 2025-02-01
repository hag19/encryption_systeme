/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 97.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  const char * path = "nombre.bin";
  FILE * fichier = NULL;
  int compteur = 0;
  if((fichier = fopen(path, "rb")) != NULL) {
    if(fread(&compteur, sizeof(int), 1, fichier) != 1) {
      fprintf(stderr, "Erreur lecture dans %s\n", path);
    }
    fclose(fichier);
  }
  ++compteur;
  if((fichier = fopen(path, "wb")) == NULL) {
    fprintf(stderr, "Erreur ouverture %s\n", path);
    exit(EXIT_FAILURE);
  }
  if(fwrite(&compteur, sizeof(int), 1, fichier) != 1) {
    fprintf(stderr, "Erreur écriture dans %s\n", path);
    fclose(fichier);
    exit(EXIT_FAILURE);
  }
  fclose(fichier);
  fichier = NULL;
  printf("Programme lancé %d fois\n", compteur);
  exit(EXIT_SUCCESS);
}