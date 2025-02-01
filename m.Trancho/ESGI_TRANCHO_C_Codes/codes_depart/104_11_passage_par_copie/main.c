#include <stdio.h>
#include <stdlib.h>

/* TODO : utiliser votre structure Stats */

Stats Stats_creer(int vie, int attaque, int defense, int vitesse) {
  Stats perso;
  /* TODO : renvoyer perso avec les valeurs adéquates */
  return perso;
}

void Stats_afficher(const Stats perso) {
  printf("Perso : {\n");
  /* TODO : afficher perso */
  printf("}\n");
}

int main() {
  Stats perso = Stats_creer(100, 50, 70, 30);
  Stats_afficher(perso);
  exit(EXIT_SUCCESS);
}