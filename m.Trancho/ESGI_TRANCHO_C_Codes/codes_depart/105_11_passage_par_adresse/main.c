#include <stdio.h>
#include <stdlib.h>

/* TODO : utiliser votre structure Stats */

int Stats_creer(Stats * perso, int vie, int attaque, int defense, int vitesse) {
  if(vie < 0 || attaque < 0 || defense < 0 || vitesse < 0) {
    fprintf(stderr, "Les statistiques ne peuvent pas être négatives.\n");
    return 0;
  }
  /* TODO : affecter perso avec les valeurs adéquates */
  return 1;
}

void Stats_afficher(const Stats * perso) {
  printf("Perso : {\n");
  /* TODO : afficher perso */
  printf("}\n");
}

int main() {
  Stats perso;
  if(! Stats_creer(&perso, 100, 50, 70, 30)) {
    fprintf(stderr, "Erreur création personnage : arrêt.\n");
    exit(EXIT_FAILURE);
  }
  Stats_afficher(&perso);
  exit(EXIT_SUCCESS);
}