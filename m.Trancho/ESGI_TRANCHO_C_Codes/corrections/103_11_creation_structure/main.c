/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 103.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Stats Stats;
struct Stats {
  int vie;
  int attaque;
  int defense;
  int vitesse;
};

int main() {
  Stats perso;
  perso.vie = 100;
  perso.attaque = 50;
  perso.defense = 70;
  perso.vitesse = 30;
  printf("Perso : {\n");
  printf("\tvie : %d\n", perso.vie);
  printf("\tattaque : %d\n", perso.attaque);
  printf("\tdefense : %d\n", perso.defense);
  printf("\tvitesse : %d\n", perso.vitesse);
  printf("}\n");
  exit(EXIT_SUCCESS);
}