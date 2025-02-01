/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 96.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
  FILE * output = stdout;
  FILE * current = NULL;
  int i;
  int car;
  for(i = 1; i < argc; ++i) {
    if((current = fopen(argv[i], "r")) == NULL) {
      fprintf(stderr, "Erreur ouverture \"%s\".\n", argv[i]);
      continue;
    }
    while((car = fgetc(current)) != EOF) {
      fputc(car, output);
    }
    fclose(current);
  }
  exit(EXIT_SUCCESS);
}