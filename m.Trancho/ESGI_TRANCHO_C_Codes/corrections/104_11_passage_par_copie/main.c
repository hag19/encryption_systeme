/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 104.
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

Stats Stats_creer(int vie, int attaque, int defense, int vitesse) {
  Stats perso;
  perso.vie = vie;
  perso.attaque = attaque;
  perso.defense = defense;
  perso.vitesse = vitesse;
  return perso;
}

void Stats_afficher(const Stats perso) {
  printf("Perso : {\n");
  printf("\tvie : %d\n", perso.vie);
  printf("\tattaque : %d\n", perso.attaque);
  printf("\tdefense : %d\n", perso.defense);
  printf("\tvitesse : %d\n", perso.vitesse);
  printf("}\n");
}

int main() {
  Stats perso = Stats_creer(100, 50, 70, 30);
  Stats_afficher(perso);
  exit(EXIT_SUCCESS);
}