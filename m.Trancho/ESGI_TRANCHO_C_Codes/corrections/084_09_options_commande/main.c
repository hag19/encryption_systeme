/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 84.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]) {
  int i;
  int first = 0;
  int second = 0;
  int x = 0, y = 0;
  for(i = 0; i < argc; ++i) {
    if(strcmp(argv[i], "--first") == 0 || strcmp(argv[i], "-f") == 0) {
      if(argc - i <= 1) {
        fprintf(stderr, "Options : Pas assez d'arguments pour %s\n", argv[i]);
        continue;
      }
      ++i;
      first = atoi(argv[i]);
      continue;
    } else if(strcmp(argv[i], "--second") == 0 || strcmp(argv[i], "-s") == 0) {
      if(argc - i <= 1) {
        fprintf(stderr, "Options : Pas assez d'arguments pour %s\n", argv[i]);
        continue;
      }
      ++i;
      second = atoi(argv[i]);
      continue;
    } else if(strcmp(argv[i], "--coords") == 0 || strcmp(argv[i], "-c") == 0) {
      if(argc - i <= 2) {
        fprintf(stderr, "Options : Pas assez d'arguments pour %s\n", argv[i]);
        continue;
      }
      ++i;
      x = atoi(argv[i]);
      ++i;
      y = atoi(argv[i]);
      continue;
    }
  }
  printf("first = %d\nsecond = %d\ncoords = (%d, %d)\n", first, second, x, y);
  exit(EXIT_SUCCESS);
}