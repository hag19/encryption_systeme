#include <stdio.h>
#include <stdlib.h>
/* interdiction d'importer string.h */

void chaine_double(char * chaine) {
  char * aux;
  /* TODO : aux peut être utilisée */
  char * end;
  /* TODO : end doit permettre la copie des caracteres de chaine */
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