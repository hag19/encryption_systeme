/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 14.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  unsigned char first;
  unsigned char second;
  unsigned char third;
  unsigned char fourth;
  unsigned int entier;
  float flottant;
  printf("Entrez quatre caractères : ");
  scanf("%c%c%c%c", &first, &second, &third, &fourth);
  entier = first + second * 0x100 + third * 0x10000 + fourth * 0x1000000;
  printf("Copiez l'entier %x : ", entier);
  scanf("%x", &flottant);
  printf("Codage : %.8e\n", flottant);
  exit(EXIT_SUCCESS);
}