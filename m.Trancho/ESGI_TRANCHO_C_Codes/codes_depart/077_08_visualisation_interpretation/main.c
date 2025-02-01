#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_char(unsigned char * ptr, int taille) {
  int i;
  printf("[");
  for(i = 0; i < taille; ++i, ++ptr) {
    if(i) printf(", ");
    printf("0x%x", *ptr);
  }
  printf("]\n");
}

void read_int(unsigned int * ptr, int taille) {
  int i;
  printf("[");
  for(i = 0; i < taille; ++i, ++ptr) {
    if(i) printf(", ");
    printf("0x%x", *ptr);
  }
  printf("]\n");
}

int main() {
  char chaine[] = "Exemple de texte";
  int values[] = {0xFEEDCAFE, 0xC0DEF00D};
  /* TODO : appeler read_char sur chaine */
  /* TODO : appeler read_int sur values */
  /* TODO : appeler read_int sur chaine */
  /* TODO : appeler read_char sur values */
  exit(EXIT_SUCCESS);
}