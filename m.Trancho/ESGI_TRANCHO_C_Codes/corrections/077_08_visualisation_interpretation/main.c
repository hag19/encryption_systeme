/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 77.
 */

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
  read_char((unsigned char *)chaine, strlen(chaine));
  read_int((unsigned int *)values, 2);
  read_int((unsigned int *)chaine, strlen(chaine) / sizeof(int));
  read_char((unsigned char *)values, 2 * sizeof(int));
  exit(EXIT_SUCCESS);
}