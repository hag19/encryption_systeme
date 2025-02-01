/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 28.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  int vitesse, limitation;
  int diff;
  int amende = 0, points = 0;
  printf("Entrez vitesse et limitation : ");
  scanf("%d %d", &vitesse, &limitation);
  diff = vitesse - limitation;
  if(diff >= 50) {
    amende = 1500; points = 6;
  } else if(diff >= 40) {
    amende = 135; points = 4;
  } else if(diff >= 30) {
    amende = 135; points = 3;
  } else if(diff >= 20) {
    amende = 135; points = 2;
  } else if(diff > 0) {
    if(limitation > 50) {
      amende = 68; points = 1;
    } else {
      amende = 135; points = 1;
    }
  }
  if(diff > 0) {
    printf("Amende de %d et retrait de %d point%s\n", amende, points, (points > 1) ? "s" : "");
  } else {
    printf("Pas de problème, circulez.\n");
  }
  exit(EXIT_SUCCESS);
}