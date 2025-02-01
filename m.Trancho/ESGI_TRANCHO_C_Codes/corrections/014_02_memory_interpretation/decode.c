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
  printf("Entrez un réel : ");
  scanf("%f", &entier);
  first = entier;
  second = entier / 0x100;
  third = entier / 0x10000;
  fourth = entier / 0x1000000;
  printf("Texte : \"%c%c%c%c\"\n", first, second, third, fourth);
  exit(EXIT_SUCCESS);
}