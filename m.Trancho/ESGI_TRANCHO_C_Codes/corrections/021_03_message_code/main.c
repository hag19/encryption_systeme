/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 21.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  unsigned int p = 4285404239;
  unsigned int k = 2015201261;
  unsigned int code;
  unsigned int message;
  printf("Entrez un code : ");
  scanf("%x", &code);
  message = ((unsigned long)k * code) % p;
  printf("Message : %x\n", message);
  exit(EXIT_SUCCESS);
}