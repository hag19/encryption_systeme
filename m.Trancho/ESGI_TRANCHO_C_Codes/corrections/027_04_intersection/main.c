/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 27.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  int age;
  printf("Quel est votre âge ? ");
  scanf("%d", &age);

  if(age >= 18 && age <= 25) {
    printf("Vous êtes un jeune de 18 - 25 ans.\n");
  } else {
    printf("Vous n'êtes pas un jeune de 18 - 25 ans.\n");
  }
  exit(EXIT_SUCCESS);
}