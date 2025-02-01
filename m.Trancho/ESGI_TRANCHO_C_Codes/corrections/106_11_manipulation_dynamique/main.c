/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 106.
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

Stats * Stats_creer(int vie, int attaque, int defense, int vitesse) {
  Stats * perso = NULL;
  if(vie < 0 || attaque < 0 || defense < 0 || vitesse < 0) {
    fprintf(stderr, "Les statistiques ne peuvent pas être négatives.\n");
    return NULL;
  }
  if((perso = (Stats *)malloc(sizeof(Stats))) == NULL) {
    fprintf(stderr, "Erreur allocation Stats.\n");
    return NULL;
  }
  perso->vie = vie;
  perso->attaque = attaque;
  perso->defense = defense;
  perso->vitesse = vitesse;
  return perso;
}

void Stats_free(Stats ** perso) {
  if(perso == NULL || *perso == NULL) {
    return;
  }
  free(*perso);
  *perso = NULL;
}

void Stats_afficher(const Stats * perso) {
  printf("Perso : {\n");
  printf("\tvie : %d\n", perso->vie);
  printf("\tattaque : %d\n", perso->attaque);
  printf("\tdefense : %d\n", perso->defense);
  printf("\tvitesse : %d\n", perso->vitesse);
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