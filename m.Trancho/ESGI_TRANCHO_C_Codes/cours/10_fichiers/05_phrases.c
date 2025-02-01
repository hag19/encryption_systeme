/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

int carInChaine(char c, const char * chaine) {
  for(; *chaine != '\0'; ++chaine) {
    if(*chaine == c) {
      return 1;
    }
  }
  return 0;
}

int lirePhrase(FILE * file, long * start, long * end) {
  int car;
  while((car = fgetc(file)) != EOF) {
    if(! carInChaine(car, "\t\n ")) {
      break;
    }
  }
  if(start) /* on récupère la position du début de la phrase */
    *start = ftell(file) - 1;
  do {
    if(car == '.') {
      break;
    }
  } while((car = fgetc(file)) != EOF);
  if(end) /* on récupère la position de la fin de la phrase */
    *end = ftell(file);
  return car != EOF;
}

void afficherPortionFichier(FILE * file, long start, long end) {
  /* on se replace dans le fichier à la position indiquée */
  fseek(file, start, SEEK_SET);
  while(ftell(file) != end) { putchar(fgetc(file)); }
}
int main() {
  FILE * file = NULL;
  if((file = fopen("message.txt", "r")) == NULL) {
  	fprintf(stderr, "Erreur ouverture message.txt\n");
  	exit(EXIT_FAILURE);
  }
  int i;
  long start, end;
  for(i = 0; lirePhrase(file, NULL, NULL); ++i);
  printf("%d phrases.\n", i);
  rewind(file); /* on rembobine le fichier au début */
  for(i = 0; lirePhrase(file, &start, &end); ++i) {
    printf(" - Phrase %d (%ld caracteres): ", i + 1, end - start);
    afficherPortionFichier(file, start, end);
    printf("\n");
  }
  fclose(file);
  exit(EXIT_SUCCESS);
}