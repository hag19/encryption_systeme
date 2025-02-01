#include <stdio.h>
#include <stdlib.h>

/* TODO : utiliser votre structure Stats */

Stats * Stats_creer(int vie, int attaque, int defense, int vitesse) {
  /* TODO : allouer et affecter une structure Stats */
}

void Stats_free(Stats ** perso) {
  /* TODO : libérer une struture Stats */
}

void Stats_afficher(const Stats * perso) {
  printf("Perso : {\n");
  /* TODO : afficher perso */
  printf("}\n");
}

int main() {
  Stats * perso = NULL;
  if((perso = Stats_creer(100, 50, 70, 30)) == NULL) {
    fprintf(stderr, "Erreur création personnage : arrêt.\n");
    exit(EXIT_FAILURE);
  }
  Stats_afficher(perso);
  Stats_free(&perso);
  exit(EXIT_SUCCESS);
}