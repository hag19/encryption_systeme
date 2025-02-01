/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 29.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  /* Nous déclarons les entrées de l'utilisateur : */
  float argent;
  float prix;
  float remise;
  
  /* Nous lisons les entrées de l'utilisateur : */
  printf("Votre argent : ");
  scanf("%f", &argent);
  printf("Le prix de l'article (hors soldes) : ");
  scanf("%f", &prix);
  printf("Remise en %% : ");
  scanf("%f", &remise);
  
  /* Nous pouvons rendre conforme les entrées à notre calcul   */
  /* ou vérifier leur validité :                               */
  if(prix < 0.) {
    printf("Un prix négatif, étrange ...\n");
    exit(EXIT_FAILURE);
  }
  if(remise < 0.) {
    remise *= -1.;
  }
  if(remise > 100.) {
    printf("La remise ne peut pas excéder -100 %% ...\n");
    exit(EXIT_FAILURE);
  }
  
  /* Nous calculons le prix en solde : */
  prix *= (1 - remise / 100.);
  
  printf("L'article en solde vaut %g\n", prix);
  
  /* Nous prenons une décision : */
  if(argent >= prix) {
    printf("J'achète !\n");
  } else if(argent < 0.) {
    printf("Vous ne seriez pas déjà à découvert ?\n");
  } else {
    printf("Il faudra encore économiser ...\n");
  }
  
  exit(EXIT_SUCCESS);
}