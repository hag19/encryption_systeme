/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 26.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  int age;
  printf("Quel est votre âge ? ");
  scanf("%d", &age);
  printf("Selon le cycle de vie, votre catégorie d'âge est ");
  if(age <= 14) {
    printf("Enfant.\n");
  } else if(age <= 24) {
    printf("Adolescent.\n");
  } else if(age <= 64) {
    printf("Adulte.\n");
  } else {
    printf("Aîné.\n");
  }
  exit(EXIT_SUCCESS);
}